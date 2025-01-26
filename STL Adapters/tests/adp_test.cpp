#include <gtest/gtest.h>
#include "../lib/adpcont.h"

TEST(OneAdaptor, Transform
) {
  std::vector<int> v = {1, 2, 3, 4, 5, 6};
  std::vector<int> ans = {1, 4, 9, 16, 25, 36};
  std::vector<int> v_try = v | transform{[](int i) { return i * i; }};

  ASSERT_EQ(ans[0], v_try[0]
  );
}

TEST(OneAdaptor, Filter
) {
  std::vector<int> v = {1, 2, 3, 4, 5, 6};
  std::vector<int> ans = {1, 3, 5};
  std::vector<int> v_try = v | filter{[](int i) { return i % 2 == 1; }};

  ASSERT_EQ(ans[0], v_try[0]
  );
}

TEST(OneAdaptor, Take
) {
  std::vector<int> v = {1, 2, 3, 4, 5, 6};
  std::vector<int> ans = {1, 2, 3, 4};
  std::vector<int> v_try = v | take(4);

  ASSERT_EQ(ans[0], v_try[0]
  );
}

TEST(OneAdaptor, Drop
) {
  std::vector<int> v = {1, 2, 3, 4, 5, 6};
  std::vector<int> ans = {5, 6};
  std::vector<int> v_try = v | drop(4);

  ASSERT_EQ(ans[0], v_try[0]
  );
}

TEST(OneAdaptor, Reverse
) {
  std::vector<int> v = {1, 2, 3, 4, 5, 6};
  std::vector<int> ans = {6, 5, 4, 3, 2, 1};
  std::vector<int> v_try = v | reverse();

  ASSERT_EQ(ans[0], v_try[0]
  );
}

TEST(OneAdaptor, Keys
) {
  std::map<int, int> v = {{1, 5}, {2, 4}, {3, 3}, {4, 2}, {5, 1}};
  std::map<int, int> ans = {{1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}};
  auto v_try = v | keys();

  ASSERT_EQ(ans[0], v_try[0]
  );
}

TEST(OneAdaptor, Values) {
  std::map<int, int> v = {{1, 5}, {2, 4}, {3, 3}, {4, 2}, {5, 1}};
  std::map<int, int> ans = {{5, 0}, {4, 0}, {3, 0}, {2, 0}, {1, 0}};
  auto v_try = v | values();

  ASSERT_EQ(ans[0], v_try[0]);
}

TEST(Conveir, First
) {
  std::vector<int> v = {1, 2, 3, 4, 5, 6};
  std::vector<int> v_try;
  std::vector<int> ans = {1, 9, 25};

  for (int i : v | filter([](int i) { return i % 2; }) | transform([](int i) { return i * i; })) v_try.push_back(i);

  ASSERT_EQ(ans[0], v_try[0]
  );
}
