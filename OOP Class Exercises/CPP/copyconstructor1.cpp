#include <iostream>
#include <string>

class Node {
 public:
  std::string nodename;
  int key;

  Node(std::string name, int k) {
    this->nodename = name;
    std::cout << this->nodename << "'s constructor was called" << std::endl;
    this->key = k;
    std::cout << "Key: " << this->key << std::endl;
  }

  Node(const Node& n) {
    this->nodename = std::string("copy-of-") + n.nodename;
    std::cout << this->nodename << "'s COPY constructor was called"
              << std::endl;
    this->key = n.key;
    std::cout << "Key: " << this->key << std::endl;
  }
};

Node someFunc(Node node) {
  std::cout << "Inside someFunc(), key of newly created node is " << node.key
            << std::endl;
  std::cout << "\nReturn a node by value from someFunc()" << std::endl;
  return node;
}

int main() {
  Node* node1 = new Node(std::string("Node One"), 1);

  std::cout << "\nPassing a node by value to someFunc()" << std::endl;
  Node node2 = someFunc(*node1);

  std::cout << "\nAfter returning from someFunc(), returned node's key: "
            << node2.key << std::endl;

  return 0;
}