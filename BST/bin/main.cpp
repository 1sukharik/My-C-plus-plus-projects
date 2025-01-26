#include "../lib/bintree.h"
#include "vector"

int main() {
  BinSaerchTree<int, preordertraversal> a;

  a.insert(8);
  a.insert(3);
  a.insert(1);
  a.insert(6);
  a.insert(4);
  a.insert(7);
  a.insert(10);
  a.insert(14);
  a.insert(13);
  a.insert(15);
  auto in_it = a.find(90);
  std::cout << (a.end() == in_it);
}
