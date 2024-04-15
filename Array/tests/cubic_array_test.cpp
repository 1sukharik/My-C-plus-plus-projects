#include <lib/CubicArray.h>
#include <gtest/gtest.h>
#include <sstream>



TEST(CubicArrayTestSuite, EndOfTheArrayArray) {
  SeventeenBitClass arr = SeventeenBitClass::make_array(4, 3, 2);
  arr[3][2][1] = 131071;
  SeventeenBitClass arr1 = SeventeenBitClass::make_array(4, 3, 2);
  arr1[3][2][1] = 131071;
  ASSERT_EQ(arr, arr1);
}

TEST(CubicArrayTestSuite, EndOfTheArrayElement) {
  SeventeenBitClass arr = SeventeenBitClass::make_array(4, 3, 2);
  arr[3][2][1] = 131071;
  SeventeenBitClass arr1 = SeventeenBitClass::make_array(4, 3, 2);
  arr1[3][2][1] = 131071;
  ASSERT_EQ(arr[3][2][1], arr[3][2][1]);
}

TEST(CubicArrayTestSuite, EqualityOfArrays) {
  SeventeenBitClass arr = SeventeenBitClass::make_array(4, 3, 2);
  arr[2][2][1] = 131071;
  SeventeenBitClass arr1 = SeventeenBitClass::make_array(4, 3, 2);
  arr1[2][2][1] = 131071;
  ASSERT_EQ(arr, arr1);
}

TEST(CubicArrayTestSuite, EqualityOfElements) {
  SeventeenBitClass arr = SeventeenBitClass::make_array(4, 3, 2);
  arr[3][2][1] = 131071;
  SeventeenBitClass arr1 = SeventeenBitClass::make_array(4, 3, 2);
  arr1[3][2][1] = 131071;
  ASSERT_EQ(arr[3][2][1], arr1[3][2][1]);
}

TEST(CubicArrayTestSuite, AdditionElement) {
  SeventeenBitClass arr = SeventeenBitClass::make_array(4, 3, 2);
  arr[1][1][1] = 1;
  SeventeenBitClass arr1 = SeventeenBitClass::make_array(4, 3, 2);
  arr1[1][1][1] = 2;
  SeventeenBitClass arr2 = arr1 + arr;
  SeventeenBitClass arr3 = SeventeenBitClass::make_array(4, 3, 2);
  arr3[1][1][1] = 3;
  ASSERT_EQ(arr2[1][1][1], arr3[1][1][1]);
}

TEST(CubicArrayTestSuite, AdditionArray) {
  SeventeenBitClass arr = SeventeenBitClass::make_array(4, 3, 2);
  arr[1][1][1] = 1;
  SeventeenBitClass arr1 = SeventeenBitClass::make_array(4, 3, 2);
  arr1[1][1][1] = 2;
  SeventeenBitClass arr2 = arr1 + arr;
  SeventeenBitClass arr3 = SeventeenBitClass::make_array(4, 3, 2);
  arr3[1][1][1] = 3;
  ASSERT_EQ(arr2, arr3);
}

TEST(CubicArrayTestSuite, SubstractionElement) {
  SeventeenBitClass arr = SeventeenBitClass::make_array(4, 3, 2);
  arr[1][1][1] = 1;
  SeventeenBitClass arr1 = SeventeenBitClass::make_array(4, 3, 2);
  arr1[1][1][1] = 2;
  SeventeenBitClass arr3 = arr1 - arr;
  SeventeenBitClass arr4 = SeventeenBitClass::make_array(4, 3, 2);
  arr4[1][1][1] = 1;
  ASSERT_EQ(arr3[1][1][1], arr4[1][1][1]);
}

TEST(CubicArrayTestSuite, SubstractionArray) {
  SeventeenBitClass arr = SeventeenBitClass::make_array(4, 3, 2);
  arr[1][1][1] = 1;
  SeventeenBitClass arr1 = SeventeenBitClass::make_array(4, 3, 2);
  arr1[1][1][1] = 2;
  SeventeenBitClass arr3 = arr1 - arr;
  SeventeenBitClass arr4 = SeventeenBitClass::make_array(4, 3, 2);
  arr4[1][1][1] = 1;
  ASSERT_EQ(arr3[1][1][1], arr4[1][1][1]);
}

TEST(CubicArrayTestSuite, PermutElement) {
  SeventeenBitClass arr = SeventeenBitClass::make_array(4, 3, 2);
  arr[1][1][1] = 1;

  SeventeenBitClass arr2 = arr * 5;
  SeventeenBitClass arr3 = SeventeenBitClass::make_array(4, 3, 2);
  arr3[1][1][1] = 5;
  ASSERT_EQ(arr2[1][1][1], arr3[1][1][1]);
}

TEST(CubicArrayTestSuite, PermutArray) {
  SeventeenBitClass arr = SeventeenBitClass::make_array(4, 3, 2);
  arr[1][1][1] = 1;

  SeventeenBitClass arr2 = arr * 5;
  SeventeenBitClass arr3 = SeventeenBitClass::make_array(4, 3, 2);
  arr3[1][1][1] = 5;
  ASSERT_EQ(arr2, arr3);
}

TEST(CubicArrayTestSuite, DifficultDuncElement) {
  SeventeenBitClass arr = SeventeenBitClass::make_array(4, 3, 2);
  arr[1][1][1] = 1;

  SeventeenBitClass arr2 = arr * 5;
  SeventeenBitClass arr3 = arr2 + arr;
  SeventeenBitClass arr4 = SeventeenBitClass::make_array(4, 3, 2);
  arr4[1][1][1] = 6;
  ASSERT_EQ(arr3[1][1][1], arr4[1][1][1]);
}

TEST(CubicArrayTestSuite, DifficultDuncArray) {
  SeventeenBitClass arr = SeventeenBitClass::make_array(4, 3, 2);
  arr[1][1][1] = 1;

  SeventeenBitClass arr2 = arr * 5;
  SeventeenBitClass arr3 = arr2 + arr;
  SeventeenBitClass arr4 = SeventeenBitClass::make_array(4, 3, 2);
  arr4[1][1][1] = 6;
  ASSERT_EQ(arr3[1][1][1], arr4[1][1][1]);
}

TEST(CubicArrayTestSuite, ZeroesElement) {
  SeventeenBitClass arr = SeventeenBitClass::make_array(4, 3, 2);
  arr[1][1][1] = 1;
  SeventeenBitClass arr2 = arr * 5;
  SeventeenBitClass arr3 = arr2 + arr;
  SeventeenBitClass arr4 = SeventeenBitClass::make_array(4, 3, 2);
  arr4[1][1][1] = 0;
  ASSERT_EQ(arr3[0][0][0], arr4[1][1][1]);
}

TEST(CubicArrayTestSuite, ZeroesArray) {
  SeventeenBitClass arr = SeventeenBitClass::make_array(4, 3, 2);
  arr[1][1][1] = 1;
  SeventeenBitClass arr2 = arr * 5;
  SeventeenBitClass arr3 = arr2 + arr;
  SeventeenBitClass arr4 = SeventeenBitClass::make_array(4, 3, 2);
  arr4[1][1][1] = 0;
  ASSERT_EQ(arr3[0][0][0], arr4[1][1][1]);
}
