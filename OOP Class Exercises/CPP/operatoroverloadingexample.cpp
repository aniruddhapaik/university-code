#include <iostream>
#include <ostream>
#include <vector>

std::ostream& operator<<(std::ostream& COUT, const std::vector<int>& list) {
  for (auto& item: list) {
    std::cout << item << ' ';
  }
  return COUT;
}

int main() {
  std::vector<int> List = {1, 2, 3, 5, 8, 10};
  std::cout << List << std::endl;
  return 0;
}