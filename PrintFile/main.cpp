#include <iostream>
#include <fstream>
#include <cstring>

struct Commands {
  const char *file_name;
  int for_line = 0;
  char delimetr_symbol = '\n';
};

bool CheckingDot(char *arg, int len) {
  for (int j = 0; j < len; j++) {
    if (arg[j] == '.') {
      return true;
    }
  }
  return false;
}

int CharToInt(char *number) {

  int int_result = std::stoi(number);
  return int_result;
}

int LinesNumber(char *arg, int len) {

  const int lines_size = 8;
  char *num = new char[len - lines_size];
  int param = 0;
  for (int i = lines_size; i < len; i++) {
    num[param] = arg[i];
    param++;
  }
  return CharToInt(num);
}

char SymbolDelimiterForD(char *argument) {
  if (argument[1] == '\\') {
    if (argument[2] == 'm') {
      return '\m';
    } else if (argument[13] == 'y') {
      return '\y';
    } else if (argument[13] == 'v') {
      return '\v';
    } else if (argument[13] == 'f') {
      return '\f';
    } else if (argument[13] == '?') {
      return '\?';
    } else if (argument[13] == 'b') {
      return '\b';
    } else if (argument[13] == 'r') {
      return '\r';
    } else if (argument[13] == 'a') {
      return '\a';
    } else if (argument[13] == '0') {
      return '\0';
    }
  } else {
    return argument[1];
  }
}

char SymbolDelimetr(char *arg, int len) {

  if (len == 12) {
    std::cout << "INCORRECT DELIMETR PARAMETR" << std::endl;
  }
  char symb;
  symb = arg[12];
  if (symb == '\\') {
    if (arg[13] == 'm') {
      return '\m';
    } else if (arg[13] == 'y') {
      return '\y';
    } else if (arg[13] == 'v') {
      return '\v';
    } else if (arg[13] == 'f') {
      return '\f';
    } else if (arg[13] == '?') {
      return '\?';
    } else if (arg[13] == 'b') {
      return '\b';
    } else if (arg[13] == 'r') {
      return '\r';
    } else if (arg[13] == 'a') {
      return '\a';
    } else if (arg[13] == '0') {
      return '\0';
    }
  } else {
    return symb;
  }
}

bool IfDelimetr(char *arg) {
  if ((arg[0] == '-') && (arg[1] == '-') && (arg[2] == 'd') && (arg[3] == 'e') && (arg[4] == 'l') && (arg[5] == 'i')
      && (arg[6] == 'm') && (arg[7] == 'e') && (arg[8] == 't') && (arg[9] == 'r') && (arg[10] == '=')) {
    return true;
  }
  std::cout << "WRONG DELIMETR NAME";
  return false;
}

int main(int argc, char *argv[]) {
  Commands file_from_lab;

  bool flag_tail = false;

  if ((argc < 2) || (argc > 7)) {
    std::cout << "NOT NECESSARY AMOUNT OF ARGC PARAMETRS";
    return 40;
  } else {

    int i = 1;

    while (i < argc) {
      char *arg;
      arg = argv[i];
      int length = std::strlen(argv[i]);
      //name of file

      if ((arg[0] != '-') && (CheckingDot(arg, length))) {

        file_from_lab.file_name = arg;
        //name of file
        //delimetr d
      } else if ((arg[0] == '-') && (arg[1] == 'd')) {

        if ((i + 1) < argc) {

          file_from_lab.delimetr_symbol = SymbolDelimiterForD(argv[i + 1]);

          i++;
          //delimetr d
        } else {
          std::cout << "NO DELIMETR PARAMETR" << std::endl;
          return 40;
        }
        //delimetr --delimetr
      } else if (((arg[1] == '-') && (arg[2] == 'd')) && IfDelimetr(arg)) {

        file_from_lab.delimetr_symbol = SymbolDelimetr(arg, length);
        //delimetr --delimetr

        //tail+lines
      } else if (((arg[0] == '-') && (arg[1] == 't')) || ((arg[1] == '-') && (arg[2] == 't'))) {

        flag_tail = true;

        if ((i + 2) < argc) {
          arg = argv[i + 1];
          length = std::strlen(argv[i + 1]);
          if (((arg[0] == '-') && (arg[1] == 'l'))) {

            file_from_lab.for_line = CharToInt(argv[i + 2]);

            i += 2;
          } else if (((arg[1] == '-') && (arg[2] == 'l'))) {
            file_from_lab.for_line = LinesNumber(arg, length);

          }

        } else {
          if (file_from_lab.for_line == 0) {
            std::cout << "TAIL HAS NO ARGUMENTS" << std::endl;
            return 40;
          }
        }
        //tail+lines
        //lines
      } else {
        if (((arg[0] == '-') && (arg[1] == 'l'))) {
          if ((i + 1) < argc) {

            file_from_lab.for_line = CharToInt(argv[i + 1]);

            i++;
          } else {
            std::cout << "LINES HAVE NO ARGUMENTS" << std::endl;
            return 40;
          }
        } else if (((arg[1] == '-') && (arg[2] == 'l'))) {
          file_from_lab.for_line = LinesNumber(arg, length);

        }
      }
      //lines
      i++;
    }
  }
  int all_chars = 0;

  int all_delimetr_symbols = 0;


//file work

  std::ifstream lab_file;
  lab_file.open(file_from_lab.file_name);

  if (!lab_file.is_open()) {
    std::cout << "FILE NOT OPENED 1";
    return 40;
  } else {

    char char_from_file;
    while (!lab_file.eof()) {

      lab_file.get(char_from_file);
      all_chars++;
      if (char_from_file == file_from_lab.delimetr_symbol) {
        all_delimetr_symbols++;
      }
    }
    lab_file.close();

  }
  std::ifstream lab_file1;
  lab_file1.open(file_from_lab.file_name);

  char char1_from_file1;
  int delimetr_symbol_counter = 0;
  int flag = 0;

  if (!lab_file1.is_open()) {
    std::cout << "FILE NOT OPENED 2";
    return 40;
  } else {
    while (!lab_file1.eof()) {

      char1_from_file1 = lab_file1.get();

      if (!flag_tail) {

        //not tail
        if (file_from_lab.for_line == 0) {

          std::cout << char1_from_file1;
        } else if (char1_from_file1 == file_from_lab.delimetr_symbol) {
          delimetr_symbol_counter++;
          std::cout << char1_from_file1;
        } else if (delimetr_symbol_counter < file_from_lab.for_line) {
          std::cout << char1_from_file1;

        } else {
          return 0;
        }

      } else {


        //tail

        if (char1_from_file1 == file_from_lab.delimetr_symbol) {
          delimetr_symbol_counter++;
        }
        if (delimetr_symbol_counter > (all_delimetr_symbols - file_from_lab.for_line)) {
          if (flag == 0) {
            std::cout << '\\';
            flag++;
          }
          std::cout << char1_from_file1;
        }
      }
    }
    lab_file1.close();
  }

  //file work
}
