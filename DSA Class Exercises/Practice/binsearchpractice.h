#pragma once

#include <vector>

class BinarySearch {
public:
  static BinarySearch& get();
  const void setArray(std::vector<int>*);
  void setTerm(int);

private:
  BinarySearch() : arr(nullptr), l(0), r(0), i(0), searchterm(0) {}
  BinarySearch(const BinarySearch&) = delete;
  BinarySearch& operator=(const BinarySearch&) = delete;

  void search();
  const void logfound() const;
  const void lognotfound() const;
  void calcIndex();

private:
  std::vector<int>* arr;
  static BinarySearch binstance;
  size_t l,r,i;
  int searchterm;
};
