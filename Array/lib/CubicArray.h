#include <iostream>
#include "cstdint"

class SeventeenBit {
  friend bool operator == (const SeventeenBit &lhs, const SeventeenBit &rhs);
  friend bool operator != (const SeventeenBit &lhs, const SeventeenBit &rhs);

  friend std::ostream& operator<<(std::ostream& stream, const SeventeenBit& cllas);
  friend std::istream& operator>>(std::istream& stream, const SeventeenBit& cllas);
  friend class SeventeenBitClass;
 private:
  int16_t *first_16_bits;
  int16_t *last_bit;
  int index = 0;
  int size = 0;
 public:



  void operator=(const int& k) {
    int16_t a = 0;
    (last_bit[index / 16]) |= (((k >> 0) & 1) << (15 - index % 16));
    for (int i = 1; i < 17; i++) {
      a |= (((k >> i) & 1) << (i - 1));
    }
    first_16_bits[index] = a;
  }

};
bool operator == (const SeventeenBit &lhs, const SeventeenBit &rhs);
bool operator != (const SeventeenBit &lhs, const SeventeenBit &rhs);

class SeventeenBitClass {
  friend bool operator == (const SeventeenBitClass &lhs, const SeventeenBitClass &rhs);
  friend bool operator != (const SeventeenBitClass &lhs, const SeventeenBitClass &rhs);
 private:
  int x_;
  int y_;
  int z_;
 public:

  SeventeenBitClass operator+(const SeventeenBitClass& other);
  SeventeenBitClass operator-(const SeventeenBitClass& other);
  SeventeenBitClass operator*(const int& other);

  SeventeenBit small;

  SeventeenBitClass(int c_x, int c_y, int c_z) {
    x_ = c_x;
    y_ = c_y;
    z_ = c_z;
    small.first_16_bits = new int16_t[c_x * c_y * c_z]{};
    small.last_bit = new int16_t[((c_x * c_y * c_z) / 16) + 1]{};
    small.size = (x_ * y_ * z_);
  }

  class Square {
    friend SeventeenBitClass;
   private:
    SeventeenBitClass& arr;
    int curr_x_, curr_y_;
   public:
    SeventeenBit small;
    Square(SeventeenBitClass& arrr, int x, int y) : arr(arrr), curr_x_(x), curr_y_(y) {}

    SeventeenBit& operator[](int z) {
      arr.small.index =
          ((arr.small.size / arr.x_) * curr_x_ + (arr.small.size / (arr.x_ * arr.y_)) * curr_y_ + z * (arr.z_ - 1));
      small.first_16_bits = arr.small.first_16_bits;
      small.last_bit = arr.small.last_bit;
      return arr.small;
    }
  };

  class Line {
    friend SeventeenBitClass;
   private:
    SeventeenBitClass& arr;
    int curr_x_;
   public:
    SeventeenBit small;
    Line(SeventeenBitClass& arr, int x) : arr(arr), curr_x_(x) {}

    Square operator[](int y) {
      return Square(arr, curr_x_, y);
    }
  };

  Line operator[](int x) {
    return Line(*this, x);
  }
  static SeventeenBitClass make_array(int cooddinate_x, int cooddinate_y, int cooddinate_z) {
    return SeventeenBitClass(cooddinate_x, cooddinate_y, cooddinate_z);
  }
  ~SeventeenBitClass() {
    delete[] small.first_16_bits;
    delete[] small.last_bit;
  }
};
bool operator == (const SeventeenBitClass &lhs, const SeventeenBitClass &rhs);
bool operator != (const SeventeenBitClass &lhs, const SeventeenBitClass &rhs);
