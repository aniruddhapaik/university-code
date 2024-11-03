#include <iostream>

class Node {
 public:
  static Node& getNode() { return Node::instance; }
  int getKey() { return this->key; }

 private:
  Node(int k) { this->key = k; }
  Node(const Node&) = delete;
  Node& operator=(const Node&) = delete;

 private:
  int key;
  static Node instance;
};

Node Node::instance(10);

int main() {
  Node& node = Node::getNode();
  std::cout << node.getKey() << std::endl;
  return 0;
}