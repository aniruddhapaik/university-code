#include <iostream>
#include <vector>
#include <utility>

#include "KnapSack.h"

int main() {
  KnapSack sack;

  std::vector<std::pair<float, float>> iteminfo = { // <weight, profit>
    {2, 10}, {3, 5}, {5, 15}, {7, 7}, {1, 6}, {4, 18}, {1, 3}
  };

  std::cout << "Format: (Weight|Profit)\n";

  for(auto& pair: iteminfo) {
    std::cout << pair.first << '|' << pair.second << ' ';
  }
  std::cout << '\n' << std::endl;

  sack.getItemsInfo(iteminfo, 15);

  return 0;
}