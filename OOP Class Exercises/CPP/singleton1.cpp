#include <iostream>

class Node {
  static Node instance;
  int key = 0;

 public:
  static Node& getNode() { return Node::instance; }
  const void printVar() const { std::cout << key << std::endl; }

 private:
  Node(int k) { this->key = k; }
  Node(const Node&) = delete;
  Node& operator=(const Node&) = delete;
};

Node Node::instance(10);

int main() {
  Node& node = Node::getNode();
  return 0;
}