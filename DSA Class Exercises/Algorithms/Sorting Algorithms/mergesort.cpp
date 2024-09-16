#include <vector>
#include "mergesort.h"

MergeSort::MergeSort(std::vector<int>* arrptr) { 
  this->arr = arrptr; 
  this->mergeSort(0, this->arr->size()-1);
}

void MergeSort::mergeSort(size_t leftindex, size_t rightindex) {
  if (leftindex < rightindex) {
    size_t mid = (leftindex + rightindex) / 2;
    this->mergeSort(leftindex, mid);
    this->mergeSort(mid+1, rightindex);
    this->merge(leftindex, mid, rightindex);
  }
}

void MergeSort::merge(size_t leftindex, size_t mid, size_t rightindex) {
  size_t i{leftindex};
  size_t j{mid+1};
  std::vector<int> temp;

  while (i <= mid and j <= rightindex) {
    if (this->arr->at(i) < this->arr->at(j)) {
      temp.push_back(this->arr->at(i));
      i++;
    } else {
      temp.push_back(this->arr->at(j));
      j++;
    }
  }

  while (i <= mid) {
    temp.push_back(this->arr->at(i));
    i++;
  }

  while (j <= rightindex) {
    temp.push_back(this->arr->at(j));
    j++;
  }

  size_t t{0};
  for (size_t k = leftindex; k <= rightindex; k++) {
    this->arr->at(k) = temp.at(t);
    t++;
  }
}