#include <iostream>

class Node {
 public:
  Node(){};

  Node(const Node& n) {
    this->key = n.key;
    this->next = nullptr;
    std::cout << "Copy Constructor was called" << std::endl;
  }

  int key;
  Node* next;
};

int main() {
  Node node_one;
  node_one.key = 10;

  Node node_two;
  node_two.key = 20;
  node_two.next = &node_one;

  Node node_two_copy = node_two;

  std::cout << "\nNode two: \n"
            << "Key: " << node_two.key << '\n'
            << "Next node exists: " 
            << (node_two.next == nullptr ? "no" : "yes");

  std::cout << std::endl;

  std::cout << "\nNode two's copy: \n"
            << "Key: " << node_two_copy.key << '\n'
            << "Next node exists: " 
            << (node_two_copy.next == nullptr ? "no" : "yes");

  return 0;
}