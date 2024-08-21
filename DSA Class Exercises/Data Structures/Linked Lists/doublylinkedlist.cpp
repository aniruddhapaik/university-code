#include "../../input_utils.cpp"

#define DEFAULT -1;

struct Node {
    Node* prev;
    Node* next;
    int key;

    Node(int value) {
        key = value;
        prev = nullptr;
        next = nullptr;
    }
    Node(int value, Node* previous, Node* nextptr) {
        key = value;
        prev = previous;
        next = nextptr;
    }
};

class DoublyLinkedList {
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

    const void printReturnDefault() const {
        std::cout << "Returning default value..." << std::endl;
        return;
    }

    void addNodeBefore(Node* node) {
        // if (node == this->Head) {
        //     this->Head = new Node(this->last_input, nullptr, this->Head);
        //     this->Head->next->prev = this->Head; // since the old head node's prev pointer was nullptr;
        // } else {
        // first going to the previous node
        Node* prev = node->prev;
        // creating and assigning new node's address to the next pointer of the previous node;
        // this previous node is the previous node of the current node before the addition of the new node in between them
        prev->next = new Node(this->last_input, prev, node);
        // assigning the appropriate address to the current node's previous node pointer...
        // ...which should now contain the new node's address
        node->prev = prev->next; // since prev->next is the new node
        // }
        this->listsize++;
        return;
    }

    void addNodeAfter(Node* node) {
        // if (node->next == nullptr) {
        //     // in case the node after which you want to add a new node is the current tail node
        //     this->Tail->next = new Node(this->last_input, this->Tail, nullptr); // Node(key, previous, next)
        //     this->Tail = this->Tail->next;
        // } else {
        Node* nextnode = node->next;
        nextnode->prev = new Node(this->last_input, node, nextnode);
        node->prev = nextnode->next; // since previous->next is the new node
        // }
        
        this->listsize++;
        return;
    }

