#pragma once
#include <vector>

class MergeSort {
public:
  MergeSort(std::vector<int>*);

private:
  std::vector<int>* arr;

private:
  void mergeSort(size_t, size_t);
  void merge(size_t, size_t, size_t);
};