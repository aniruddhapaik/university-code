#include <iostream>
#include <string>

class SomeClass {
 public:
  SomeClass(std::string str) {
    std::cout << "\nThis is " << str
              << " of class SomeClass that just got instantiated\n"
              << std::endl;
  }
};

int main() {
  SomeClass ObjectOne(std::string("Object One"));
  SomeClass ObjectTwo(std::string("Object Two"));
  return 0;
}