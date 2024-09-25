#include "linsearchpractice.h"
#include <vector>
#include <iostream>

LinearSearch& LinearSearch::get() { return linstance; }

void LinearSearch::setTerm(int searchterm) { 
  this->value = searchterm; 
  this->search();
}

void LinearSearch::search() {
  this->arrsize = this->arr->size();

  while(this->index < this->arrsize) {
    if (this->value == this->arr->at(this->index)) { this->logfound(); return; }
    this->index++;
  }

  this->lognotfound();
  return;
}

const void LinearSearch::setArray(std::vector<int>* sortedarr) { this->arr = sortedarr; }

const void LinearSearch::logfound() const { std::cout << "Found: " << this->value << " at index: " << this->index << std::endl; }

const void LinearSearch::lognotfound() const { std::cout << "Not found: " << this->value << std::endl; }

LinearSearch LinearSearch::linstance;