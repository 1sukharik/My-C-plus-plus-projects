#ifndef LABWORK8_1SUKHARIK_LIB_BINTREE_H_
#define LABWORK8_1SUKHARIK_LIB_BINTREE_H_

#include "iostream"
#include "stack"
#include "limits"

struct inordertraversal {};

struct preordertraversal {};

struct postordertraversal {};

template<typename T>
struct Node {
  T value;
  Node *left;
  Node *right;
  Node *parent;

  Node(T data) {
    value = data;
    left = nullptr;
    right = nullptr;
    parent = nullptr;

  }
  void operator=(const Node<T> *other) {
    this = new Node<T>(other->value);
  }
};

template<typename T, typename Tag, typename Allocator=std::allocator<T>>
class BinSaerchTree {
 public:
  friend class Iterator;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef T *pointer;
  typedef const T *const_pointer;
  typedef T& reference;
  typedef const T& const_reference;
  typedef T value_type;

  BinSaerchTree() {
    root = nullptr;
    bbegin = nullptr;
    eend = nullptr;
    cbbegin = nullptr;
    ceend = nullptr;
    size_ = 0;
  }

  BinSaerchTree(const BinSaerchTree<T, Tag>& other) {
    this->ceend = other.ceend;
    this->bbegin = other.bbegin;
    this->cbbegin = other.cbbegin;
    this->size_ = other.size_;
    this->eend = other.eend;
    this->max_size_ = other.max_size_;
    this->root = Copy(other.root, nullptr);

  }

  ~BinSaerchTree() {
    Clear(root);

  }

  void insert(T value) {
    Ins(root, value);
  }

  void insert(T value1, T value2) {
    for (auto i = value1; i < value2; i++) {
      Ins(root, i);
    }
  }

  class Iterator {
   public:

    Iterator(Node<T> *it) {
      curr = it;
    }

    T& operator*() {
      return curr->value;
    }

    Iterator& operator++(int value) {
      BinSaerchTree temp(*this);
      if constexpr (std::is_same<Tag, inordertraversal>::value) {
        if (curr->right) {
          curr = curr->right;
          while (curr->left) {
            curr = curr->left;
          }
        } else {
          while (curr->parent && curr == curr->parent->right) {
            curr = curr->parent;
          }
          curr = curr->parent;
        }
        return *temp;

      } else if constexpr (std::is_same<Tag, preordertraversal>::value) {
        if (curr->left) {
          curr = curr->left;
        } else if (curr->right) {
          curr = curr->right;
        } else {
          while (curr->parent && (curr == curr->parent->right || !curr->parent->right)) {
            curr = curr->parent;
          }
          if (curr->parent) {
            curr = curr->parent->right;
          } else {
            curr = nullptr;
          }
        }
        return *temp;

      } else if constexpr (std::is_same<Tag, postordertraversal>::value) {
        if (curr->parent && curr == curr->parent->left && curr->parent->right) {
          curr = curr->parent->right;
          while (curr->left || curr->right) {
            while (curr->left) {
              curr = curr->left;
            }
            if (curr->right) {
              curr = curr->right;
            }
          }
        } else {
          curr = curr->parent;
        }
        return *temp;

      }

    }

    Iterator& operator++() {
      if constexpr (std::is_same<Tag, inordertraversal>::value) {
        if (curr->right) {
          curr = curr->right;
          while (curr->left) {
            curr = curr->left;
          }
        } else {
          while (curr->parent && curr == curr->parent->right) {
            curr = curr->parent;
          }
          curr = curr->parent;
        }
        return *this;

      } else if constexpr (std::is_same<Tag, preordertraversal>::value) {
        if (curr->left) {
          curr = curr->left;
        } else if (curr->right) {
          curr = curr->right;
        } else {
          while (curr->parent && (curr == curr->parent->right || !curr->parent->right)) {
            curr = curr->parent;
          }
          if (curr->parent) {
            curr = curr->parent->right;
          } else {
            curr = nullptr;
          }
        }
        return *this;

      } else if constexpr (std::is_same<Tag, postordertraversal>::value) {
        if (curr->parent && curr == curr->parent->left && curr->parent->right) {
          curr = curr->parent->right;
          while (curr->left || curr->right) {
            while (curr->left) {
              curr = curr->left;
            }
            if (curr->right) {
              curr = curr->right;
            }
          }
        } else {
          curr = curr->parent;
        }
        return *this;

      }

    }

