

#ifndef LAB7__ARGHEAD_H_
#define LAB7__ARGHEAD_H_

#pragma once
#include "iostream"
#include "string"
#include "vector"

namespace ArgumentParser {

class AllArguments {
 public:
  std::string long_name;
  char short_name = ' ';
  bool is_default_value = false;
  bool is_store_value = false;
  std::string descript;
  AllArguments() {

  }

  AllArguments(const std::string& param)
      : long_name{param} {}
  AllArguments(char p, const std::string& param)
      : long_name{param}, short_name{p} {}

};

class FlagArgument : public AllArguments {
  friend class AllArguments;
 public:
  std::string tip = "flag";
  FlagArgument() {}
  bool value_we_have = false;
  bool *value_for_storevalue;
  FlagArgument(const std::string& param) : AllArguments(param) {}
  FlagArgument(char p, const std::string& param) : AllArguments(p, param) {}
  void Default(bool value) {
    value_we_have = value;
    is_default_value = true;
  }
  void StoreValue(bool& value) {
    value_for_storevalue = &value;
    is_store_value = true;
    value = value_we_have;

  }

};

class StringArgument : public AllArguments {
  friend class AllArguments;
 public:
  std::string tip = "str";
  std::string value_we_have;
  std::string *value_for_storevalue;
  bool is_multi_value = false;
  size_t amount_of_min_arguments = 0;
  StringArgument() {}

  StringArgument(const std::string& param) : AllArguments(param) {}
  StringArgument(char p, const std::string& param) : AllArguments(p, param) {}
  void Default(const std::string& value) {
    is_default_value = true;
    value_we_have = value;
  }
  void StoreValue(std::string& value) {
    value_for_storevalue = &value;
    is_store_value = true;
    value = value_we_have;

  }
  StringArgument& MultiValue(size_t min_count) {
    amount_of_min_arguments = min_count;
    is_multi_value = true;
    return *this;

  }

};

class IntArgument : public AllArguments {
  friend class AllArguments;
 public:
  std::string tip = "int";
  std::vector<int> *value_for_storevalue;
  bool is_positional = false;
  bool is_multi_value = false;
  bool is_store_values = false;
  bool empty_multi;
  size_t amount_of_min_arguments = 0;
  std::vector<int> values_we_have;
  IntArgument() {}

  IntArgument(const std::string& param) : AllArguments(param) {}
  IntArgument(char p, const std::string& param) : AllArguments(p, param) {}
  void StoreValues(std::vector<int>& values) {
    value_for_storevalue = &values;
    is_store_values = true;
    values = values_we_have;

  }
  IntArgument& MultiValue() {
    empty_multi = true;
    is_multi_value = true;
    return *this;
  }
  IntArgument& MultiValue(size_t min_amount) {
    is_multi_value = true;
    amount_of_min_arguments = min_amount;
    return *this;
  }
  IntArgument& Positional() {
    is_positional = true;
    return *this;

  }

};

class ArgParser{
 public:
  std::string long_name_help;
  char short_name_help_argument;
  std::string description_help_argument;
  bool is_help_argument = false;

  ArgParser(const std::string& s);

  std::vector<AllArguments *> all_args;

  bool Parse(const std::vector<std::string>& all_commands);
  bool Parse(int argc, char **argv);
  std::string parser_name;

  StringArgument& AddStringArgument(const std::string& longer, const std::string& description = "");
  StringArgument& AddStringArgument(char shorter, const std::string& longer, const std::string& description = "");

  const std::string& GetStringValue(const std::string& s, size_t index = 0);

  IntArgument& AddIntArgument(const std::string& longer, const std::string& description = "");
  IntArgument& AddIntArgument(char shorter, const std::string& longer, const std::string& description = "");

  int GetIntValue(const std::string& s, size_t index = 0);

  FlagArgument& AddFlag(const std::string& longer, const std::string& description = "");
  FlagArgument& AddFlag(char shorter, const std::string& longer, const std::string& description = "");

  bool GetFlag(const std::string& s);

  bool Help();
  void AddHelp(char short_name, const std::string& long_name, const std::string& description);
  const std::string HelpDescription();
  ~ArgParser() {
    for (int i = 0; i < all_args.size(); i++) {
      delete[] all_args[i];
    }
  }
};

}

#endif //LAB7__ARGHEAD_H_
