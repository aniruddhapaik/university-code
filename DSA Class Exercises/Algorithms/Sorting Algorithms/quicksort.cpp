#include <vector>
#include "quicksort.h"

QuickSort::QuickSort(std::vector<int>* arrptr) {
  this->arr = arrptr;
  this->quickSort(0, this->arr->size()-1);
}

size_t QuickSort::sort(size_t leftindex, size_t rightindex) {
  size_t pivotindex = leftindex;
  while (leftindex < rightindex) {
    do { leftindex++; } while (this->arr->at(leftindex) <= this->arr->at(pivotindex)); 
    while (this->arr->at(rightindex) > this->arr->at(pivotindex)) { rightindex--; }
    if (leftindex < rightindex) {
      int temp = this->arr->at(leftindex);
      this->arr->at(leftindex) = this->arr->at(rightindex);
      this->arr->at(rightindex) = temp;
    }
  }
  int temp = this->arr->at(rightindex);
  this->arr->at(rightindex) = this->arr->at(pivotindex);
  this->arr->at(pivotindex) = temp;
  return rightindex;
}

void QuickSort::quickSort(size_t leftindex, size_t rightindex) {
  if (leftindex < rightindex) {
    size_t pivotindex = this->sort(leftindex, rightindex);
    this->quickSort(leftindex, pivotindex);
    this->quickSort(pivotindex+1, rightindex);
  }
}