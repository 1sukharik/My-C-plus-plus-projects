

#ifndef LABWORK11_1SUKHARIK_LIB_INDEX_H_
#define LABWORK11_1SUKHARIK_LIB_INDEX_H_

#include "iostream"
#include "vector"
#include "fstream"
#include <filesystem>
#include "map"
#include "set"

class Index {
 public:

  void Parse(int argc, char **argv) {
    //-f/--file - название индекса
    //-d/--dir - название директории
    //-p/--put - куда положить индекс
    //-s/--sep - добавить разделитель
    //-e/--ex -какие существуют разделители

    for (int i = 2; i < argc; i++) {
      std::string arg = argv[i];
      if ((arg[1] == '-' && arg[2] == 'f') || (arg[1] == 'f')) {
        if (i + 1 >= argc) {
          std::cout << "NO FILE NAME";
          return;
        } else {
          name_of_index_from_cmd = argv[++i];
        }

      } else if ((arg[1] == '-' && arg[2] == 'd') || (arg[1] == 'd')) {
        if (i + 1 >= argc) {
          std::cout << "NO PATH NAME";
          return;
        } else {
          path_for_index_from_cmd = argv[++i];
        }

      } else if ((arg[1] == '-' && arg[2] == 'p') || (arg[1] == 'p')) {
        if (i + 1 >= argc) {
          std::cout << "NO DIRECTORY TO PUT NAME";
          return;
        } else {
          where_to_put_index_cmd = argv[++i];
        }
      } else if ((arg[1] == '-' && arg[2] == 's') || (arg[1] == 's')) {
        if (i + 1 >= argc) {
          std::cout << "NO SEPARATOR NAME";
          return;
        } else {
          AddSeparator(argv[++i][0]);
        }

      } else if ((arg[1] == '-' && arg[2] == 'e') || (arg[1] == 'e')) {
        if (i + 1 >= argc) {
          std::cout << "NO SEPARATOR NAME";
          return;
        } else {
          ++i;
          WhatSeparatorsExist();
        }

      } else {
        std::cout << "CHECK QUERIES";
        return;
      }

    }

    CreateIndex(name_of_index_from_cmd,
                where_to_put_index_cmd,
                path_for_index_from_cmd);

  }

  void Parse(int argc, std::vector<std::string> argv) {
    //-f/--file - название индекса
    //-d/--dir - название директории
    //-p/--put - куда положить индекс
    //-s/--sep - добавить разделитель
    //-e/--ex -какие существуют разделители

    for (int i = 2; i < argc; i++) {
      std::string arg = argv[i];
      if ((arg[1] == '-' && arg[2] == 'f') || (arg[1] == 'f')) {
        if (i + 1 >= argc) {
          std::cout << "NO FILE NAME";
          return;
        } else {
          name_of_index_from_cmd = argv[++i];
        }

      } else if ((arg[1] == '-' && arg[2] == 'd') || (arg[1] == 'd')) {
        if (i + 1 >= argc) {
          std::cout << "NO PATH NAME";
          return;
        } else {
          path_for_index_from_cmd = argv[++i];
        }

      } else if ((arg[1] == '-' && arg[2] == 'p') || (arg[1] == 'p')) {
        if (i + 1 >= argc) {
          std::cout << "NO DIRECTORY TO PUT NAME";
          return;
        } else {
          where_to_put_index_cmd = argv[++i];
        }
      } else if ((arg[1] == '-' && arg[2] == 's') || (arg[1] == 's')) {
        if (i + 1 >= argc) {
          std::cout << "NO SEPARATOR NAME";
          return;
        } else {
          AddSeparator(argv[++i][0]);
        }

      } else if ((arg[1] == '-' && arg[2] == 'e') || (arg[1] == 'e')) {
        if (i + 1 >= argc) {
          std::cout << "NO SEPARATOR NAME";
          return;
        } else {
          ++i;
          WhatSeparatorsExist();
        }

      } else {
        std::cout << "CHECK QUERIES";
        return;
      }

    }

    CreateIndex(name_of_index_from_cmd,
                where_to_put_index_cmd,
                path_for_index_from_cmd);

  }

