#include <lib/CubicArray.h>

#include <iostream>

int main() {
  SeventeenBitClass arr = SeventeenBitClass::make_array(2, 2, 2);
  SeventeenBitClass arr1 = SeventeenBitClass::make_array(2, 2, 2);
  arr[0][0][0] = 1;
  arr1[0][0][0] = 1;

  SeventeenBitClass arr2 = arr * 5;

  std::cout << arr2[0][0][0];

  return 0;
}
