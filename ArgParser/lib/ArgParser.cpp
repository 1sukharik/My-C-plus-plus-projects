#include "ArgParser.h"
using namespace ArgumentParser;
ArgParser::ArgParser(const std::string& s) {
  parser_name = s;

}

bool ArgParser::Parse(const std::vector<std::string>& all_commands) {
  if (all_commands.size() == 1) {
    if (!all_args.empty() && reinterpret_cast<StringArgument&>(all_args[0]).tip == "str"
        && (!reinterpret_cast<StringArgument&>(all_args[0]).long_name.empty()
            || (reinterpret_cast<StringArgument&>(all_args[0]).short_name != ' '))
        && (!reinterpret_cast<StringArgument&>(all_args[0]).is_default_value)) {
      return false;
    }
    return true;
  }

  for (int i = 0; i < all_commands.size(); i++) {
    if (all_commands[i][1] == '-') {
      if (is_help_argument) {
        std::string command;
        for (int k = 2; k < all_commands[i].size(); k++) {
          command.push_back(all_commands[i][k]);
          if (command == long_name_help) {
            return true;
          }

        }

      }
      if (!all_args.empty() && reinterpret_cast<StringArgument&>(all_args[i]).tip == "str") {
        std::string command;
        std::string value_of_command;
        bool flag = false;
        for (int k = 2; k < all_commands[i].size(); k++) {
          if (flag) {
            value_of_command.push_back(all_commands[i][k]);
          }
          if (all_commands[i][k] == '=') {
            flag = true;
          }
          if (!flag) {
            command.push_back(all_commands[i][k]);
          }
        }
        if (i == all_commands.size() - 1) {
          if (reinterpret_cast<StringArgument&>(all_args[0]).is_multi_value) {
            int k = 0;
            int k1 = 0;
            for (int t = 0; t < all_args.size(); t++) {
              if (reinterpret_cast<StringArgument&>(all_args[t]).tip == "str") {
                k = reinterpret_cast<StringArgument&>(all_args[t]).value_we_have.size();
              } else if (reinterpret_cast<IntArgument&>(all_args[t]).tip == "int") {
                k1 = reinterpret_cast<IntArgument&>(all_args[t]).amount_of_min_arguments;

              }
            }
            if (k < k1) {
              return false;
            }
          }
        }
        for (int j = 0; j < all_args.size(); j++) {
          if (reinterpret_cast<StringArgument&>(all_args[j]).tip == "str"
              && reinterpret_cast<StringArgument&>(all_args[j]).long_name == command) {
            reinterpret_cast<StringArgument&>(all_args[j]).value_we_have = value_of_command;
            if (reinterpret_cast<StringArgument&>(all_args[j]).is_store_value) {
              *reinterpret_cast<StringArgument&>(all_args[j]).value_for_storevalue = value_of_command;
            }
          }
        }

      } else if (!all_args.empty() && reinterpret_cast<IntArgument&>(all_args[i]).tip == "int") {

        std::string command;
        std::string value_of_command;
        bool flag = false;

        for (int k = 2; k < all_commands[i].size(); k++) {
          if (flag) {
            value_of_command.push_back(all_commands[i][k]);
          }
          if (all_commands[i][k] == '=') {
            flag = true;
          }
          if (!flag) {
            command.push_back(all_commands[i][k]);
          }
        }

        if (i == all_commands.size() - 1) {
          if (reinterpret_cast<IntArgument&>(all_args[0]).is_multi_value) {
            if ((!reinterpret_cast<IntArgument&>(all_args[0]).empty_multi)
                && (reinterpret_cast<IntArgument&>(all_args[0]).values_we_have.size())
                    < reinterpret_cast<IntArgument&>(all_args[0]).amount_of_min_arguments) {
              return false;
            }
          }
        }
        for (int j = 0; j < all_args.size(); j++) {
          if (reinterpret_cast<IntArgument&>(all_args[j]).tip == "int"
              && reinterpret_cast<IntArgument&>(all_args[j]).long_name == command) {
            reinterpret_cast<IntArgument&>(all_args[j]).values_we_have.push_back(std::stoi(value_of_command));
            if (reinterpret_cast<IntArgument&>(all_args[j]).is_store_values) {
              reinterpret_cast<IntArgument&>(all_args[j]).value_for_storevalue->push_back(std::stoi(value_of_command));
            }
          }
        }

      } else if (!all_args.empty() && reinterpret_cast<FlagArgument&>(all_args[i]).tip == "flag") {
        std::string command;
        std::string value_of_command;
        bool flag = false;
        for (int k = 2; k < all_commands[i].size(); k++) {
          command.push_back(all_commands[i][k]);
        }
        for (int j = 0; j < all_args.size(); j++) {
          if (reinterpret_cast<FlagArgument&>(all_args[j]).tip == "flag"
              && reinterpret_cast<FlagArgument&>(all_args[j]).long_name == command) {
            reinterpret_cast<FlagArgument&>(all_args[j]).value_we_have = true;
          }
        }

      }

    } else if (all_commands[i][0] == '-') {
      if (!all_args.empty()) {

        std::string value_of_command;
        char small_command = all_commands[i][1];

        for (int k = 3; k < all_commands[i].size(); k++) {
          value_of_command.push_back(all_commands[i][k]);
        }
        for (int j = 0; j < all_args.size(); j++) {
          if (reinterpret_cast<StringArgument&>(all_args[j]).short_name == small_command) {
            reinterpret_cast<StringArgument&>(all_args[j]).value_we_have = value_of_command;
          }

        }
      } else if (!all_args.empty()) {

      } else if (!all_args.empty()) {
        for (int k = 1; k < all_commands[i].size(); k++) {
          for (int y = 0; y < all_args.size(); y++) {
            if (reinterpret_cast<FlagArgument&>(all_args[y]).tip == "flag"
                && reinterpret_cast<FlagArgument&>(all_args[y]).short_name == all_commands[i][k]) {
              reinterpret_cast<FlagArgument&>(all_args[y]).value_we_have = true;
              if (reinterpret_cast<FlagArgument&>(all_args[y]).is_store_value) {
                *reinterpret_cast<FlagArgument&>(all_args[y]).value_for_storevalue = true;
              }
            }
          }
        }

      }

    } else if (!all_args.empty() && reinterpret_cast<IntArgument&>(all_args[0]).tip == "int" && i >= 1) {
      std::string command = reinterpret_cast<IntArgument&>(all_args[0]).long_name;
      std::string value_of_command;
      if (reinterpret_cast<IntArgument&>(all_args[0]).is_positional) {
        for (int k = 0; k < all_commands[i].size(); k++) {
          value_of_command.push_back(all_commands[i][k]);
        }
      }
      if (i == all_commands.size() - 1) {
        if (reinterpret_cast<IntArgument&>(all_args[0]).is_multi_value) {
          if ((!reinterpret_cast<IntArgument&>(all_args[0]).empty_multi)
              && (reinterpret_cast<IntArgument&>(all_args[0]).values_we_have.size())
                  < reinterpret_cast<IntArgument&>(all_args[0]).amount_of_min_arguments) {
            return false;
          }
        }
      }
      for (int j = 0; j < all_args.size(); j++) {
        if (reinterpret_cast<IntArgument&>(all_args[j]).long_name == command
            && reinterpret_cast<IntArgument&>(all_args[j]).tip == "int") {
          reinterpret_cast<IntArgument&>(all_args[j]).values_we_have.push_back(std::stoi(value_of_command));
          if (reinterpret_cast<IntArgument&>(all_args[j]).is_store_values) {
            reinterpret_cast<IntArgument&>(all_args[j]).value_for_storevalue->push_back(std::stoi(value_of_command));
          }
        }
      }

    }
  }
  return true;

}

