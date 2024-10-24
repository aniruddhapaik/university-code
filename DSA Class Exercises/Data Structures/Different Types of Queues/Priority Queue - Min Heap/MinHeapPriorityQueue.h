#pragma once
#include <iostream>
#include <vector>

template <typename T>
class MinHeapPriorityQueue {
 public:
  void enqueue(T* node) {
    this->queue.emplace_back(node);
    this->heapifypush();
  }

  void dequeue() {
    if (this->queue.size()) {
      this->queue.erase(this->queue.begin());
      this->heapifydelete(0);
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
      std::cout << i->key << '(' << i->costorpriority << ") ";
    }
    std::cout << '\n' << std::endl;
  }

 private:
  void heapifypush() {
    if (this->queue.size() <= 1) {
      return;
    } else {
      size_t index = this->queue.size() - 1;

      while (index > 0) {
        size_t child = index;
        size_t parent = (child - 1) / 2;

        if (this->queue.at(child)->costorpriority <
            this->queue.at(parent)->costorpriority) {
          std::swap(this->queue.at(parent), this->queue.at(child));
        }
        index = parent;
      }
    }
  }

  size_t heapifydelete(size_t index) {
    if (((index * 2) + 2) < this->queue.size()) {
      size_t leftindex = this->heapifydelete((index * 2) + 1);
      size_t rightindex = this->heapifydelete((index * 2) + 2);

      T* leftchild = this->queue.at(leftindex);
      T* rightchild = this->queue.at(rightindex);

      if (leftchild->costorpriority <= rightchild->costorpriority) {
        if (leftchild->costorpriority < this->queue.at(index)->costorpriority) {
          this->swap(index, leftindex);
        }
      } else {
        if (rightchild->costorpriority <
            this->queue.at(index)->costorpriority) {
          this->swap(index, rightindex);
        }
      }
    } else if (((index * 2) + 1) < this->queue.size()) {
      size_t leftindex = (index * 2) + 1;
      T* leftchild = this->queue.at(leftindex);

      if (leftchild->costorpriority < this->queue.at(index)->costorpriority) {
        this->swap(index, leftindex);
      }
    }
    return index;
  }

  void swap(size_t first, size_t second) {
    T* temp = this->queue.at(first);
    this->queue.at(first) = this->queue.at(second);
    this->queue.at(second) = temp;
  }

 public:
  std::vector<T*> queue;
};