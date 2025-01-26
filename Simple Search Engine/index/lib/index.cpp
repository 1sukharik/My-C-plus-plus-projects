#include "index.h"

std::string Index::GetPathInString(std::string a) {
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

int Index::GetNumberOfFiles(std::string a) {
  std::string result;
  int count = 0;
  for (auto& u : a) {

    if (u == ' ') {
      count++;
    } else {
      if (count == 1) {
        result += u;
      }
    }
  }
  return std::stoi(result);

}
std::string Index::GetRestOfString(std::string a) {
  std::string result;
  int count = 0;
  for (auto& u : a) {

    if (count >= 2) {
      result += u;
    }
    if (u == ' ') {
      count++;
    }

  }
  return result;
}
std::string Index::GetKWordInString(std::string a, int n) {
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
std::string Index::GetNumbersOfLines(std::string a, std::string b) {
  std::string result = "";
  std::set<int> res;
  for (int i = 0; i < std::stoi(GetKWordInString(a, 4)); i++) {
    res.insert(std::stoi(GetKWordInString(a, 4 + i + 1)));
  }
  for (int i = 0; i < std::stoi(GetKWordInString(b, 4)); i++) {
    res.insert(std::stoi(GetKWordInString(b, 4 + i + 1)));
  }
  int t = 0;
  for (auto& u : res) {
    t++;
    result += std::to_string(u);
    if (t < res.size()) {
      result += " ";
    }
  }
  return result;

}
void Index::CopyFile(std::string to, std::string from) {
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
void Index::MergeIndexes(std::string first_index, std::string second_index, int regime) {
  std::string name_of_help_index = GetPathInString(first_index) + "\\index_to_help.txt";
  CopyFile(name_of_help_index, first_index);
  std::fstream MergeTo(first_index, std::ios::out);
  std::fstream MergeFrom1(second_index, std::ios::in);
  std::fstream MergeFrom2(name_of_help_index, std::ios::in);
  std::string first, second;

  if (std::getline(MergeFrom1, first)) {
    if (first == "") {
      return;
    }
    if (std::getline(MergeFrom2, second)) {
      if (second == "") {
        return;
      }
      while (true) {
        if (GetKWordInString(first, 1) < GetKWordInString(second, 1)) {
          MergeTo << first << std::endl;
          std::string first_ = GetKWordInString(first, 1), second_ = GetKWordInString(second, 1);
          if (!std::getline(MergeFrom1, first)) {
            if (second_ != first_) {
              MergeTo << second << std::endl;
            }
            while (std::getline(MergeFrom2, second)) {
              if (second_ != first_) {
                MergeTo << second << std::endl;
              }
            }
            break;
          }
        } else if (GetKWordInString(first, 1) > GetKWordInString(second, 1)) {
          MergeTo << second << std::endl;
          std::string first_ = first, second_ = second;
          if (!std::getline(MergeFrom2, second)) {
            if (second_ != first_) {
              MergeTo << first << std::endl;
            }
            while (std::getline(MergeFrom1, first)) {
              if (second_ != first_) {
                MergeTo << first << std::endl;
              }
            }
            break;
          }
        } else {
          if (regime) {
            MergeTo << GetKWordInString(first, 1) << " "
                    << std::to_string(GetNumberOfFiles(first) + GetNumberOfFiles(second)) << " "
                    << GetKWordInString(first, 3) << " "
                    << std::to_string(std::stoi(GetKWordInString(first, 4)) + std::stoi(GetKWordInString(second, 4)))
                    << " "
                    << GetNumbersOfLines(first, second) << std::endl;
          } else {
            MergeTo << GetKWordInString(first, 1) << " "
                    << std::to_string(GetNumberOfFiles(first) + GetNumberOfFiles(second)) << " "
                    << GetRestOfString(first) << " " << GetRestOfString(second) << std::endl;
          }
          std::string first_ = GetKWordInString(first, 1), second_ = GetKWordInString(second, 1);
          if (!std::getline(MergeFrom2, second)) {
            if (second_ != first_) {
              MergeTo << first << std::endl;
            }
            while (std::getline(MergeFrom1, first)) {
              if (second_ != first_) {
                MergeTo << first << std::endl;
              }
            }
            break;
          }

          if (!std::getline(MergeFrom1, first)) {
            if (second_ != first_) {
              MergeTo << second << std::endl;
            }
            while (std::getline(MergeFrom2, second)) {
              if (second_ != first_) {
                MergeTo << second << std::endl;
              }
            }
            break;
          }

        }

      }
    } else {
      MergeTo << first << std::endl;
      while (std::getline(MergeFrom1, first)) {
        MergeTo << first << std::endl;
      }
    }
  } else {
    while (std::getline(MergeFrom2, second)) {
      MergeTo << second << std::endl;
    }
  }
  MergeTo.close();
  MergeFrom1.close();
  MergeFrom2.close();
  std::filesystem::remove(name_of_help_index);

}
