#include <iostream>
#include <vector>
#include "mergesort.h"
#include "quicksort.h"

std::ostream& operator<< (std::ostream& COUT, const std::vector<int>* arr) {
  size_t arrsize{};
  while (arrsize < arr->size()) {
    COUT << arr->at(arrsize) << " | ";
    arrsize++;
  }
  return COUT;
}

int main() {
  std::vector<int>* arr = new std::vector<int> {9,3,7,5,6,4,8,2};

  MergeSort mergearr(arr);
  std::cout << arr;

  return 0;
}