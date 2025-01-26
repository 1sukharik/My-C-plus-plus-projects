#include "iostream"
#include "vector"
#include "fstream"
#include <filesystem>
#include "map"
#include "set"
#include "stack"
#include "cmath"
#ifndef LABWORK11_1SUKHARIK_LIB_QUERY_H_
#define LABWORK11_1SUKHARIK_LIB_QUERY_H_

struct QueryWordInfo {
  std::string word;
  std::string name_of_storage;
  bool operation;
  int priority;
  QueryWordInfo(std::string a, std::string b, bool is_operation, int priority)
      : word(a), name_of_storage(b), operation(is_operation), priority(priority) {}
};

struct WordInfo {
  std::string name;
  int amount_in_all_files;
  std::vector<std::pair<std::string, std::vector<int>>> file_which_contains_word;
  WordInfo() {

  }
  WordInfo(std::string name_, int a, std::vector<std::string> v) {
    name = name_;
    amount_in_all_files = a;
    int t = a;
    for (int i = 0; i < v.size(); i++) {
      if (t == 0) {
        break;
      }
      std::string filename = v[i];
      int amount = std::stoi(v[++i]);
      std::vector<int> numbers;
      numbers.push_back(amount);
      if (amount > 1) {
        t -= (amount);
      } else {
        t--;
      }
      for (int j = 0; j < amount; j++) {
        numbers.push_back(std::stoi(v[++i]));
      }
      file_which_contains_word.push_back({filename, numbers});
      numbers.clear();

    }

  }
};

class Query {
 public:
  std::string CheckQuery(int argc, std::vector<std::string> argv) {
    for (int i = 0; i < argc; i++) {
      if (i == 0 && argv[i] == "OR" || i == 0 && argv[i] == "AND") {
        return "FIRST MUST BE WORD, NOT COMMAND";
      } else if ((argv[i] == "AND" || argv[i] == "OR") && (argv[i - 1] == "OR" || argv[i] == "AND")) {
        return "NO 2 COMMAND IN A ROW";
      }else if ((ConvertToLowercase(argv[i]) == "and" || ConvertToLowercase(argv[i]) == "or") && argv[i]!="AND" && argv[i]!="OR") {
        return "INCORRECT WRITING OF COMMAND";
      }
    }
  }

  void Parse(int argc, char **argv) {
    std::string name_of_index = argv[2];
    std::string name_of_index_files = argv[3];
    int k_ = std::stoi(argv[4]);
    int priority_of_operation = 0;
    std::vector<std::string> words_in_query;
    std::string word;
    std::stack<QueryWordInfo> words;

    std::stack<QueryWordInfo> operations;

    std::string name_of_res_file = GetPathInString(name_of_index) + "\\result_file.txt";
    for (int i = 5; i < argc; i++) {
      if (i == 5 && argv[i] == "OR" || i == 5 && argv[i] == "AND") {
        std::cout << "FIRST MUST BE WORD, NOT COMMAND";
        return;
      } else if ((argv[i] == "AND" || argv[i] == "OR") && (argv[i - 1] == "OR" || argv[i] == "AND")) {
        std::cout << "NO 2 COMMAND IN A ROW";
        return;
      }
    }

    for (int i = 5; i < argc; i++) {
      std::string arg = argv[i];
      if (arg[0] == '(') {
        priority_of_operation = 2;
        arg = arg.substr(1, arg.size() - 1);
        if (arg[arg.size() - 1] == ')') {
          arg = arg.substr(0, arg.size() - 1);
        }
        words.push(QueryWordInfo(arg, name_of_res_file, false, -1));
      } else if (arg == "AND") {
        if (priority_of_operation == 2) {
          operations.push(QueryWordInfo("AND", name_of_res_file, true, 2));
        } else {
          if (operations.size() > 0 && 1 < operations.top().priority) {
            while (operations.size() > 0 && 1 < operations.top().priority) {
              words.push(operations.top());
              operations.pop();
            }
          }
          operations.push(QueryWordInfo("AND", name_of_res_file, true, 1));
        };
      } else if (arg == "OR") {
        if (priority_of_operation == 2) {
          if (operations.size() > 0 && 2 > operations.top().priority) {
            while (operations.size() > 0 && 2 > operations.top().priority) {
              words.push(operations.top());
              operations.pop();
            }
          }
          operations.push(QueryWordInfo("OR", name_of_res_file, true, 2));
        } else {
          operations.push(QueryWordInfo("OR", name_of_res_file, true, 0));
        };
      } else if (arg[arg.size() - 1] == ')') {
        priority_of_operation = -1;
        arg = arg.substr(0, arg.size() - 1);
        words.push(QueryWordInfo(arg, name_of_res_file, false, -1));
      } else {
        if (ConvertToLowercase(arg) == "and" || ConvertToLowercase(arg) == "or") {
          std::cout << "INCORRECT WRITING OF COMMAND";
          return;
        }
        words.push(QueryWordInfo(arg, name_of_res_file, false, -1));
      }
    }
    while (!operations.empty()) {
      words.push(operations.top());
      operations.pop();
    }
    std::stack<QueryWordInfo> reversed_stack;
    while (!words.empty()) {
      reversed_stack.push(words.top());
      words.pop();
    }
    std::stack<QueryWordInfo> solve_stack;
    bool we_have_watch_file = false;
    while (!reversed_stack.empty()) {

      if (!reversed_stack.top().operation) {
        solve_stack.push(reversed_stack.top());
        reversed_stack.pop();
      } else {
        if (reversed_stack.top().word == "AND") {
          if (!we_have_watch_file) {
            we_have_watch_file = true;
            QueryWordInfo a = solve_stack.top();
            solve_stack.pop();
            MyAnd(a, solve_stack.top(), name_of_index);
            solve_stack.pop();

            solve_stack.push(a);

          } else {
            QueryWordInfo a = solve_stack.top();
            solve_stack.pop();
            CustomAND(a, name_of_index);
            solve_stack.pop();

            solve_stack.push(a);
          }

        } else {
          if (!we_have_watch_file) {
            we_have_watch_file = true;
            QueryWordInfo a = solve_stack.top();
            solve_stack.pop();
            MyOr(a, solve_stack.top(), name_of_index);
            solve_stack.pop();

            solve_stack.push(a);

          } else {

            QueryWordInfo a = solve_stack.top();
            solve_stack.pop();
            CustomOR(a, name_of_index);
            solve_stack.pop();

            solve_stack.push(a);

          }

        }
        reversed_stack.pop();
      }
    }
    MakeScore(name_of_index_files, name_of_res_file, name_of_index, k_);

  }
 private:
  void CopyFile(std::string to, std::string from);

