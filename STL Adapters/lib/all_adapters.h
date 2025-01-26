

#ifndef LABWORK9_1SUKHARIK_LIB_ALL_ADAPTERS_H_
#define LABWORK9_1SUKHARIK_LIB_ALL_ADAPTERS_H_
#include "iostream"
#include "algorithm"
#include <concepts>

template<typename T>
concept AssociativeContainer = requires(T a) {
  typename T::key_type;
  typename T::mapped_type;
};

template<typename T>
concept NonAssociativeContainer = !requires(T a) {
  typename T::key_type;
  typename T::mapped_type;
};

template<typename Container, typename Function>
class TransformAdapter {

 private:

  template<typename InnerIterator>
  class InIterator {
   public:
    using inner_iterator_type = typename InnerIterator::value_type;
    using value_type = std::__invoke_result<Function, const inner_iterator_type&>;

    InIterator(InnerIterator it, Function func)
        : it_(std::move(it)),
          func_(std::move(func)) {
    };

    value_type operator*() {
      return func_(*it_);
    }

    InIterator& operator++() {
      ++it_;
      return *this;
    }

    bool operator==(const InIterator& other) const {
      return it_ == other.it_;
    }

    bool operator!=(const InIterator& other) const {
      return it_ != other.it_;
    }

   private:
    InnerIterator it_;
    Function func_;
  };

  Function func_;

  Container range_;
 public:
  using inner_iterator = typename Container::const_iterator;
  using iterator = InIterator<inner_iterator>;
  Container to_transform() {
    for (auto& i : range_) {
      i = func_(i);
    }
    return range_;

  }
  iterator begin() {
    return iterator(std::begin(range_), func_);
  }

  iterator end() {
    return iterator(std::end(range_), func_);
  }

  TransformAdapter(Container range, Function func) :
      range_(range),
      func_(func) {
  }

};

template<typename Container, typename Function>
class FilterAdapter {
 private:

  template<typename InnerIterator>
  class InIterator {
   public:
    using inner_iterator_type = typename InnerIterator::value_type;
    using value_type = std::__invoke_result<Function, const inner_iterator_type&>;

    InIterator(InnerIterator it, Function func)
        : it_(std::move(it)),
          func_(std::move(func)) {
    };

    value_type operator*() {
      return func_(*it_);
    }

    InIterator& operator++() {
      ++it_;
      return *this;
    }

    bool operator==(const InIterator& other) const {
      return it_ == other.it_;
    }

    bool operator!=(const InIterator& other) const {
      return it_ != other.it_;
    }

   private:
    InnerIterator it_;
    Function func_;
  };

  Function func_;

  Container range_;
 public:
  using inner_iterator = typename Container::const_iterator;
  using iterator = InIterator<inner_iterator>;
  Container to_filtr() {
    Container answer;

    for (auto& i : range_) {
      if (func_(i)) {
        answer.push_back(i);
      }
    }
    range_ = answer;
    return range_;
  }
  iterator begin() {
    return iterator(std::begin(range_), func_);
  }

  iterator end() {
    return iterator(std::end(range_), func_);
  }

  FilterAdapter(Container range, Function func) :
      range_(range),
      func_(func) {
  }

};

template<typename Container, typename Function>
class TakeAdapter {
 private:

  template<typename InnerIterator>
  class InIterator {
   public:
    using inner_iterator_type = typename InnerIterator::value_type;
    using value_type = std::__invoke_result<Function, const inner_iterator_type&>;

    InIterator(InnerIterator it, Function func)
        : it_(std::move(it)),
          func_(std::move(func)) {
    };

    value_type operator*() {
      return func_(*it_);
    }

    InIterator& operator++() {
      ++it_;
      return *this;
    }

    bool operator==(const InIterator& other) const {
      return it_ == other.it_;
    }

    bool operator!=(const InIterator& other) const {
      return it_ != other.it_;
    }

   private:
    InnerIterator it_;
    Function func_;
  };

  Function func_;

  Container range_;
 public:
  using inner_iterator = typename Container::const_iterator;
  using iterator = InIterator<inner_iterator>;
  Container to_take() {
    Container answer;
    Function t = 0;

    for (auto& i : range_) {
      t++;
      if (t <= func_) {
        std::fill_n(std::back_inserter(answer), i, 1);
      }
    }
    range_ = answer;
    return range_;
  }
  iterator begin() {
    return iterator(std::begin(range_), func_);
  }

  iterator end() {
    return iterator(std::end(range_), func_);
  }

  TakeAdapter(Container range, Function func) :
      range_(range),
      func_(func) {
  }

};

template<typename Container, typename Function>
class DropAdapter {
 private:

  template<typename InnerIterator>
  class InIterator {
   public:
    using inner_iterator_type = typename InnerIterator::value_type;
    using value_type = std::__invoke_result<Function, const inner_iterator_type&>;

    InIterator(InnerIterator it, Function func)
        : it_(std::move(it)),
          func_(std::move(func)) {
    };

    value_type operator*() {
      return func_(*it_);
    }

    InIterator& operator++() {
      ++it_;
      return *this;
    }

