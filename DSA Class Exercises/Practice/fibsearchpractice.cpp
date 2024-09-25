#include "fibsearchpractice.h"
#include <iostream>
#include <vector>
#include <utility>

FibonacciSearch& FibonacciSearch::get() { return finstance; }

const void FibonacciSearch::setArray(std::vector<int>* sortedarr) { this->arr = sortedarr; }

void FibonacciSearch::setTerm(int searchterm) {
  this->value = searchterm;
  this->fib2 = 0;
  this->fib1 = 1;
  this->fibM = this->fib2 + this->fib1;
  this->search();
}

void FibonacciSearch::search() {
  const size_t arrsize = this->arr->size();
  if (arrsize == 0) { return; }

  while (fibM < arrsize) {
    this->fib2 = this->fib1;
    this->fib1 = this->fibM;
    this->fibM = this->fib2 + this->fib1;
  }

  size_t index {0};
  int offset {-1};

  while (this->fib2 > 0 and this->fib2 < arrsize) {
    index = std::min(this->fib2 + offset, arrsize-1);
    if (this->value < this->arr->at(index)) {
      this->fibM = this->fib2;
      this->fib1 = this->fib1 - this->fib2;
      this->fib2 = this->fibM - this->fib1;
    } else if (this->value > this->arr->at(index)) {
      offset = index;
      this->fibM = this->fib1;
      this->fib1 = this->fib2;
      this->fib2 = this->fibM - this->fib1;
    } else {
      this->logfound(index);
      return;
    }
  }

  if ((static_cast<size_t>(1) + offset) < arrsize) {
    if (this->value == this->arr->at(static_cast<size_t>(1) + offset)) {
      this->logfound(static_cast<size_t>(1)+offset); 
      return; 
    }
  }
  
  this->lognotfound();
}

const void FibonacciSearch::logfound(size_t index) const { std::cout << "Found: " << this->value << " at index: " << index << std::endl; }

const void FibonacciSearch::lognotfound() const { std::cout << "Not found: " << this->value << std::endl; }

FibonacciSearch FibonacciSearch::finstance;