  void AddSeparator(char symbol) {
    not_part_of_word.push_back(symbol);
  }

  void WhatSeparatorsExist() {
    for (auto& u : not_part_of_word) {
      std::cout << u << " ";
    }
  }

  std::vector<char> WhatSeparatorsExistVector() {
    return not_part_of_word;
  }

 private:
  int amount_of_documents = 0;
  int amount_of_words = 0;
  int amount_of_words_for_curr_document = 0;
  std::string name_of_index_from_cmd;
  std::string path_for_index_from_cmd;
  std::string where_to_put_index_cmd;

  std::vector<char> not_part_of_word = {'/', '.', ',', '!', '?', '\\', ';', '-', '<', '>', '$'};
  void CreateIndex(std::string name_of_index_file, std::string where_to_put_index, std::string path_of_watching) {
    std::string files_file_name = where_to_put_index + "\\" + "index_files.txt";
    name_of_index_file = where_to_put_index + "\\" + name_of_index_file;
    std::fstream NewIndex(name_of_index_file, std::ios::out);
    if (NewIndex) {
      RecursiveWatchingThrough(path_of_watching, name_of_index_file, files_file_name);
    } else {
      std::cout << "CANT CREATE INDEX FILE\n";
      return;
    }
    NewIndex.close();

  }

  void MergeIndexes(std::string first_index, std::string second_index, int regime);

  bool IfSymbolCorrect(char symbol) {
    for (auto& u : not_part_of_word) {
      if (u == symbol) {
        return false;
      }
    }
    return true;
  }

  void MakeWordClear(std::string& word) {
    int i = 0;
    for (auto& u : word) {
      if (!IfSymbolCorrect(u)) {
        word = word.substr(0, i);
      }
      i++;

    }
  }

  void CopyFile(std::string to, std::string from);

  std::string GetKWordInString(std::string a, int n);

  std::string GetNumbersOfLines(std::string a, std::string b);

  std::string GetRestOfString(std::string a);

  int GetNumberOfFiles(std::string a);

  std::string GetPathInString(std::string a);

  std::vector<std::string> GetWords(std::string line) {
    std::string word;
    std::vector<std::string> all_word_in_line;
    for (auto& u : line) {
      if (u != ' ') {
        word += u;
      } else {
        MakeWordClear(word);
        all_word_in_line.push_back(word);
        word.clear();
      }
    }
    MakeWordClear(word);
    all_word_in_line.push_back(word);
    return all_word_in_line;

  }

//  void SetLineNumbersInIndex(std::string index_name) {
//    CopyFile(GetPathInString(index_name) + "\\" + "copied_index.txt", index_name);
//    std::string line;
//    std::fstream Copy(GetPathInString(index_name) + "\\" + "copied_index.txt");
//    std::fstream Ind(index_name, std::ios::out);
//    int line_number = 1;
//    while (std::getline(Copy, line)) {
//      Ind << line << " " << std::to_string(line_number) << std::endl;
//      line_number++;
//    }
//    Copy.close();
//    Ind.close();
//    std::filesystem::remove(GetPathInString(index_name) + "\\" + "copied_index.txt");
//  }