StringArgument& ArgumentParser::ArgParser::AddStringArgument(const std::string& longer,
                                                             const std::string& description) {
  all_args.push_back(new StringArgument(longer));

  StringArgument& fl = *reinterpret_cast<StringArgument *>(all_args.back());

  return fl;

}
StringArgument& ArgumentParser::ArgParser::AddStringArgument(char short_name,
                                                             const std::string& longer,
                                                             const std::string& description) {
  all_args.push_back(new StringArgument(short_name, longer));

  StringArgument& fl = *reinterpret_cast<StringArgument *>(all_args.back());

  return fl;
}
IntArgument& ArgumentParser::ArgParser::AddIntArgument(const std::string& longer,
                                                       const std::string& description) {
  all_args.push_back(new IntArgument(longer));

  IntArgument& fl = *reinterpret_cast<IntArgument *>(all_args.back());

  return fl;
}
IntArgument& ArgumentParser::ArgParser::AddIntArgument(char shorter,
                                                       const std::string& longer,
                                                       const std::string& description) {
  all_args.push_back(new IntArgument(shorter, longer));

  IntArgument& fl = *reinterpret_cast<IntArgument *>(all_args.back());

  return fl;


//  IntArgument *x = new IntArgument(shorter, longer);
//  x->descript = description;
//  int_arguments.push_back(x);
//  return *x;
}

