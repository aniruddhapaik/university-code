#include <iostream>
#include <string>

struct Node {
  int value;
  Node* next;

  Node(int val, Node* nextptr = nullptr) {
    this->value = val;
    this->next = nextptr;
  }

  Node(const Node* other) {
    this->value = other->value;
    this->next = nullptr;
  }
};

class Stack {
 private:
  Node* head = nullptr;
  Node* tail = nullptr;
  size_t stacksize = 0;

 public:
  void operator+=(int val) {
    if (this->head == nullptr) {
      this->head = this->tail = new Node(val);
    } else {
      this->tail->next = new Node(val);
      this->tail = this->tail->next;
    }
    this->stacksize++;
    std::cout << "\nPushed" << std::endl;
  }

  Stack operator--(int) {
    if (this->head == nullptr) {
      std::cout << "Stack is empty! can't delete" << std::endl;
    } else if (this->stacksize == 2) {
      delete this->tail;
      this->stacksize--;
      this->head->next = nullptr;
      this->tail = this->head;
    } else {
      Node* tempnode = this->head;
      while (tempnode->next->next != nullptr) {
        tempnode = tempnode->next;
      }
      delete tempnode->next;
      this->stacksize--;
      this->tail = tempnode;
      this->tail->next = nullptr;
    }
    std::cout << "\nPopped" << std::endl;
    return *this;
  }

  Node* top() const {
    if (this->stacksize) {
      return this->tail;
    } else {
      return nullptr;
    }
  }

  friend std::ostream& operator<<(std::ostream&, const Stack&);
  friend std::ostream& operator<<(std::ostream&, const Node*);
};

std::ostream& operator<<(std::ostream& COUT, const Node* node) {
  if (node == nullptr) {
    COUT << "ERROR: Invalid node!" << std::endl;
  } else {
    COUT << node->value << std::flush;
  }

  return COUT;
}

std::ostream& operator<<(std::ostream& COUT, const Stack& stack) {
  if (stack.stacksize) {
    Node* temp = stack.head;
    COUT << "\nStack: ";
    while (temp != nullptr) {
      COUT << " | " << temp;
      temp = temp->next;
    }
    COUT << " <- Top" << std::endl;
  } else {
    COUT << "Stack is empty!" << std::endl;
  }

  return COUT;
}

int main() {
  Stack stack;
  std::cout << stack;
  std::cout << stack.top();

  stack += 10;
  std::cout << stack;
  std::cout << stack.top();

  stack += 20;
  std::cout << stack;
  std::cout << stack.top();

  stack--;
  std::cout << stack;
  std::cout << stack.top();

  stack += 40;
  stack += 50;

  std::cout << stack;
  std::cout << stack.top();

  Node copied_top(stack.top());
  std::cout << "\nOriginal Stack Top: " << stack.top();
  std::cout << "\nCopied top: " << &copied_top;

  std::cout << "\nAdding next node to Copied Top (it should not affect the "
               "original top's next node, which should remain nullptr)\n";
  Node* nextnode_after_copied_top = new Node(100);
  copied_top.next = nextnode_after_copied_top;

  std::cout << "\nNext node of Stack's Top: "
            << (stack.top()->next == nullptr
                    ? std::string("Null")
                    : std::to_string(stack.top()->next->value))
            << std::endl;
  std::cout << "\nNext node of Copied Top: " << copied_top.next->value
            << std::endl;

  return 0;
}