  std::string MakeIndexFromOneFile(std::string file_name) {
    std::fstream ReadFile;
    try {
      ReadFile.open(file_name);
    } catch (std::exception& ex) {
      std::cout << ex.what();
    }
    int size_of_block = 0;
    std::string name_of_help_index = GetPathInString(file_name) + "\\mini_index_to_help.txt";
    std::string name_of_help_index_2 = GetPathInString(file_name) + "\\mini_index_to_help_2.txt";
    std::fstream Help1(name_of_help_index, std::ios::out);
    std::map<std::string, std::vector<std::string>> small_index;
    std::set<std::string> all_words;
    std::string line;
    int line_number = 1;
    while (std::getline(ReadFile, line)) {
      for (auto& word : GetWords(line)) {
        size_of_block++;

        if (ReadFile) {
          amount_of_words++;
          amount_of_words_for_curr_document++;
        }
        int startsize = all_words.size();
        all_words.insert(word);
        if (startsize == all_words.size()) {
          small_index[word][0] = std::to_string(std::stoi(small_index[word][0]) + 1);
          small_index[word][2] = std::to_string(std::stoi(small_index[word][2]) + 1);
          small_index[word].push_back(std::to_string(line_number));

        } else {
          std::vector<std::string> a(3);
          small_index.insert({word, a});
          small_index[word][0] = "1";
          small_index[word][1] = file_name;
          small_index[word][2] = "1";
          small_index[word].push_back(std::to_string(line_number));

        }
        if (size_of_block == 10000) {
          size_of_block = 0;
          std::fstream Help2(name_of_help_index_2, std::ios::out);
          for (auto& u : small_index) {
            int i = 0;
            Help2 << u.first << " ";
            for (auto& u1 : u.second) {
              if (i == u.second.size() - 1) {
                Help2 << u1;
              } else {
                Help2 << u1 << " ";
              }
              i++;
            }

            Help2 << std::endl;
          }
          Help2.close();

          MergeIndexes(name_of_help_index, name_of_help_index_2, 1);
          small_index.clear();
          all_words.clear();
        }

      }
      line_number++;

    }

    std::fstream Help2(name_of_help_index_2, std::ios::out);
    for (auto& u : small_index) {
      int i = 0;
      Help2 << u.first << " ";
      for (auto& u1 : u.second) {
        if (i == u.second.size() - 1) {
          Help2 << u1;
        } else {
          Help2 << u1 << " ";
        }
        i++;
      }

      Help2 << std::endl;
    }
    Help2.close();
    MergeIndexes(name_of_help_index, name_of_help_index_2, 1);

    ReadFile.close();
    Help1.close();
    std::filesystem::remove(name_of_help_index_2);
    return name_of_help_index;
  }

  void RecursiveWatchingThrough(const std::string& curr_path,
                                std::string name_of_index_file,
                                std::string files_file_name) {
    std::map<std::string, int> all_files;
    std::fstream NewFilesFile(files_file_name, std::ios::out);
    for (const auto& file : std::filesystem::directory_iterator(curr_path)) {

      if (std::filesystem::is_directory(file)) {
        RecursiveWatchingThrough(file.path().string(), name_of_index_file, files_file_name);
      } else {
        if (file.path().string() != (GetPathInString(file.path().string()) + "\\mini_index_to_help.txt")
            || file.path().string() != (GetPathInString(file.path().string()) + "\\mini_index_to_help_2.txt")) {
          amount_of_documents++;
          std::string help_index = MakeIndexFromOneFile(file.path().string());
          MergeIndexes(name_of_index_file, help_index, 0);
          all_files.insert({file.path().string(), amount_of_words_for_curr_document});
          if (all_files.size() == 10000) {

            std::string help_files_file = GetPathInString(files_file_name) + "\\help_files_file.txt";
            std::fstream FilesFile(help_files_file);

            for (auto& u : all_files) {
              FilesFile << u.first << " " << std::to_string(u.second) << std::endl;
            }
            all_files.clear();
            MergeIndexes(files_file_name, help_files_file, 0);
            FilesFile.close();

          }
//          NewFilesFile << file.path().string() << " " << amount_of_words_for_curr_document << std::endl;
          std::filesystem::remove(help_index);
        }
      }
      amount_of_words_for_curr_document = 0;

    }
    std::string help_files_file = GetPathInString(files_file_name) + "\\help_files_file.txt";
    std::fstream FilesFile(help_files_file, std::ios::out);

    for (auto& u : all_files) {
      FilesFile << u.first << " " << std::to_string(u.second) << std::endl;
    }
    MergeIndexes(files_file_name, help_files_file, 0);
    FilesFile.close();
    NewFilesFile.close();
    all_files.clear();
    std::filesystem::remove(help_files_file);
//    SetLineNumbersInIndex(name_of_index_file);
  }

};

#endif //LABWORK11_1SUKHARIK_LIB_INDEX_H_
