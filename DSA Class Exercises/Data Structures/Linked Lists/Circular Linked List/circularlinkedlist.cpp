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
public:
    CircularLinkedList() {
        this->headnode = nullptr;
        this->tailnode = nullptr;
        this->listsize = 0;
        this->last_input = 0;
    }

    int pushFront() {}
    
    int pushBack() {}

    int pushAfter() {}

    void deleteKey() {}

    const void displayList() const {
        if (this->listsize == 0) {
            std::cout << "List is empty!" << std::endl;
        } else {
            Node* temp {this->headnode};
            while(temp != this->tailnode) {
                std::cout << temp->value << " | ";
                temp = temp->next;
            }
            std::cout << temp->value << std::endl; // the tail node value
        }
    }
};