    bool operator==(const Iterator& other) const {
      return (other.curr == this->curr);

    }

    bool operator!=(const Iterator& other) const {
      return (other.curr != this->curr);

    }

    Iterator& operator--(int value) {
      BinSaerchTree temp(*this);
      if constexpr (std::is_same<Tag, inordertraversal>::value) {
        if (curr->left) {
          curr = curr->left;
          while (curr->right) {
            curr = curr->right;
          }
        } else {
          while (curr->parent && curr == curr->parent->left) {
            curr = curr->parent;
          }
          curr = curr->parent;
        }
        return *temp;

      } else if constexpr (std::is_same<Tag, preordertraversal>::value) {
        if (curr->parent && curr->parent->left && curr->parent->right == curr) {
          curr = curr->parent->left;
          while (curr->left || curr->right) {
            if (curr->left) {
              curr = curr->left;
            } else {
              curr = curr->right;
            }
          }
        } else {
          curr = curr->parent;
        }
        return *temp;

      } else if constexpr (std::is_same<Tag, postordertraversal>::value) {
        if (curr->parent && curr->parent->right == curr) {
          if (curr->parent->left) {
            curr = curr->parent->left;
            while (curr->left || curr->right) {
              if (curr->right) {
                curr = curr->right;
              } else {
                curr = curr->left;
              }
            }
          } else {
            curr = curr->parent;
          }
        } else {
          curr = curr->parent;
        }
        return *temp;

      }
    }

    Iterator& operator--() {
      if constexpr (std::is_same<Tag, inordertraversal>::value) {
        if (curr->left) {
          curr = curr->left;
          while (curr->right) {
            curr = curr->right;
          }
        } else {
          while (curr->parent && curr == curr->parent->left) {
            curr = curr->parent;
          }
          curr = curr->parent;
        }
        return *this;

      } else if constexpr (std::is_same<Tag, preordertraversal>::value) {
        if (curr->parent && curr->parent->left && curr->parent->right == curr) {
          curr = curr->parent->left;
          while (curr->left || curr->right) {
            if (curr->left) {
              curr = curr->left;
            } else {
              curr = curr->right;
            }
          }
        } else {
          curr = curr->parent;
        }
        return *this;

      } else if constexpr (std::is_same<Tag, postordertraversal>::value) {
        if (curr->parent && curr->parent->right == curr) {
          if (curr->parent->left) {
            curr = curr->parent->left;
            while (curr->left || curr->right) {
              if (curr->right) {
                curr = curr->right;
              } else {
                curr = curr->left;
              }
            }
          } else {
            curr = curr->parent;
          }
        } else {
          curr = curr->parent;
        }
        return *this;

      }

    }

   private:

    Node<T> *curr;

    std::stack<Node<T> *> traversal;

  };

  void insert(BinSaerchTree& a) {
    for (auto i = a.begin(); i < a.end(); i++) {
      Ins(root, *i);
    }
  }

  Iterator begin() {
    if constexpr (std::is_same<Tag, preordertraversal>::value) {
      return Begin(root);
    }
    return Begin(bbegin);

  }

  Iterator end() {
    return End(eend);

  }

  size_t size() {
    return size_;

  }

  void clear() {
    Clear(root);
  }

  void merge(BinSaerchTree& other) {
    Merg(other.root);

  }

  Iterator erase(T k) {
    Iterator it = find(k);

    it++;
    this->Delete(root, k);
    return it;

  }

  void erase(T k1, T k2) {
    for (auto i = k1; i < k2; i++) {
      this->erase(i);
    }
  };

  Iterator extract(T k) {
    Node<T> *a = find(k);
    Delete(root, k);
    return a;

  }
  Iterator emplace(T k) {

    return Em(Ins(root, k));

  }

  Iterator lower_bound(T k) {
    Node<T> *l = Prev(root, k);
    return Iterator(l);

  }

  Iterator upper_bound(T k) {
    Node<T> *l = Next(root, k);
    return (Up(l));

  }

  size_t count(T k) {
    if (this->find(k)) {
      return 1;
    }
    return find(k);

  }

  Iterator cend() {
    if constexpr (std::is_same<Tag, preordertraversal>::value) {
      return Cend(root);
    }
    return Cend(ceend);

  }

  Iterator cbegin() {
    return Cbegin(cbbegin);

  }

  const Iterator crend() {
    return Cend(ceend);

  }

  const Iterator crbegin() {
    return Cbegin(cbbegin);

  }

  bool empty() {
    return this->begin() == this->end();
  }