  std::string FindWord(std::string word, std::string index_name);

  std::vector<std::string> GetWords(std::string line);

  int CountAmountOfFilesForWord(std::string a);

  std::string GetKWordInString(std::string a, int n);

  void MyAnd(QueryWordInfo word1, QueryWordInfo word2, std::string name_of_index) {
    std::fstream ResultFile(word1.name_of_storage, std::ios::out);
    std::string all_word_info = FindWord(word1.word, name_of_index);
    std::string all_word_info2 = FindWord(word2.word, name_of_index);
    WordInfo find1(word1.word, CountAmountOfFilesForWord(all_word_info), GetWords(all_word_info));
    WordInfo find2(word2.word, CountAmountOfFilesForWord(all_word_info2), GetWords(all_word_info2));
    for (auto& u : find1.file_which_contains_word) {
      for (auto& u1 : find2.file_which_contains_word) {
        if (u.first == u1.first) {
          ResultFile << u.first << " " << std::to_string(u.second[0] + u1.second[0]) << " " << word1.word << " ";
          int k;
          for (int i : u.second) {
            ResultFile << std::to_string(i) << " ";
          }
          k = 0;
          ResultFile << word2.word << " ";
          for (int i : u1.second) {
            if (k == u1.second.size() - 1) {
              ResultFile << std::to_string(i) << std::endl;
            } else {
              ResultFile << std::to_string(i) << " ";
            }
            k++;
          }

        }
      }
    }

    ResultFile.close();

  }

  void MyOr(QueryWordInfo word1, QueryWordInfo word2, std::string name_of_index) {
    std::fstream ResultFile(word1.name_of_storage, std::ios::out);
    std::string all_word_info = FindWord(word1.word, name_of_index);
    std::string all_word_info2 = FindWord(word2.word, name_of_index);
    WordInfo find1(word1.word, CountAmountOfFilesForWord(all_word_info), GetWords(all_word_info));
    WordInfo find2(word2.word, CountAmountOfFilesForWord(all_word_info2), GetWords(all_word_info2));
    bool flag = false;
    for (auto& u : find1.file_which_contains_word) {
      for (auto& u1 : find2.file_which_contains_word) {
        if (u.first == u1.first) {
          flag = true;
          ResultFile << u.first << " " << std::to_string(u.second[0] + u1.second[0]) << " " << word1.word << " ";
          int k;
          for (int i : u.second) {
            ResultFile << std::to_string(i) << " ";
          }
          k = 0;
          ResultFile << word2.word << " ";
          for (int i : u1.second) {
            if (k == u1.second.size() - 1) {
              ResultFile << std::to_string(i) << std::endl;
            } else {
              ResultFile << std::to_string(i) << " ";
            }
            k++;
          }

        }
        if (flag) {
          break;
        }
      }
      if (!flag) {
        ResultFile << u.first << " " << std::to_string(u.second[0]) << " ";
        int k = 0;
        ResultFile << word1.word << " ";
        for (int i : u.second) {
          if (k == u.second.size() - 1) {
            ResultFile << std::to_string(i) << std::endl;
          } else {
            ResultFile << std::to_string(i) << " ";
          }
          k++;
        }
      } else {
        flag = false;
      }
    }
    for (auto& u : find2.file_which_contains_word) {
      for (auto& u1 : find1.file_which_contains_word) {
        if (u.first == u1.first) {
          flag = true;
          if (flag) {
            break;
          }
        }
      }
      if (!flag) {
        ResultFile << u.first << " " << std::to_string(u.second[0]) << " ";
        int k = 0;
        ResultFile << word2.word << " ";
        for (int i : u.second) {
          if (k == u.second.size() - 1) {
            ResultFile << std::to_string(i) << std::endl;
          } else {
            ResultFile << std::to_string(i) << " ";
          }
          k++;
        }
      } else {
        flag = false;
      }

    }

    ResultFile.close();
  }

