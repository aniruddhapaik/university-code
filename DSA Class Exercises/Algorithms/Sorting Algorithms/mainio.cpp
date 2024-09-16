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
  std::vector<int>* arr = new std::vector<int> {9,3,1,7,5,6,4,0,8,2};

  std::cout << "Merge Sort --\n";
  std::cout << "- Not sorted: " << arr << std::endl;
  MergeSort mergearr(arr);
  std::cout << "- Sorted:     " << arr << std::endl;

  std::vector<int>* arr2 = new std::vector<int> {2,15,3,8,7,1,12,10,
                                                7,14,11,9,5,13,0,4,6};

  std::cout << "Quick Sort --\n";
  std::cout << "- Not Sorted: " << arr2 << std::endl;
  QuickSort quickarr(arr2);
  std::cout << "- Sorted:     " << arr2 << std::endl;

  return 0;
}