    void popNode(Node* parent) { // expext the parent node of the node the user wants to delete.
        Node* temp = parent->next;
        parent->next = parent->next->next;
        delete temp;
        this->listsize--;
        return;
    }

public:
    DoublyLinkedList() {
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
                this->Head->prev = new Node(this->last_input, nullptr, this->Head);
                this->Head = this->Head->prev;
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
                this->Tail->next = new Node(this->last_input, this->Tail, nullptr); // key, previous, next
                this->Tail = this->Tail->next;
            }
            this->listsize++;
        }
        return;
    }

    bool isEmpty(bool printsize=false) const {
        if (this->listsize) { 
            if (printsize) { std::cout << "List size is " << this->listsize << std::endl; }
            return false; 
        }
        if (printsize) { this->printEmpty(); }
        return true;
    }

    int getFront() const {
        if (this->isEmpty()) {
            this->printEmpty();
        } else {
            std::cout << "Value at the front: " << this->Head->key << std::endl;
            return this->Head->key;
        }
        this->printReturnDefault();
        return DEFAULT;
    }

    int getBack() const {
        if (this->isEmpty()) {
            this->printEmpty();
        } else {
            std::cout << "Value at the back: " << this->Tail->key << std::endl;
            return this->Tail->key;
        }
        this->printReturnDefault();
        return DEFAULT; // if the list is empty, returning a default value
    }

    void popFront() {
        if (this->isEmpty()) { this->printEmpty(); }
        else {
            Node* newhead = this->Head->next;
            delete this->Head; // freeing memory
            this->listsize--; // decreasing the size counter
            this->Head = newhead;
            
            if (this->Head == nullptr) { this->Tail = nullptr; }
            else { this->Head->prev = nullptr; } // not to forget to set the previous node ptr to nullptr! since this node is the new head.
            // the above if statement is for the case there was only one node in the list before the deletion,
            // so assigning the tail to nullptr as well since the head now points to nullptr.
        }
        return;
    }

    void popBack() {
        if (this->isEmpty()) { this->printEmpty(); }
        else if (this->Head == this->Tail) {
            // this block runs if there was only one node, so popBack() would render the list empty.
            delete this->Head; // freeing memory
            this->listsize--;
            this->Head = nullptr;
            this->Tail = nullptr;
        } else {
            Node* newtail = this->Tail->prev; // first saving the previous node before the tail
            // then deleting the current tail from memory
            delete this->Tail; // freeing the memory, NO MEMORY LEAKS!
            this->listsize--; // reducing the list size counter
            newtail->next = nullptr; // making sure the new tail's next pointer is not a dangling pointer; setting it to nullptr
            this->Tail = newtail; // assigning new tail
        }
        return;
    }

    Node* findNode() {
        std::cout << "Find key: " << std::flush;
        if (this->handleInput()) {
            Node* temp = this->Head;
            // checking every node if its value matches the key the user is looking for
            while(temp != nullptr) { // evaluates to false once the tail->next is reached, since tail->next is nullptr
                if (temp->key == this->last_input) {
                    std::cout << "Key " << this->last_input << " has been found!" << std::endl;
                    return temp;
                }
                temp = temp->next;
            }
            // if the key has not been found 
            std::cout << "Key not found!" << std::endl;
        }
        return nullptr;
    }

    void addBefore() {
        if (this->isEmpty()) { 
            this->printEmpty();
            std::cout << "So add a new key.\n";
            this->pushFront(); 
            // since list is empty, addBefore() automatically switches to pushing a new node to the list.
            // pushFront() or pushBack() would result in doing the same thing.
        } else {
            if (this->listsize == 1) {
                std::cout << "Only one node exists.\nAdding a new head.." << std::endl;
                this->pushFront(); 
                // since there is only one node, choosing to addBefore can only mean you are want to add to the beginning of the list.
            } else {
                std::cout << "Enter the key before which you add a new key.\n";
                Node* node = this->findNode();
                if (node == nullptr) { return; } // checking node requested for exists or not
                else if (node == this->Head) { this->pushFront(); }
                else { 
                    std::cout << "Enter key to add: " << std::flush;
                    if (this->handleInput()) { addNodeBefore(node); }
                }
            }
        }
        return;
    }

    void addAfter() {
        if (this->isEmpty()) { 
            this->printEmpty();
            std::cout << "So add a new key.\n";
            this->pushBack(); 
            // since list is empty, addAfter() automatically switches to pushing a new node to the list.
            // pushFront() or pushBack() would result in doing the same thing.
        } else {
            if (this->listsize == 1) {
                std::cout << "Only one node exists.\nAdding a new tail.." << std::endl;
                this->pushBack(); 
                // since there is only one node, choosing to addAfter can only mean you are want to add to the end of the list.
            } else {
                std::cout << "Enter the key after which you add a new key.\n";
                Node* node = this->findNode();
                if (node == nullptr) { return; } // checking node requested for exists or not
                else if (node->next == nullptr) { this->pushBack(); }
                else { }
            }
        }
    }

    void delKey() {
        if (this->isEmpty()) { 
            this->printEmpty(); 
            std::cout << "Can't perform delete operation" << std::endl;
            return;
        } else {
            if (this->listsize == 1) {
                std::cout << "Do you want to delete the only key there is in the list?\n";
                std::cout << "(1 = yes, 0 = NO)(Default is NO): " << std::flush;
                this->last_input = 0; // purposely setting it to 0, since default is NO
                if (this->handleInput()) {
                    if (this->last_input == 1) {
                        std::cout << "Deleting the only key there is...\n";
                        popBack();
                    } else {
                        std::cout << "You have chosen to not delete the only key there is\n";
                        std::cout << "or you have not chosen option 1\n";
                    }
                }
                return;
            } else {
                std::cout << "Which key you want to delete: " << std::flush;
                if (this->handleInput()) {
                    if (this->Head->key == this->last_input) {
                        popFront();
                    } else if (this->listsize > 1) {
                        Node* parent = this->findNode(); // check this
                        if (parent != nullptr) { this->popNode(parent); }
                    } else {
                        std::cout << "Node was not found!" << std::endl;
                    }
                }
            }
        }
    }

    int peekIndex() {
        if (this->isEmpty()) {
            this->printEmpty();
        } else { 
            if (this->listsize > 1) {
                std::cout << "The list size is " << this->listsize;
                std::cout << "\nEnter index to peek at: " << std::flush;
                if (this->handleInput()) {
                    if (this->last_input >= 0 and this->last_input < this->listsize) {
                        // traverse the list until index is met.
                        size_t counter = this->last_input;
                        Node* temp = this->Head;
                        while (counter) {
                            temp = temp->next;
                            counter--;
                        }
                        std::cout << "Key at index " << this->last_input << " is " << temp->key << std::endl;
                        return temp->key;
                    } else {
                        std::cout << "Index is out of bounds!" << std::endl;
                    }
                } 
                // deleted else statement, for future reference
            } else {
                std::cout << "The only key in the list is " << this->Head->key << std::endl;
                return this->Head->key;
            }
        }
        this->printReturnDefault();
        return DEFAULT;
    }

    void delIndex() {
        if (this->isEmpty()) {
            this->printEmpty();
            return;
        } else {
            if (listsize > 1) {
                std::cout << "List size is " << this->listsize;
                std::cout << "\nEnter index at which key is to be deleted: " << std::flush;
                if (this->handleInput()) { // enter index of node to deleted
                    if (this->last_input == 0) {
                        // if the index at which the user wants to delete is 0,
                        // that means its a popFront() operation.
                        popFront();
                        return;
                    }
                    if (this->last_input > 0 and this->last_input < this->listsize) {
                        size_t counter = this->last_input - 1; 
                        // negating 1 purposely to first get to the parent of the node the user wants to delete.
                        Node* parent = this->Head;
                        while(counter) {
                            parent = parent->next;
                            counter--;
                        }
                        popNode(parent);
                        return;
                    } else {
                        std::cout << "Index is out of bounds!\n";
                        return;
                    }
                }
            } else {
                // if there is only one node, delIndex() would mean deleting the only node,
                // so doing popBack(). popFront() would work here too since there is only one node;
                std::cout << "Do you want to delete the only key there is in the list?\n";
                std::cout << "(1 = yes, 0 = NO)(Default is NO): " << std::flush;
                this->last_input = 0; // purposely setting it to 0, since default is NO
                if (this->handleInput()) {
                    if (this->last_input == 1) {
                        std::cout << "Deleting the only key there is...\n";
                        popBack();
                    } else {
                        std::cout << "You have chosen to not delete the only key there is\n";
                        std::cout << "or you have not chosen option 1\n";
                    }
                }
                
                return;
            }
        }
    }

    size_t getSize() {
        if (this->isEmpty()) {
            this->printEmpty();
            this->printReturnDefault();
            return DEFAULT;
        } 
        // else
        std::cout << "The list size is " << this->listsize << std::endl;
        return this->listsize;
    }

    const void printList() const {
        if (this->isEmpty()) {
            this->printEmpty();
            return;
        }
        // else 
        Node* temp = this->Head;
        std::cout << "Elements in list:\n| ";
        while(temp != nullptr) {
            std::cout << temp->key << " | ";
            temp = temp->next;
        }
        std::cout << "\n";
        return;
    }
};
