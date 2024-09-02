#include "../../input_utils.h"

struct Node {
  int value;
  Node* next;

  Node(int key) {
    value = key;
    next = nullptr;
  }
  Node(int key, Node* node) {
    value = key;
    next = node;
  }
};

class CircularLinkedList {
private:
  Node* headnode;
  Node* tailnode;
  size_t listsize;
  int last_input;

  bool handleInput() {
    std::cin >> this->last_input;
    if (std::cin.fail()) {
      if (std::cin.eof()) { std::cout << "Reached end of input (EOF)." << std::endl; }
      else { std::cout << "Error: Enter valid integer!" << std::endl; }
      clearAndResetInputState();
      return false;
    } else { return true; }
  }
  
  Node* findNode() {
    Node* temp {this->headnode};
    while (temp != this->tailnode) {
      if (this->last_input == temp->value) { return temp; }
      temp = temp->next;
    }
    return nullptr;
  }

  Node* findNodeBefore() { // it is guaranteed the listsize is atleast 2
    Node* temp {this->headnode};
    while(temp->next->next != this->headnode) {
      if (this->last_input == temp->next->value) { return temp; }
      temp = temp->next;
    }
    if (this->last_input == temp->next->value) { return temp; }
    std::cout << "Node with key not found!" << std::endl;
    return nullptr;
  }

  void popFront() {
    if (this->listsize == 0) { std::cout << "List is empty!" << std::endl; }
    else {
      if (this->listsize == 1) {
        delete this->headnode;
        this->headnode = this->tailnode = nullptr;
        this->listsize = 0;
      } else {
        Node* temphead = this->headnode;
        this->headnode = this->headnode->next; // assigning new head
        this->tailnode->next = this->headnode; // linking the new head node after the tail node
        delete temphead; // deleting old head and freeing memory
        this->listsize--;
      }
    }
  }

  void popBack() {
    if (this->listsize == 0) { std::cout << "List is empty!" << std::endl; }
    else {
      if (this->listsize == 1) {
        delete this->headnode;
        this->headnode = this->tailnode = nullptr;
        this->listsize = 0;
      } else {
        Node* nodeparent = this->findNodeBefore();
        Node* node_to_del = nodeparent->next;
        nodeparent->next = node_to_del->next; // assigned the head node
        delete node_to_del;
        this->listsize--;
        this->tailnode = nodeparent;
      }
    }
  }

  const void printReturnDefault() const { std::cout << "Returning default value." << std::endl; }

public:
  CircularLinkedList() {
    this->headnode = nullptr;
    this->tailnode = nullptr;
    this->listsize = 0;
    this->last_input = 0;
  }

  int pushFront() {
    std::cout << "Enter key to push in front: " << std::flush;
    if (this->handleInput()) {
      if(this->listsize == 0) {
        this->headnode = new Node(this->last_input);
        this->tailnode = this->headnode;
        this->tailnode->next = this->headnode; // headnode points to itself
      } else {
        this->headnode = new Node(this->last_input, this->headnode);
        this->tailnode->next = this->headnode;
      }
      this->listsize++;
      return this->last_input;
    }
    return -1;
  }
    
  int pushBack() {
    std::cout << "Enter key to push back: " << std::flush;
    if (this->handleInput()) {
      if (this->listsize == 0) {
        this->headnode = new Node(this->last_input);
        this->tailnode = this->headnode;
        this->tailnode->next = this->headnode; // headnode points to itself
      } else {
        this->tailnode->next = new Node(this->last_input, this->headnode);
        this->tailnode = this->tailnode->next;
      }
      this->listsize++;
      return this->last_input;
    } else { this->printReturnDefault(); }
    return -1;
  }

  int pushAfter() {
    if (this->listsize == 0) {
      // if the list is empty anyway, just push back
      this->pushBack();
    } else {
      this->displayList();
      if (this->listsize == 1) {
        this->pushBack();
        return this->last_input;
      }
      std::cout << "Enter after which node value you want to push new node: " << std::flush;
      if (this->handleInput()) {
        if (this->last_input == this->tailnode->value) {
          this->pushBack();
          return this->last_input;
        } else {
          Node* temp = this->findNode();
          if (temp == nullptr) {
            std::cout << "Node not found!" << std::endl;
            this->printReturnDefault();
          } else {
            std::cout << "Enter key you want to insert: " << std::flush;
            if (this->handleInput()) {
              temp->next = new Node(this->last_input, temp->next);
              this->listsize++;
              return this->last_input;
            } else { this->printReturnDefault(); }
          }
        }
      } else { this->printReturnDefault(); }
    }
    return -1;
  }

  void deleteKey() {
    if (this->listsize == 0) {
      std::cout << "List is empty! can't perform delete operation" << std::endl;
    } else {
      if (this->listsize == 1) { // since only one node is left, deleting that
        std::cout << "Delete the only node left?\n(1 = yes, 0 = no; no is default): " << std::flush;
        if (this->handleInput()) {
          if (this->last_input == 1) {
            this->popFront();
            return;
          }
        }
      } else {
        this->displayList();
        std::cout << "Delete which value?: " << std::flush;
        if (this->handleInput()) {
          if (this->last_input == this->headnode->value) {
            this->popFront();
            return;
          } else if (this->last_input == this->tailnode->value) {
            this->popBack();
            return;
          } else {
            Node* nodeparent = this->findNodeBefore();
            if (nodeparent != nullptr) {
              Node* node_to_del = nodeparent->next;
              nodeparent->next = node_to_del->next;
              delete node_to_del;
              this->listsize--;
            }
          }
        }
      }
    }
  }

  const size_t getListSize() const {
    if (this->listsize == 0) { std::cout << "List is empty!" << std::endl; }
    else { std::cout << "List size is: " << this->listsize << std::endl; }
    return this->listsize;
  }

  const void displayList() const {
    if (this->listsize == 0) {
      std::cout << "List is empty!" << std::endl;
    } else {
      std::cout << "Displaying List: " << std::endl;
      Node* temp {this->headnode};
      while(temp != this->tailnode) {
        std::cout << temp->value << " | ";
        temp = temp->next;
      }
      std::cout << temp->value << " | -> HEAD: " << temp->next->value << std::endl; // the tail node value
    }
  }
};