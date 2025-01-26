#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../index/lib/index.h"
#include "../query/lib/query.h"

TEST(Query, first_word_is_command) {
  Query q;
  std::vector<std::string> commands = {"OR", "AND", "one", "OR", "two"};
  std::string a = q.CheckQuery(5, commands);

  ASSERT_EQ(a, "FIRST MUST BE WORD, NOT COMMAND");

}

TEST(Query, two_command_in_a_row) {
  Query q;
  std::vector<std::string> commands = {"two", "AND", "OR", "two"};
  std::string a = q.CheckQuery(4, commands);

  ASSERT_EQ(a, "NO 2 COMMAND IN A ROW");

}

TEST(Query, wrong_writing_of_command) {
  Query q;
  std::vector<std::string> commands = {"two", "ANd", "two"};
  std::string a = q.CheckQuery(3, commands);

  ASSERT_EQ(a, "INCORRECT WRITING OF COMMAND");

}

TEST(Index, separators) {
  Index i;
  std::vector<char> separators = i.WhatSeparatorsExistVector();

  ASSERT_THAT(separators, ::testing::ElementsAreArray({'/', '.', ',', '!', '?', '\\', ';', '-', '<', '>', '$'}));

}
TEST(Index, correct_writing) {
  Index i;
  i.Parse(8,
          {"C:\\Users\\a8921\\CLionProjects\\OP2\\labwork11-1sukharik>", "index.exe", "-d",
           "C:\\Users\\a8921\\CLionProjects\\OP2\\labwork11-1sukharik\\test_txt", "-p",
           "C:\\Users\\a8921\\CLionProjects\\OP2\\labwork11-1sukharik", "-f", "my_index.txt"});
  std::string a;
  std::fstream File("C:\\Users\\a8921\\CLionProjects\\OP2\\labwork11-1sukharik\\my_index.txt");
  std::getline(File, a);
  File.close();

  ASSERT_EQ(a, "abc 1 C:\\Users\\a8921\\CLionProjects\\OP2\\labwork11-1sukharik\\test_txt\\test1.txt 1 2");

}
