#include "CubicArray.h"

std::ostream& operator<<(std::ostream& stream, const SeventeenBit& cllas) {
  int ans = 0;
  ans |= ((cllas.last_bit[cllas.index / 16] >> (15 - cllas.index % 16)) & 1);
  for (int i = 0; i < 16; i++) {
    ans |= (((cllas.first_16_bits[cllas.index] >> i) & 1) << (i + 1));
  }
  std::cout << ans;
  return stream;
}

std::istream& operator>>(std::istream& stream, SeventeenBit& cllas) {
  int a;
  std::cin >> a;
  cllas = 5;
  return stream;
}

bool operator==(const SeventeenBit& lhs, const SeventeenBit& rhs) {
  int first_num = 0;
  first_num |= ((lhs.last_bit[lhs.index / 16] >> (15 - lhs.index % 16)) & 1);
  for (int i = 0; i < 16; i++) {
    first_num |= (((lhs.first_16_bits[lhs.index] >> i) & 1) << (i + 1));
  }
  int second_num = 0;
  second_num |= ((rhs.last_bit[rhs.index / 16] >> (15 - rhs.index % 16)) & 1);
  for (int i = 0; i < 16; i++) {
    second_num |= (((rhs.first_16_bits[rhs.index] >> i) & 1) << (i + 1));
  }
  return (first_num == second_num);
}

bool operator!=(const SeventeenBit& lhs, const SeventeenBit& rhs) {
  return !(lhs == rhs);
}

bool operator==(const SeventeenBitClass& lhs, const SeventeenBitClass& rhs) {
  for (int i = 0; i < lhs.small.size; i++) {
    if (lhs.small.first_16_bits[i] != rhs.small.first_16_bits[i]) {
      return false;
    }
  }
  for (int i = 0; i < lhs.small.size / 16; i++) {
    for (int j = 0; j < 16; j++) {
      if (((lhs.small.last_bit[i] >> j) & 1) != ((rhs.small.last_bit[i] >> j) & 1)) {
        return false;
      }
    }
  }
  return true;
}
bool operator!=(const SeventeenBitClass& lhs, const SeventeenBitClass& rhs) {
  return !(lhs == rhs);
}

SeventeenBitClass SeventeenBitClass::operator+(const SeventeenBitClass& other) {
  SeventeenBitClass tmp = SeventeenBitClass::make_array(this->x_, this->y_, this->z_);

  tmp.small.last_bit = new int16_t[this->small.size]{};
  tmp.small.first_16_bits = new int16_t[this->small.size]{};

  int ans1 = 0;
  int ans2 = 0;
  for (int i = 0; i < this->small.size; i++) {
    ans1 |= ((this->small.last_bit[i / 16] >> (15 - i % 16)) & 1);
    for (int j = 0; j < 16; j++) {
      ans1 |= (((this->small.first_16_bits[i] >> j) & 1) << (j + 1));
    }
    ans2 |= ((other.small.last_bit[i / 16] >> (15 - i % 16)) & 1);
    for (int j = 0; j < 16; j++) {
      ans2 |= (((other.small.first_16_bits[i] >> j) & 1) << (j + 1));
    }
    ans1 += ans2;
    int16_t a = 0;
    (tmp.small.last_bit[i / 16]) |= (((ans1 >> 0) & 1) << (15 - i % 16));
    for (int k = 1; k < 17; k++) {
      a |= (((ans1 >> k) & 1) << (k - 1));
    }
    tmp.small.first_16_bits[i] = a;
    ans1 = 0;
    ans2 = 0;
  }
  return tmp;
}

SeventeenBitClass SeventeenBitClass::operator-(const SeventeenBitClass& other) {
  SeventeenBitClass tmp = SeventeenBitClass::make_array(this->x_, this->y_, this->z_);

  tmp.small.last_bit = new int16_t[this->small.size]{};
  tmp.small.first_16_bits = new int16_t[this->small.size]{};

  int ans1 = 0;
  int ans2 = 0;
  for (int i = 0; i < this->small.size; i++) {
    ans1 |= ((this->small.last_bit[i / 16] >> (15 - i % 16)) & 1);
    for (int j = 0; j < 16; j++) {
      ans1 |= (((this->small.first_16_bits[i] >> j) & 1) << (j + 1));
    }
    ans2 |= ((other.small.last_bit[i / 16] >> (15 - i % 16)) & 1);
    for (int j = 0; j < 16; j++) {
      ans2 |= (((other.small.first_16_bits[i] >> j) & 1) << (j + 1));
    }
    ans1 -= ans2;
    int16_t a = 0;
    (tmp.small.last_bit[i / 16]) |= (((ans1 >> 0) & 1) << (15 - i % 16));
    for (int k = 1; k < 17; k++) {
      a |= (((ans1 >> k) & 1) << (k - 1));
    }
    tmp.small.first_16_bits[i] = a;
    ans1 = 0;
    ans2 = 0;
  }
  return tmp;
}

SeventeenBitClass SeventeenBitClass::operator*(const int& other) {
  SeventeenBitClass tmp = SeventeenBitClass::make_array(this->x_, this->y_, this->z_);

  tmp.small.last_bit = new int16_t[this->small.size]{};
  tmp.small.first_16_bits = new int16_t[this->small.size]{};

  int ans1 = 0;
  for (int i = 0; i < this->small.size; i++) {
    ans1 |= ((this->small.last_bit[i / 16] >> (15 - i % 16)) & 1);
    for (int j = 0; j < 16; j++) {
      ans1 |= (((this->small.first_16_bits[i] >> j) & 1) << (j + 1));
    }

    ans1 *= other;

    int16_t a = 0;
    (tmp.small.last_bit[i / 16]) |= (((ans1 >> 0) & 1) << (15 - i % 16));

    for (int k = 1; k < 17; k++) {
      a |= (((ans1 >> k) & 1) << (k - 1));
    }

    tmp.small.first_16_bits[i] = a;
    ans1 = 0;
  }
  return tmp;
}
