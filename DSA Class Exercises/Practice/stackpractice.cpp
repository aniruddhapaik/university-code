#include "stackpractice.h"

Stack::Stack() { this->stack = new std::vector<int>; }

void Stack::push(int key) { this->stack->push_back(key); }

int Stack::top() { 
  if (this->stack->size() > 0) {
    std::cout << "Top: " << this->stack->back() << std::endl;
    return this->stack->back();
  }
  std::cout << "Stack is empty!" << std::endl;
  return -1;
}

int Stack::pop() {
  if (this->stack->size() > 0) {
    int top = this->top();
    this->stack->resize(this->stack->size() - 1);
    std::cout << "Popped..." << std::endl;
    return top;
  }
  std::cout << "Stack is empty!" << std::endl;
  return -1;
}

bool Stack::empty() {
  if (this->stack->size()) {
    std::cout << "Stack is not empty." << std::endl;
    return false;
  }
  std::cout << "Stack is empty!" << std::endl;
  return true;
}

size_t Stack::size() { 
  std::cout << "Size of the stack: " << this->stack->size() << std::endl;
  return this->stack->size(); 
}

const void Stack::printStack() const {
  if (this->stack->size()) {
    std::cout << "Stack: \n";
    for (int& key: *(this->stack)) {
      std::cout << " | " << key;
    }
    std::cout << " <- Top" << std::endl;
    return;
  }
  std::cout << "Stack is empty!" << std::endl;
}

std::ostream& operator<<(std::ostream& COUT, const Stack& stack) { 
  stack.printStack();
  return COUT; 
}