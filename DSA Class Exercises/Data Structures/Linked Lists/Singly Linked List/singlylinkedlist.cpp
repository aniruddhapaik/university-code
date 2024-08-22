#include "../../../input_utils.cpp"

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

    const void printReturnDefault() const {
        std::cout << "Returning default value..." << std::endl;
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

        if (temp->next->key == val) { return temp; }
        else {
            std::cout << "Key not found!" << std::endl;
            return nullptr;
        }
    }

    void addNodeAfter(Node* parent) {
        parent->next = new Node(this->last_input, parent->next);
        this->listsize++;
        return;
    }

    void popNodeAfter(Node* parent) { // expects the parent node of the node the user wants to delete.
        Node* temp = parent->next;
        parent->next = parent->next->next;
        if (parent->next == nullptr) { this->Tail = parent; }
        delete temp;
        this->listsize--;
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
            Node* temp = this->Head->next;
            delete this->Head; // freeing memory
            this->listsize--; // decreasing the size counter
            this->Head = temp;
            if (this->Head == nullptr) { this->Tail = nullptr; }
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
            Node* temp = this->Head;

            while(temp->next->next != nullptr) { // this runs if there are at least 2 nodes
                // traversing to the parent of the last node 
                // to delete the last node and set its parent->next pointer to nullptr
                temp = temp->next;
            }
            delete temp->next; // freeing the memory, NO MEMORY LEAKS!
            this->listsize--;
            temp->next = nullptr;
            this->Tail = temp; // assigning new tail
        }
        return;
    }

    void addBefore() {
        if (this->isEmpty()) { 
            this->printEmpty(); 
            std::cout << "So add a new key.\n";
            this->pushFront(); 
            // since list is empty, addAfter() automatically switches to pushing to the list,
            // so now pushFront() or pushBack() would result in doing the same thing.
        } else {
            if (this->listsize == 1) { // checking if only one node exists
                std::cout << "Only one node exists.\n-> Adding new head.." << std::endl;
                this->pushFront();
                // since there is only one node, adding before would mean you want to add to the before the only node there is.
                // so, addBefore() switches to becoming pushFront()
                return;
            } else {
                std::cout << "Enter the key before which you want to add new key.\nFind key: " << std::flush;
                if (this->handleInput()) {
                    if (this->Head->key == this->last_input) {
                        // even though there are more than 1 node, in case you still want to add before the first node...
                        // ...addBefore() automatically switches to pushFront() function
                        this->pushFront();
                        return;
                    } else {
                        // executes when you want to add somewhere after the first head node.
                        Node* node_parent = this->findNodeBefore(this->last_input);
                        // suppose you want to add to a certain node, 
                        // findNodeBefore() gets the parent node of the node before which you want to add a new node
                        if (node_parent == nullptr) { return; } 
                        // if the node requested for is not found, the above evaluates to true
                        else { 
                            // getting user to enter new key to actually create a node before requested node
                            std::cout << "Enter key to add before " << this->last_input << ": " << std::flush;
                            if (this->handleInput()) { addNodeAfter(node_parent); }
                            return;
                        }
                    }
                }
            }
        }
    }

    void addAfter() {
        if (this->isEmpty()) { 
            this->printEmpty();
            std::cout << "So add a new key.\n";
            this->pushBack(); 
            // since list is empty, addAfter() automatically switches to pushing to the list.
            // pushFront() or pushBack() would result in doing the same thing.
        } else {
            if (this->listsize == 1) {
                std::cout << "Only one node exists.\nAdding a new tail.." << std::endl;
                this->pushBack();
                // since there is only one node, choosing to addAfter can only mean you are want to add to the end of the list.
                return;
            } else {
                std::cout << "Enter the key after which you add new key.\nFind key: " << std::flush;
                if (this->handleInput()) {
                    // in case user wants to assign after the tail
                    if (this->Tail->key == this->last_input) {
                        this->pushBack();
                        return;
                    } else if (this->Head->key == this->last_input) {
                        // the function findNodeBefore(int) does not account for the head node, so
                        std::cout << "Enter key to add after " << this->last_input << ": " << std::flush;
                        if (this->handleInput()) { this->addNodeAfter(this->Head); }
                        return;
                        // I don't need to check if the head->next is a nullptr or not, 
                        //   it is guaranteed that the listsize is > 1, so the head->next is definitely not nullptr.
                    } else {
                        // Although findNodeBefore returns the node before the node of interest,
                        // we can just move to the next node, after which we can add a node after it.
                        // It is guaranteed that the node after which the user wants to add is not the current tail node,
                        // because that case has already been handled
                        Node* parent = this->findNodeBefore(this->last_input);
                        if (parent == nullptr) { return; } // checking node requested for exists or not
                        else {
                            std::cout << "Enter key to add after " << this->last_input << ": " << std::flush;
                            if (this->handleInput()) { addNodeAfter(parent->next); }
                            return;
                        }
                    }
                }
            }
        }
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
                        return;
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
                        Node* parent = this->findNodeBefore(this->last_input);
                        if (parent == nullptr) { return; }
                        else { this->popNodeAfter(parent); }
                    } 
                }
            }
        }
        return;
    }

    int peekIndex() {
        if (this->isEmpty()) {
            this->printEmpty();
        } else { 
            if (this->listsize > 1) {
                std::cout << "The list size is " << this->listsize;
                std::cout << "\nEnter a number in the range of [0, " << this->listsize-1 << "]";
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
                std::cout << "\nEnter a number in the range of [0, " << this->listsize-1 << "]";
                std::cout << "\nEnter index at which key is to be deleted: " << std::flush;
                if (this->handleInput()) { // enter index of node to deleted
                    if (this->last_input == 0) {
                        // if the index at which the user wants to delete is 0,
                        // that means it's a popFront() operation.
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
                        popNodeAfter(parent);
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
                std::cout << "(1 = yes, any integer = NO)(Default is NO): " << std::flush;
                this->last_input = 0; // purposely setting it to 0, since default is NO
                if (this->handleInput()) {
                    if (this->last_input == 1) {
                        std::cout << "Deleting the only key there is...\n";
                        popBack();
                    } else {
                        std::cout << "Not performing any deletion\n";
                    }
                }
            }
        }
        return;
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