#include "all_adapters.h"


template<typename Function>
class transform {

 public:

  explicit transform(Function f) : function_(f) {

  }
  Function GetFunc() {
    return function_;
  }
 private:

  Function function_;
};

template<typename Function>

class filter {
 public:
  explicit filter(Function f) : function_(f) {

  }
  Function GetFunc() {
    return function_;
  }
 private:
  Function function_;
};

template<typename Function>
class take {
 public:
  explicit take(Function f) : function_(f) {

  }
  Function GetFunc() {
    return function_;
  }
 private:
  Function function_;
};

template<typename Function>
class drop {
 public:
  explicit drop(Function f) : function_(f) {

  }
  Function GetFunc() {
    return function_;
  }
 private:
  Function function_;
};

template<typename Function>
class reverse {
 public:
  explicit reverse(Function f) : function_(f) {

  }
  Function GetFunc() {
    return function_;
  }
 private:
  Function function_;
};

template<typename Function>
class keys {
 public:
  explicit keys(Function f) : function_(f) {

  }
  Function GetFunc() {
    return function_;
  }
 private:
  Function function_;
};

template<typename Function>
class values {
 public:
  explicit values(Function f) : function_(f) {

  }
  Function GetFunc() {
    return function_;
  }
 private:
  Function function_;
};

template<typename Container, typename Function>
Container operator|(Container c, Function f) {
  Container result;
  if constexpr (std::is_same_v<Function, transform<decltype(f.GetFunc())> >) {

    result = TransformAdapter<Container, decltype(f.GetFunc())>(c, f.GetFunc()).to_transform();

  } else if constexpr (std::is_same_v<Function, filter<decltype(f.GetFunc())> >) {

    result = FilterAdapter<Container, decltype(f.GetFunc())>(c, f.GetFunc()).to_filtr();

  } else if constexpr (std::is_same_v<Function, take<decltype(f.GetFunc())> >) {

    result = TakeAdapter<Container, decltype(f.GetFunc())>(c, f.GetFunc()).to_take();

  } else if constexpr (std::is_same_v<Function, drop<decltype(f.GetFunc())> >) {

    result = DropAdapter<Container, decltype(f.GetFunc())>(c, f.GetFunc()).to_drop();
  } else if constexpr (std::is_same_v<reverse<Function>, decltype(f.GetFunc())>) {

    result = ReverseAdapter<Container, decltype(f.GetFunc())>(c, f.GetFunc()).to_reverse();

  } else if constexpr (std::is_same_v<keys<Function>, decltype(f.GetFunc())>) {

    result = ReverseAdapter<Container, decltype(f.GetFunc())>(c, f.GetFunc()).to_key();

  } else if constexpr (std::is_same_v<values<Function>, decltype(f.GetFunc())>) {

    result = ReverseAdapter<Container, decltype(f.GetFunc())>(c, f.GetFunc()).to_value();
  }
  return result;
}
