#include <cstring>
#include "number.h"

const int size_of_int2023_t = 253;

void Summ(uint8_t *arr1, uint8_t *arr2, uint8_t *ans) {
  uint32_t sign_one = 0;
  for (int i = size_of_int2023_t - 1; i >= 0; i--) {
    ans[i] = arr1[i] + arr2[i] + sign_one;
    sign_one = ((arr1[i] + arr2[i] - 1) > ans[i]) ? 1 : 0;
  }
}

void MoveToLeftOnce(uint8_t *arr) {
  for (int i = 0; i < size_of_int2023_t - 1; i++) {
    int t = ((arr[i + 1] >> 7) & 1);
    arr[i] <<= 1;
    arr[i] |= t;
  }
  arr[252] <<= 1;
}

void Copy(uint8_t *arr1, uint8_t *arr2) {
  for (int i = 0; i < size_of_int2023_t; i++) {
    arr2[i] = arr1[i];
  }
}

void AddedCode(uint8_t *arr) {
  uint8_t reversed_arr[size_of_int2023_t]{0};
  for (int i = 0; i < size_of_int2023_t; i++) {
    arr[i] = ~arr[i];
  }

  uint8_t one[size_of_int2023_t]{0};
  one[size_of_int2023_t - 1] |= 1;
  Copy(arr, reversed_arr);

  Summ(reversed_arr, one, arr);

}

bool IsZero(uint8_t *arr) {
  int count = 0;
  for (int i = 0; i < 253; i++) {
    if (arr[i] == 0) {
      count++;
    }
  }
  if (count == 253) {
    return true;

  } else {
    return false;
  }

}

int2023_t from_int(int32_t i) {

  int2023_t int_2023;

  bool is_negative = false;
  if (i < 0) {
    i = -i;
    is_negative = true;
  }
  int m = size_of_int2023_t - 1;
  for (int j = 0; j < sizeof i; j++) {
    int_2023.num[m--] = (i & 0xFF);
    i >>= 8;
  }
  if (is_negative) {
    AddedCode(int_2023.num);
  }
  return int_2023;
}

int2023_t operator+(const int2023_t& lhs, const int2023_t& rhs) {
  int2023_t r = rhs, l = lhs, summ;
  Summ(l.num, r.num, summ.num);
  return summ;
}

int2023_t from_string(const char *buff) {
  int2023_t number;

  bool is_negative = false;
  int index_of_first_symbol = 0;
  if (buff[0] == '-') {
    is_negative = true;
    index_of_first_symbol = 1;
  }
  int2023_t k = from_int(1);
  int count = std::strlen(buff);
  for (int i = count - 1; i >= index_of_first_symbol; i--) {
    number = number + (k * from_int(buff[i] - '0'));
    k = k * from_int(10);
  }
  if (is_negative) {
    AddedCode(number.num);
  }
  return number;
}

int2023_t operator-(const int2023_t& lhs, const int2023_t& rhs) {
  int2023_t difference, lhs_2 = lhs, rhs_2 = rhs;
  AddedCode(rhs_2.num);
  difference = rhs_2 + lhs_2;
  return difference;
}

bool SecondNotBiggerThenFirst(int2023_t lhs, int2023_t rhs) {
  int2023_t result;
  if (((lhs.num[0] >> 7) & 1) == 0 and ((rhs.num[0] >> 7) & 1) == 1) {
    return true;
  } else if (((lhs.num[0] >> 7) & 1) == 1 and ((rhs.num[0] >> 7) & 1) == 0) {
    return false;
  } else {
    result = lhs - rhs;
    if (result == from_int(0)) {
      return true;
    }
    if (((result.num[0] >> 7) & 1) == 0) {
      return true;
    } else {
      return false;
    }
  }
}

int2023_t operator*(const int2023_t& lhs, const int2023_t& rhs) {
  int2023_t ans, copied_ans, second_num1 = lhs, multiplier_2 = rhs;

  for (int i = size_of_int2023_t - 1; i >= 0; i--) {
    for (int j = 0; j < 8; j++) {
      int t = ((multiplier_2.num[i] >> j) & 1);
      if (t == 1) {
        Summ(copied_ans.num, second_num1.num, ans.num);
        Copy(ans.num, copied_ans.num);
      }
      MoveToLeftOnce(second_num1.num);
    }
  }

  return ans;
}

bool operator==(const int2023_t& lhs, const int2023_t& rhs) {
  int2023_t lhs_2 = lhs, rhs_2 = rhs, rez = lhs_2 - rhs_2;

  int count = 0;
  for (int i = 0; i < size_of_int2023_t; i++) {
    if (rez.num[i] == 0) {
      count++;
    }
  }
  if (count == size_of_int2023_t) {
    return true;
  } else {
    return false;
  }
}

bool operator!=(const int2023_t& lhs, const int2023_t& rhs) {
  int2023_t l = lhs, r = rhs;
  if (r == l) {
    return false;
  } else {
    return true;
  }
}

int2023_t operator/(const int2023_t& lhs, const int2023_t& rhs) {
  int2023_t quotient, remainder, divisor = rhs, divindend = lhs, one;
  one = one + from_int(1);
  bool ans_will_be_negative = false;
  if (((divindend.num[0] >> 7) & 1) == 1 && ((divisor.num[0] >> 7) & 1) == 1) {
    AddedCode(divindend.num);
    AddedCode(divisor.num);

  } else if (((divindend.num[0] >> 7) & 1) == 1 && ((divisor.num[0] >> 7) & 1) == 0) {
    AddedCode(divindend.num);
    ans_will_be_negative = true;

  } else if (((divindend.num[0] >> 7) & 1) == 0 && ((divisor.num[0] >> 7) & 1) == 1) {
    AddedCode(divisor.num);
    ans_will_be_negative = true;
  }
  if (SecondNotBiggerThenFirst(divindend, divisor) == false) {
    if (divisor != divindend) {
      return quotient;
    }
  }
  if (divisor == divindend) {
    return one;
  }
  if (IsZero(divindend.num) || IsZero(divisor.num)) {
    return quotient;
  }
  for (int i = 0; i < size_of_int2023_t; i++) {
    for (int j = 7; j >= 0; j--) {
      MoveToLeftOnce(remainder.num);
      remainder.num[size_of_int2023_t - 1] |= ((divindend.num[i] >> j) & 1);
      if (SecondNotBiggerThenFirst(remainder, divisor)) {
        remainder = remainder - divisor;
        quotient.num[i] |= (1 << j);
      }
    }
  }
  if (ans_will_be_negative) {
    AddedCode(quotient.num);
  }
  return quotient;
}

std::ostream& operator<<(std::ostream& stream, const int2023_t& value) {
  for (int i = 0; i < size_of_int2023_t; i++) {
    for (int j = 7; j >= 0; j--) {
      std::cout << ((value.num[i] >> j) & 1);
    }
  }
  return stream;
}
