#include "..\lib\adpcont.h"
#include "vector"
int main() {
  std::vector<int> v = {1, 2, 3, 4, 5, 6};
  auto result = v | drop(3);

  for (auto i : result)
    std::cout << i << " ";
}
