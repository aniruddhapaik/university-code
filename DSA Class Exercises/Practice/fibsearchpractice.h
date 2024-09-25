#pragma once

#include <vector>

class FibonacciSearch {
public:
  static FibonacciSearch& get();
  const void setArray(std::vector<int>*);
  void setTerm(int);

private:
  FibonacciSearch(): arr(nullptr), value(0), fibM(1), fib1(1), fib2(0) {};
  FibonacciSearch(const FibonacciSearch&) = delete;
  FibonacciSearch& operator=(const FibonacciSearch) = delete;

  void search();
  const void logfound(size_t) const;
  const void lognotfound() const;

private:
  static FibonacciSearch finstance;
  std::vector<int>* arr;
  int value;
  size_t fibM, fib1, fib2;
};