const std::string& ArgumentParser::ArgParser::GetStringValue(const std::string& s, size_t index) {
  for (int i = 0; i < all_args.size(); i++) {
    //StringArgument& arg = *reinterpret_cast<StringArgument*>(all_args[i]);
    if (reinterpret_cast<StringArgument&>(all_args[i]).tip == "str"
        && reinterpret_cast<StringArgument&>(all_args[i]).long_name == s) {
      return reinterpret_cast<StringArgument*>(all_args[i])->value_we_have;
    }
  }
  return "";

}

int ArgumentParser::ArgParser::GetIntValue(const std::string& s, size_t index) {
  for (int i = 0; i < all_args.size(); i++) {
    if (reinterpret_cast<IntArgument&>(all_args[i]).tip == "int"
        && reinterpret_cast<IntArgument&>(all_args[i]).long_name == s) {
      if (reinterpret_cast<IntArgument&>(all_args[i]).is_multi_value == true) {
        return reinterpret_cast<IntArgument&>(all_args[i]).values_we_have[index];
      } else {
        return reinterpret_cast<IntArgument&>(all_args[i]).values_we_have[0];
      }
    }
  }
  return 0;
}
FlagArgument& ArgumentParser::ArgParser::AddFlag(const std::string& longer,
                                                 const std::string& description) {
  all_args.push_back(new FlagArgument(longer));

  all_args[all_args.size() - 1]->descript = description;
  FlagArgument& fl = *reinterpret_cast<FlagArgument *>(all_args.back());
//  flag_arguments.push_back(x);
  return fl;

}
FlagArgument& ArgumentParser::ArgParser::AddFlag(char shorter,
                                                 const std::string& longer,

                                                 const std::string& description) {
  all_args.push_back(new FlagArgument(shorter, longer));

  all_args[all_args.size() - 1]->descript = description;
  FlagArgument& fl = *reinterpret_cast<FlagArgument *>(all_args.back());

  return fl;
}

bool ArgumentParser::ArgParser::GetFlag(const std::string& s) {
  for (int i = 0; i < all_args.size(); i++) {
    if (reinterpret_cast<FlagArgument&>(all_args[i]).tip == "flag"
        && reinterpret_cast<FlagArgument&>(all_args[i]).long_name == s) {
      return reinterpret_cast<FlagArgument&>(all_args[i]).value_we_have;
    }
  }
  return false;

}

void ArgumentParser::ArgParser::AddHelp(char short_name, const std::string& long_name, const std::string& description) {
  is_help_argument = true;
  long_name_help = long_name;
  short_name_help_argument = short_name;
  description_help_argument = description;

}
bool ArgumentParser::ArgParser::Help() {
  if (is_help_argument) {
    return true;
  }
  return false;

}
const std::string ArgumentParser::ArgParser::HelpDescription() {
  std::string ans = "";
  ans = ans + "Parser name is: " + '\n';
  ans = ans + "INT argument:" + '\n';

  for (int i = 0; i < all_args.size(); i++) {
    if (reinterpret_cast<IntArgument&>(all_args[i]).tip == "int") {
      ans = ans + "Long name: " + reinterpret_cast<IntArgument&>(all_args[i]).long_name + " Short name: "
          + reinterpret_cast<IntArgument&>(all_args[i]).short_name
          + " Default value: " + (reinterpret_cast<IntArgument&>(all_args[i]).is_default_value ? "true" : "false")
          + " Desription: "
          + reinterpret_cast<IntArgument&>(all_args[i]).descript + '\n';

    }
  }
  ans = ans + "STRING argument:" + '\n';

  for (int i = 0; i < all_args.size(); i++) {
    if (reinterpret_cast<StringArgument&>(all_args[i]).tip == "str") {
      ans = ans + "Long name: " + reinterpret_cast<StringArgument&>(all_args[i]).long_name + " Short name: "
          + reinterpret_cast<StringArgument&>(all_args[i]).short_name
          + " Default value: " + (reinterpret_cast<StringArgument&>(all_args[i]).is_default_value ? "true" : "false")
          + " Desription: "
          + reinterpret_cast<StringArgument&>(all_args[i]).descript + '\n';

    }
  }
  ans = ans + "FLAG argument:" + '\n';

  for (int i = 0; i < all_args.size(); i++) {
    if (reinterpret_cast<IntArgument&>(all_args[i]).tip == "int") {
      ans = ans + "Long name: " + reinterpret_cast<FlagArgument&>(all_args[i]).long_name + " Short name: "
          + reinterpret_cast<FlagArgument&>(all_args[i]).short_name
          + " Default value: " + (reinterpret_cast<FlagArgument&>(all_args[i]).is_default_value ? "true" : "false")
          + " Desription: "
          + reinterpret_cast<FlagArgument&>(all_args[i]).descript + '\n';

      ans = ans + "HELP argumen:" + '\n';
      ans = ans + "Is help using: " + (is_help_argument ? "true" : "false");

      return ans;

    }
  }
}
