#pragma once
#include <vector>
#include <iostream>

class Queue {
public:
  Queue();
  void enQueue(int);
  void deQueue();
  const void empty() const;
  const void size() const;
  const void front() const;
  const void printQueue() const;

private:
  std::vector<int>* queue;
};

std::ostream& operator<< (std::ostream& COUT, const Queue&);