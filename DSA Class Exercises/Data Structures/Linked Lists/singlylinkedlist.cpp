#include "../../input_utils.cpp"

#define DEFAULT -1;

struct Node {
    int key;
    Node* next;

    Node(int value) {
        key = value;
        next = nullptr;
    }
    Node(int value, Node* nextptr) {
        key = value;
        next = nextptr;
    }
};

class SinglyLinkedList {
private:
    Node* Head;
    Node* Tail;
    size_t listsize;
    int last_input;

    bool handleInput() {
        std::cin >> this->last_input;
        if (std::cin.fail()) { 
            clearAndResetInputState();
            if (std::cin.eof()) {
                std::cout << "Reached end of input (EOF)." << std::endl;
            } else {
                std::cout << "Error: Invalid input. Enter integer only." << std::endl;
            }
            return false; 
        }
        else {
           return true;
        }
    }

    const void printEmpty() const {
        std::cout << "The list is empty!" << std::endl;
        return;
    }

    Node* findNodeBefore(int val) {
        Node* temp = this->Head;

        while(temp->next->next != nullptr) {
            if (temp->next->key == val) {
                return temp;
            }
            temp = temp->next;
        }

        if (temp->next->key == val) {
            return temp;
        } else {
            std::cout << "Key not found!" << std::endl;
            return nullptr;
        }
    }

    void addNode(Node* parent) {
        parent->next = new Node(this->last_input, parent->next);
        this->listsize++;
        return;
    } 

public:
    SinglyLinkedList() {
        this->Head = nullptr;
        this->Tail = nullptr;
        this->listsize = 0;
        this->last_input = -1;
    }

    void pushFront() {
        std::cout << "Enter element to push at the beginning: " << std::flush;
        if (this->handleInput()) {
            if (this->Head == nullptr) {
                this->Head = new Node(this->last_input);
                this->Tail = this->Head;
            } else {
                this->Head = new Node(this->last_input, this->Head);
            }
            this->listsize++;
        }
        return;
    }

    void pushBack() {
        std::cout << "Enter element to push at the end: " << std::flush;
        if (this->handleInput()) {
            if (this->Tail == nullptr) {
                this->Head = new Node(this->last_input);
                this->Tail = this->Head;
            } else {
                this->Tail->next = new Node(this->last_input);
                this->Tail = this->Tail->next;
            }
            this->listsize++;
        }
        return;
    }

    bool isEmpty() const {
        if (this->listsize) { return false; }
        return true;
    }

    int getFront() const {
        if (this->isEmpty()) {
            this->printEmpty();
        } else {
            std::cout << "Value at the front: " << this->Head->key << std::endl;
            return this->Head->key;
        }
        return DEFAULT;
    }

    int getBack() const {
        if (this->isEmpty()) {
            this->printEmpty();
        } else {
            std::cout << "Value at the back: " << this->Tail->key << std::endl;
            return this->Tail->key;
        }
        return DEFAULT;
    }

    void popFront() {
        if (this->isEmpty()) { this->printEmpty(); }
        else {
            Node* temp = this->Head;
            this->Head = this->Head->next;
            if (this->Head == nullptr) { this->Tail = nullptr; }
            
            delete temp;
        }
        return;
    }

    void popBack() {
        if (this->isEmpty()) { this->printEmpty(); }
        else if (this->Head == this->Tail) {
            this->Head = nullptr;
            this->Tail = nullptr;
        } else {
            Node* temp = this->Head;

            while(temp->next->next != nullptr) {
                temp = temp->next;
            }
            delete temp->next; // deleting tail
            temp->next = nullptr;
            this->Tail = temp; // assigning new tail
        }
        return;
    }

    void addBefore() {
        if (this->isEmpty()) { this->printEmpty(); }
        else {
            if (this->listsize == 1) { // checking if only one node exists
                std::cout << "Only one node exists.\n-> Adding new head.." << std::endl;
                this->pushFront();
                return;
            } else {
                std::cout << "Enter the key before which you want to add new key.\nFind key: " << std::flush;
                if (this->handleInput()) {
                    if (this->Head->key == this->last_input) { // checking if wanting assign a new head node
                        this->pushFront();
                        return;
                    } else {
                        Node* node_parent = this->findNodeBefore(this->last_input);
                        if (node_parent == nullptr) { return; } // checking node requested for exists or not
                        else { // adding new key before requested node
                            std::cout << "Enter key to add: " << std::flush;
                            if (this->handleInput()) {
                                addNode(node_parent);
                                return;
                            }
                        }
                    }
                }
            }
        }
        return;
    }

    Node* findNode() {
        std::cout << "Find key: " << std::endl;
        if (this->handleInput()) {
            Node* temp = this->Head;

            while(temp != nullptr) {
                if (temp->key == this->last_input) {
                    std::cout << "Key" << this->last_input << " has been found!" << std::endl;
                    return temp;
                }
                temp = temp->next;
            }
            std::cout << "Key not found!" << std::endl;
            return nullptr;
        }
    }

    void addAfter() {
        if (this->isEmpty()) { 
            this->printEmpty();
            std::cout << "So add a new key.\n";
            this->pushFront();
        }
        else {
            if (this->listsize == 1) {
                std::cout << "Only one node exists.\nAdding a new tail.." << std::endl;
                this->pushBack();
            } else {
                std::cout << "Enter the key after which you add new key. " << std::endl;
                Node* parent = this->findNode();
                if (parent == nullptr) { return; } // checking node requested for exists or not
                else {
                    addNode(parent);
                }
            }
        }
    }

    void delKey() {
        if (this->isEmpty()) { 
            this->printEmpty(); 
            std::cout << "Can't perform delete operation" << std::endl;
            return;
        } else {
            
        }
    }
};