  Iterator find(T k) {
    return Fi(Existence(root, k));

  }

  size_t max_size() {
    return std::numeric_limits<size_t>::max() / sizeof(T);
  }

  bool operator==(const BinSaerchTree& other) {
    return (this->size() == other->size() && std::equal(this->bbegin(), this->end(), other->begin()));

  }

  bool operator!=(const BinSaerchTree& other) {
    return !(this == other);

  }

 private:

  Iterator Up(Node<T> *l) {
    return Iterator(l);
  }

  Node<T> *Merg(Node<T> *r) {
    if (r) {
      this->insert(r->value);
      Merg(r->left);
      Merg(r->right);
    }
    return r;

  }

  Node<T> *Copy(Node<T> *r, Node<T> *parent) {
    if (!r) {
      return nullptr;
    }
    Node<T> *newNode = new Node<T>(r->value);
    newNode->parent = parent;
    newNode->left = Copy(r->left, newNode);
    newNode->right = Copy(r->right, newNode);
    return newNode;

  }

  Node<T> *Maxi(Node<T> *r) {
    if (root->right == nullptr) {
      return root;
    }
    return Maxi(r->right);
  }

  Node<T> *Delete(Node<T> *r, T value) {
    if (r == nullptr) {
      return r;
    }
    if (value < r->value) {
      r->left = Delete(r->left, value);
    } else if (value > r->value) {
      r->right = Delete(r->right, value);
    } else {
      Node<T> *leftt = r->left;
      Node<T> *rightt = r->right;
      if (leftt == nullptr) {
        return rightt;
      }
      Node<T> *maxi = Maxi(leftt);
      leftt = Delete(leftt, maxi->value);
      maxi->left = leftt;
      maxi->right = rightt;
      return maxi;

    }
    return r;

  }

  Node<T> *Prev(Node<T> *r, T prev_n) {
    Node<T> *curr = r;
    Node<T> *node = nullptr;
    while (curr != nullptr) {
      if (curr->value >= prev_n) {
        curr = curr->left;
      } else {
        node = curr;
        curr = curr->right;
      }
    }
    return node;
  }

  Node<T> *Next(Node<T> *r, T next) {
    Node<T> *curr = r;
    Node<T> *node = nullptr;
    while (curr != nullptr) {
      if (curr->value > next) {
        node = curr;
        curr = curr->left;
      } else {
        curr = curr->right;
      }
    }
    return node;

  }

  Node<T> *Existence(Node<T> *r, T value) {
    if (r == nullptr) {
      return nullptr;
    }
    if (r->value == value) {
      return r;
    } else {
      if (value > r->value) {
        return Existence(r->right, value);
      } else {
        return Existence(r->left, value);
      }
    }

  }

  void Clear(Node<T> *noda) {
    if (noda != nullptr) {
      Clear(noda->left);
      Clear(noda->right);
      delete[] noda;
    }
  }

  Iterator End(Node<T> *r) {
    return Iterator(r);
  }

  Iterator Fi(Node<T> *r) {
    return Iterator(r);
  }

  Iterator Begin(Node<T> *r) {
    return Iterator(r);

  }

  Iterator Cbegin(Node<T> *r) {
    return Iterator(r);

  }

  Iterator Cend(Node<T> *r) {
    return Iterator(r);

  }

  Iterator Em(Node<T> *l) {
    return Iterator(l);

  }

  Node<T> *root;
  size_t size_;
  Node<T> *bbegin;
  Node<T> *eend;
  Node<T> *cbbegin;
  Node<T> *ceend;
  size_t max_size_;

  Node<T> *Ins(Node<T> *node, T value) {
    size_++;
    if (!node) {
      root = new Node<T>(value);
      bbegin = root;
      ceend = root;

      return root;
    }
    int counter = 0;
    int real_left_conter = 0;
    Node<T> *nod = new Node<T>(value);
    while (node) {
      counter++;
      if (nod->value > node->value) {
        if (node->right) {
          node = node->right;
        } else {
          nod->parent = node;
          node->right = nod;
          return nod;

        }
      } else if (nod->value < node->value) {
        real_left_conter++;
        if (node->left) {
          node = node->left;
        } else {
          if (real_left_conter == counter) {
            bbegin = nod;
            ceend = nod;
          }
          nod->parent = node;
          node->left = nod;
          return nod;
        }
      }
    }
  }

};

#endif //LABWORK8_1SUKHARIK_LIB_BINTREE_H_