    bool operator==(const InIterator& other) const {
      return it_ == other.it_;
    }

    bool operator!=(const InIterator& other) const {
      return it_ != other.it_;
    }

   private:
    InnerIterator it_;
    Function func_;
  };

  Function func_;

  Container range_;
 public:
  using inner_iterator = typename Container::const_iterator;
  using iterator = InIterator<inner_iterator>;
  Container to_drop() {
    Container answer;
    Function t = 0;

    for (auto& i : range_) {
      t++;
      if (t >= func_) {
        std::fill_n(std::back_inserter(answer), 1, i);
      }
    }
    range_ = answer;
    return range_;
  }
  iterator begin() {
    return iterator(std::begin(range_), func_);
  }

  iterator end() {
    return iterator(std::end(range_), func_);
  }

  DropAdapter(Container range, Function func) :
      range_(range),
      func_(func) {
  }

};

template<typename Container, typename Function>
class ReverseAdapter {
 private:

  template<typename InnerIterator>
  class InIterator {
   public:
    using inner_iterator_type = typename InnerIterator::value_type;
    using value_type = std::__invoke_result<Function, const inner_iterator_type&>;

    InIterator(InnerIterator it, Function func)
        : it_(std::move(it)),
          func_(std::move(func)) {
    };

    value_type operator*() {
      return func_(*it_);
    }

    InIterator& operator++() {
      ++it_;
      return *this;
    }

    bool operator==(const InIterator& other) const {
      return it_ == other.it_;
    }

    bool operator!=(const InIterator& other) const {
      return it_ != other.it_;
    }

   private:
    InnerIterator it_;
    Function func_;
  };

  Function func_;

  Container range_;
 public:
  using inner_iterator = typename Container::const_iterator;
  using iterator = InIterator<inner_iterator>;
  Container to_reverse() {

    std::reverse_iterator(range_.begin(), range_.end());
    return range_;
  }
  iterator begin() {
    return iterator(std::begin(range_), func_);
  }

  iterator end() {
    return iterator(std::end(range_), func_);
  }

  ReverseAdapter(Container range, Function func) :
      range_(range),
      func_(func) {
  }

};

template<typename Container, typename Function>
class KeysAdapter {
  static_assert(AssociativeContainer<Container>, "CONTAINER MUST BE ASSOCIATIVE");
 private:

  template<typename InnerIterator>
  class InIterator {
   public:
    using inner_iterator_type = typename InnerIterator::value_type;
    using value_type = std::__invoke_result<Function, const inner_iterator_type&>;

    InIterator(InnerIterator it, Function func)
        : it_(std::move(it)),
          func_(std::move(func)) {
    };

    value_type operator*() {
      return func_(*it_);
    }

    InIterator& operator++() {
      ++it_;
      return *this;
    }

    bool operator==(const InIterator& other) const {
      return it_ == other.it_;
    }

    bool operator!=(const InIterator& other) const {
      return it_ != other.it_;
    }

   private:
    InnerIterator it_;
    Function func_;
  };

  Function func_;

  Container range_;
 public:
  using inner_iterator = typename Container::const_iterator;
  using iterator = InIterator<inner_iterator>;
  Container to_key() {

    Container answer;
    for (auto& i : range_) {
      std::fill_n(std::back_inserter(answer), i.second(), 1);
    }

    range_ = answer;
    return range_;
  }
  iterator begin() {
    return iterator(std::begin(range_), func_);
  }

  iterator end() {
    return iterator(std::end(range_), func_);
  }

  KeysAdapter(Container range, Function func) :
      range_(range),
      func_(func) {
  }

};

template<typename Container, typename Function>
class ValuesAdapter {
  static_assert(AssociativeContainer<Container>, "CONTAINER MUST BE ASSOCIATIVE");
 private:

  template<typename InnerIterator>
  class InIterator {
   public:
    using inner_iterator_type = typename InnerIterator::value_type;
    using value_type = std::__invoke_result<Function, const inner_iterator_type&>;

    InIterator(InnerIterator it, Function func)
        : it_(std::move(it)),
          func_(std::move(func)) {
    };

    value_type operator*() {
      return func_(*it_);
    }

    InIterator& operator++() {
      ++it_;
      return *this;
    }

    bool operator==(const InIterator& other) const {
      return it_ == other.it_;
    }

    bool operator!=(const InIterator& other) const {
      return it_ != other.it_;
    }

   private:
    InnerIterator it_;
    Function func_;
  };

  Function func_;

  Container range_;
 public:
  using inner_iterator = typename Container::const_iterator;
  using iterator = InIterator<inner_iterator>;
  Container to_value() {
    Container answer;
    for (auto& i : range_) {
      std::fill_n(std::back_inserter(answer), i.first(), 1);
    }

    range_ = answer;
    return range_;
  }
  iterator begin() {
    return iterator(std::begin(range_), func_);
  }

  iterator end() {
    return iterator(std::end(range_), func_);
  }

  ValuesAdapter(Container range, Function func) :
      range_(range),
      func_(func) {
  }

};

#endif //LABWORK9_1SUKHARIK_LIB_ALL_ADAPTERS_H_
