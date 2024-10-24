#pragma once
#include <iostream>
#include <vector>

template <typename T>
class PriorityQueueArray {
 public:
  void enqueue(T* node) {
    if (this->queue.size() == 0) {
      this->queue.emplace_back(node);
    } else {
      size_t index{0};
      while (index < this->queue.size()) {
        if (node->costorpriority < this->queue.at(index)->costorpriority) {
          this->queue.emplace(this->queue.begin() + index, node);
          return;
        }
        index++;
      }
      this->queue.emplace_back(node);
    }
  }

  void dequeue() {
    if (this->queue.size()) {
      this->queue.erase(this->queue.begin());
    }
  }

  T* getFront() {
    if (this->queue.size()) {
      return this->queue.at(0);
    }
    return nullptr;
  }

  const void displayQueue() const {
    for (auto& i : this->queue) {
      std::cout << '(' << i->costorpriority << ") ";
       //std::cout << i << '(' << i->costorpriority << ") ";
    }
    std::cout << '\n' << std::endl;
  }

 public:
  std::vector<T*> queue;
};