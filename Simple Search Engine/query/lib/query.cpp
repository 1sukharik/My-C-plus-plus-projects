#include "query.h"



std::string Query::GetPathInString(std::string a) {
  std::string result;
  bool flag = false;
  for (int i = a.size() - 1; i >= 0; i--) {
    if (flag) {
      result += a[i];
    }
    if (a[i] == '\\') {
      flag = true;
    }

  }
  std::string res2;
  for (int i = result.size() - 1; i >= 0; i--) {
    res2 += result[i];
  }
  return res2;
}

std::string Query::GetKWordInString(std::string a, int n) {
  std::string result;
  int count = 0;
  for (auto& u : a) {
    if (u == ' ') {
      count++;
    } else {
      if (count == (n - 1)) {
        result += u;
      }
    }
  }
  return result;
}

int Query::CountAmountOfFilesForWord(std::string a) {
  int counter = 0;
  std::string ans;
  for (auto& u : a) {
    if (u == ' ') {
      counter++;
    } else if (counter == 1) {
      ans += u;

    }
  }
  return std::stoi(ans);
}
std::vector<std::string> Query::GetWords(std::string line) {
  std::string word;
  int counter = 0;
  std::vector<std::string> all_word_in_line;
  for (auto& u : line) {
    if (u != ' ' && counter >= 2) {
      word += u;
    } else if (u == ' ') {
      if (counter >= 2) {
        all_word_in_line.push_back(word);
        word.clear();
      }
      counter++;
    }
  }
  all_word_in_line.push_back(word);
  return all_word_in_line;

}
std::string Query::FindWord(std::string word, std::string index_name) {
  std::ifstream file(index_name);
  std::string line;
  while (std::getline(file, line)) {
    if (word == GetKWordInString(line, 1)) {
      return line;
    }
  }
}

void Query::CopyFile(std::string to, std::string from) {
  std::fstream FileReadTo(to, std::ios::out);
  std::fstream FileReadFrom(from, std::ios::in);
  if (!FileReadFrom || !FileReadTo) {
    std::cout << "CANT COPY FILE " << from << " TO " << to;
    return;
  }
  std::string a;
  while (std::getline(FileReadFrom, a)) {
    FileReadTo << a << std::endl;
  }
  FileReadFrom.close();
  FileReadTo.close();
}
