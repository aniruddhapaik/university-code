#include <iostream>
#include <conio.h>
#include <vector>
#include <limits>

const std::vector<int> list{0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10,
                            11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

int searchterm = 0;

void binarysearch(size_t leftindex, size_t rightindex) {
  if (leftindex < rightindex) {
    size_t mid = (leftindex + rightindex) / 2;
    if (searchterm == list[mid]) {
      std::cout << "Found search term: " << searchterm << " at index: " << mid
                << std::endl;
      return;
    } else if (searchterm < list[mid]) {
      binarysearch(leftindex, mid);
    } else {
      binarysearch(mid + 1, rightindex);
    }
  } else {
    std::cout << "Not found search term: " << searchterm << std::endl;
  }
}

int main() {
  size_t listsize = list.size();
  int key{};
  while (1) {
    system("cls");
    std::cout << "Binary Search\nPress CTRL+C to quit" << std::endl;
    std::cout << "Enter a value to search in array: ";
    if (std::cin >> key) {
      searchterm = key;
      binarysearch(0, listsize);
    } else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Enter a valid number!" << std::endl;
    }
    _getch();
  }

  return 0;
}