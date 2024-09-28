#include "binsearchpractice.h"
#include "linsearchpractice.h"
#include "fibsearchpractice.h"
#include "stackpractice.h"
#include <iostream>
#include <vector>
#include <limits>
#include <conio.h>

void clearAndResetInput() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool handleInput(int& choice) {
  std::cin >> choice;
  if (std::cin.fail()) {
    if (std::cin.eof()) { std::cout << "Reached end of input (EOF)." << std::endl; }
    else { std::cout << "Enter valid integer!" << std::endl; }
    clearAndResetInput();
    return false;
  }
  return true;
}

enum stackmenu {push, top, pop, empty, size, printstack, exitprogram};

void stackMenu() {
  Stack stack;
  int choice {};

  while (true) {
    system( "cls" );
    std::cout << "Stack Menu ---\n";
    std::cout << "0. Push\n";
    std::cout << "1. Top\n";
    std::cout << "2. Pop\n";
    std::cout << "3. Check If Empty\n";
    std::cout << "4. Size\n";
    std::cout << "5. Print Stack\n";
    std::cout << "6. Exit\n";
    std::cout << "-------------\n";
    std::cout << "Enter choice: " << std::flush;

    if (handleInput(choice)) {
      int key = 0;
      switch(choice) {
        case push:
          std::cout << "Enter key to push: " << std::flush;
          if (handleInput(key)) { stack.push(key); }
          break;
        case top:
          stack.top();
          break;
        case pop:
          stack.pop();
          break;
        case empty:
          stack.empty();
          break;
        case size:
          stack.size();
          break;
        case printstack:
          std::cout << stack;
          break;
        case exitprogram:
          return;
        default:
          std::cout << "Enter valid choice!" << std::endl;
      }
    }
    _getch();
  }
}

int main() {
  std::vector<int> sortedarr {1,2,3,4,5,6,7,8,9,10, 11, 12, 13, 14, 15};

  //BinarySearch& binsearch = BinarySearch::get();
  //binsearch.setArray(&sortedarr);
  //std::cout << "\nBinary Search -----\n";
  //binsearch.setTerm(10);

  //LinearSearch& linsearch = LinearSearch::get();
  //linsearch.setArray(&sortedarr);
  //std::cout << "\nLinear Search -----\n";
  //linsearch.setTerm(5);

  //FibonacciSearch& fibsearch = FibonacciSearch::get();
  //fibsearch.setArray(&sortedarr);
  //std::cout << "\nFibonacci Search -----\n";
  //fibsearch.setTerm(12);
  stackMenu();


  return 0;
}