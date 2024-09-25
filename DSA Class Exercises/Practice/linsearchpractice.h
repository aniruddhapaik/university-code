#pragma once

#include <vector>

class LinearSearch {
public:
  static LinearSearch& get();
  const void setArray(std::vector<int>*);
  void setTerm(int);

private:
  LinearSearch(): arr(nullptr), value(0), arrsize(0), index(0) {}
  LinearSearch(const LinearSearch&) = delete;
  LinearSearch& operator=(const LinearSearch&) = delete;

  void search();
  const void logfound() const;
  const void lognotfound() const;

private:
  std::vector<int>* arr;
  static LinearSearch linstance;
  int value;
  size_t arrsize, index;
};

