#include "binsearchpractice.h"
#include "linsearchpractice.h"
#include "fibsearchpractice.h"
#include <iostream>
#include <vector>


int main() {
  std::vector<int> sortedarr {1,2,3,4,5,6,7,8,9,10, 11, 12, 13, 14, 15};

  BinarySearch& binsearch = BinarySearch::get();
  binsearch.setArray(&sortedarr);
  std::cout << "\nBinary Search -----\n";
  binsearch.setTerm(10);

  LinearSearch& linsearch = LinearSearch::get();
  linsearch.setArray(&sortedarr);
  std::cout << "\nLinear Search -----\n";
  linsearch.setTerm(5);

  FibonacciSearch& fibsearch = FibonacciSearch::get();
  fibsearch.setArray(&sortedarr);
  std::cout << "\nFibonacci Search -----\n";
  fibsearch.setTerm(12);

  return 0;
}