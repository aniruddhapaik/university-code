#include <conio.h>

#include <cstdlib>
#include <iosfwd>
#include <iostream>
#include <limits>

#include "MinHeapPriorityQueue.h"

bool handleInput(int& input) {
  std::cin >> input;
  if (std::cin.fail()) {  // cin fail
    if (std::cin.eof()) {
      std::cout << "\nReached end of input (EOF)" << std::endl;
    } else {
      std::cout << "\nEnter valid integer!" << std::endl;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return false;
  } else {
    return true;
  }
}

class QueueNode {
 public:
  QueueNode(int k, int p) {
    this->key = k;
    this->costorpriority = p;
  }

 public:
  int key;
  int costorpriority;
};

int main() {
  MinHeapPriorityQueue<QueueNode> queue;

  int choice{};
  int key{};
  int costorpriority{};

  while (true) {
    system("cls");
    std::cout << "Min heap costorpriority Queue\n";
    std::cout << "0. Enqueue\n";
    std::cout << "1. Dequeue\n";
    std::cout << "2. Exit\n";
    std::cout << "\nEnter choice: " << std::flush;

    if (handleInput(choice)) {
      switch (choice) {
        case 0:
          std::cout << "Enter key: " << std::flush;
          if (handleInput(key)) {
            std::cout << "Enter costorpriority: " << std::flush;
            if (handleInput(costorpriority)) {
              QueueNode* temp = new QueueNode(key, costorpriority);
              queue.enqueue(temp);
            }
          }

          queue.displayQueue();
          break;

        case 1:
          queue.displayQueue();
          queue.dequeue();
          queue.displayQueue();
          break;
        case 2:
          return 0;
        default:
          std::cout << "Invalid choice!" << std::endl;
      }
    }

    _getch();
  }

  return 0;
}