#include <iostream>
#include <string>

class SomeClass {
 public:
  SomeClass() {
    std::cout << "\nThe constructor of that class is automatically called\n"
              << std::endl;
  }
};

int main() {
  std::cout << "As soon as you instantiate an Object of some class..\n";
  SomeClass ObjectOne;
  return 0;
}