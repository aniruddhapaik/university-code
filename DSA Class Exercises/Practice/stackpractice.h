#pragma once
#include <vector>
#include <iostream>

class Stack {
public:
  Stack();
  void push(int);
  int top();
  int pop();
  bool empty();
  size_t size();
  const void printStack() const;

private:
  std::vector<int>* stack;
};

std::ostream& operator<<(std::ostream& COUT, const Stack& stack);