  void CustomOR(QueryWordInfo word1, std::string index_file) {
    std::string help_file = GetPathInString(word1.name_of_storage) + "\\help_file.txt";
    CopyFile(help_file, word1.name_of_storage);
    std::string line;
    std::fstream Help(help_file);
    std::fstream Storage(word1.name_of_storage, std::ios::out);
    std::string necessary_word = FindWord(word1.word, index_file);
    WordInfo b(GetKWordInString(necessary_word, 1),
               std::stoi(GetKWordInString(necessary_word, 2)),
               GetWords(necessary_word));//информация о просматриваемом слове

    while (std::getline(Help, line)) {
      WordInfo a(GetKWordInString(line, 1),
                 std::stoi(GetKWordInString(line, 2)),
                 GetWords(line));//смотрим информацию о файле, лежащем в файле ранжировки
      bool flag = false;
      for (auto& name_of_file : b.file_which_contains_word) {

        if (name_of_file.first == a.name) {
          Storage << line << " " << b.name << " ";
          for (int i = 0; i < name_of_file.second.size(); i++) {
            if (i == name_of_file.second.size() - 1) {
              Storage << name_of_file.second[i];
            } else {
              Storage << name_of_file.second[i] << " ";
            }
          }
        }

      }
      if (!flag) {
        Storage << line << std::endl;
      }
    }
    Storage.close();
    Help.close();
    std::filesystem::remove(help_file);

  }

  void CustomAND(QueryWordInfo word1, std::string index_file) {
    std::string help_file = GetPathInString(word1.name_of_storage) + "\\help_file.txt";
    CopyFile(help_file, word1.name_of_storage);
    std::string line;
    std::fstream Help(help_file);
    std::fstream Storage(word1.name_of_storage, std::ios::out);
    while (std::getline(Help, line)) {
      WordInfo a(GetKWordInString(line, 1),
                 std::stoi(GetKWordInString(line, 2)),
                 GetWords(line));//смотрим информацию о файле, лежащем в файле ранжировки
      std::string necessary_word = FindWord(word1.word, index_file);
      WordInfo b(GetKWordInString(necessary_word, 1),
                 std::stoi(GetKWordInString(necessary_word, 2)),
                 GetWords(necessary_word));//информация о просматриваемом слове
      for (auto& u : b.file_which_contains_word) {
        if (u.first == a.name) {
          Storage << line << " " << b.name << " ";
          for (int i = 0; i < u.second.size(); i++) {
            if (i == u.second.size() - 1) {
              Storage << u.second[i];
            } else {
              Storage << u.second[i] << " ";
            }
          }
        }
      }

    }
    Storage.close();
    Help.close();
    std::filesystem::remove(help_file);

  }

  std::string GetPathInString(std::string a);

  std::string ConvertToLowercase(std::string& str) {
    std::string result = "";

    for (char ch : str) {

      result += std::tolower(ch);
    }

    return result;
  }

  std::pair<int, int> AmountOfFiles(std::string index_files) {
    int n = 0;
    int avg = 0;
    std::fstream AllFiles(index_files);
    std::string a;
    while (std::getline(AllFiles, a)) {
      avg += std::stoi(GetKWordInString(a, 2));
      n++;
    }
    avg /= n;
    return {n, n / avg};

  }
  void MakeScore(std::string index_files, std::string info_file, std::string index_file, int k) {
    std::string file;
    std::fstream Index(index_file);
    std::pair<int, int> P = AmountOfFiles(index_files);

    std::fstream AllFiles(index_files);
    std::fstream Info(info_file);
    std::set<std::pair<int, std::string>> result;
    double score_for_curr_file = 0;
    while (std::getline(Info, file)) {
      WordInfo a(GetKWordInString(file, 1), std::stoi(GetKWordInString(file, 2)), GetWords(file));
      for (auto& parametr : a.file_which_contains_word) {
        score_for_curr_file +=
            (((parametr.second[0] * (1.5 + 1)) / (parametr.second[0] + k * (1 - 0.75 + 0.75 * P.second)))
                * std::log((P.first - std::stoi(
                    GetKWordInString(file, 2)) + 0.5) / (std::stoi(GetKWordInString(file, 2)) + 0.5)));
      }
      result.insert({score_for_curr_file, file});

    }
    int i = 0;
    for (auto& u : result) {
      if (i == k) {
        break;
      } else {
        std::cout << u.first << " " << u.second << std::endl;
        i++;
      }
    }

  }

};
#endif //LABWORK11_1SUKHARIK_LIB_QUERY_H_
