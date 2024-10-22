#include <iostream>
#include <vector>
#include <limits>
#include <conio.h>

const std::vector arr {1, 4, 10, 8, 27, 19, 15, 11, 20, 32, 46, 34};

bool search(int key) {
  for (size_t i = 0; i < arr.size(); i++) {
    if (key == arr.at(i)) {
        std::cout << "Value has been found at index: " << i << std::endl;
        return true;
    }
  }
  return false;
}

int main() {
  int key{};
  while(1) {
    system("cls");
    std::cout << "Linear Search\nPress CTRL+C to quit" << std::endl;
    std::cout << "Enter a value to search in array: ";
    if (std::cin >> key) {
      if (not search(key)) {
          std::cout << "Value not found!" << std::endl;
      }
    } else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Enter a valid number!" << std::endl;
    }
    _getch();
}

  return 0;
}

