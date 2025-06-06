#pragma once
#include <vector>

class QuickSort {
public:
  QuickSort(std::vector<int>*);

private:
  std::vector<int>* arr;

private:
  size_t sort(size_t, size_t);
  void quickSort(size_t, size_t);
};