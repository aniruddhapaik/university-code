#include <iostream>

struct Node {
    int key;
    Node* next;
};

class SinglyLinkedList {
private:
    Node* Head;
    Node* Tail;
    int last_input;

    bool handleInput() {
        if (std::cin >> this->last_input) { return true; }
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid Input!" << std::endl;
        }
        return false;
    }

public:
    SinglyLinkedList() {
        this->Head = nullptr;
        this->Tail = nullptr;
        this->last_input = -1;
    }
};
