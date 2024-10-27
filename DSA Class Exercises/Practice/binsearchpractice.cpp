#include "binsearchpractice.h"

#include <iostream>
#include <vector>

BinarySearch& BinarySearch::get() { return binstance; }

const void BinarySearch::setArray(std::vector<int>* sortedarr) {
  this->arr = sortedarr;
}

void BinarySearch::setTerm(int value) {
  this->searchterm = value;
  this->l = 0;
  this->r = this->arr->size();
  this->calcIndex();
  this->search();
}

void BinarySearch::search() {
  if (this->i == 0 or this->i == this->arr->size() - 1) {
    if (this->searchterm == this->arr->at(this->i)) {
      this->logfound();
      return;
    } else {
      this->lognotfound();
      return;
    }
  }

  if (this->searchterm == this->arr->at(this->i)) {
    this->logfound();
    return;
  } else if (this->searchterm < this->arr->at(this->i)) {
    this->r = this->i;
  } else if (this->searchterm > this->arr->at(this->i)) {
    this->l = this->i;
  }
  this->calcIndex();
  this->search();
}

const void BinarySearch::logfound() const {
  std::cout << "Found: " << this->searchterm << " at index: " << this->i
            << std::endl;
}
const void BinarySearch::lognotfound() const {
  std::cout << "Not found: " << this->searchterm << std::endl;
}
void BinarySearch::calcIndex() { this->i = (this->l + this->r) / 2; }

BinarySearch BinarySearch::binstance;