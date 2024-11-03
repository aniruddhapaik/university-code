#include <iostream>
#include <vector>

// defining a class
class Node {
// protected:
// leaving them as private, just for demonstration purpose
// but I would use them as protected if I was developing a real program with this Node class
    int value;
    Node* next;

public:
    // constructor
    Node(int val) {
        this->value = val;
        this->next = nullptr;
    }

    // overloading constructor
    Node(int val, Node* nextptr) {
        this->value = val;
        this->next = nextptr;
    }
    // or can by done this way too:
    /*
    Node(int val, Node* ptr) : value(val), next(nextptr) {}
    */

    // virtual keyword enables polymorphism
    virtual const void printNode() const {
        std::cout << "\nSingly Linked Node ------\n" \
                  << this \
                  << "\nNext Value: " << (this->next == nullptr ? "null" : "exists") << std::endl;
    }

    int getValue() const { return this->value; }
    Node* getNext() const { return this->next; }

    // non-member, operator overloading
    friend std::ostream& operator<< (std::ostream&, const Node*);
};

// operator overloading
inline std::ostream& operator<< (std::ostream& COUT, const Node* node) {
    COUT << "Value: " << node->value;
    return COUT;
}

// inheritance
class PriorityQueueNode : virtual public Node { // virtual inheritance to resolve diamond problem
private:
    int priority;

public:
    PriorityQueueNode(int val, int prn, Node* nextptr=nullptr) : Node(val, nextptr) {
        this->priority = prn;
    }

    int getPriority() const { return this->priority; }

    // override keyword ensures correct function overriding
    const void printNode() const override {
        std::cout << "\nPriority Queue Node -----\n" \
                  << this \
                  << "\nNext Value: " << (this->getNext() == nullptr ? "null" : "exists") << std::endl;
    }

    friend std::ostream& operator<< (std::ostream&, const PriorityQueueNode*);
};

inline std::ostream& operator<< (std::ostream& COUT, const PriorityQueueNode* node) {
    std::cout << "Value: " << node->getValue() << ", Priority: " << node->priority;
    return COUT;
}

class DoubleNode : virtual public Node { // virtual inheritance to resolve diamond problem
private:
    Node* previous;

public: 
    DoubleNode(int val, Node* nextptr, Node* prev=nullptr) : Node(val, nextptr) {
        this->previous = prev;
    }

    Node* getPrevious() const { return this->previous; }

    const void printNode() const override {
        std::cout << "\nDoubly Linked Node ------" \
                  << "\nPrevious Value: " << (this->getPrevious() == nullptr ? "null\n" : "exists\n") 
                  << this \
                  << "\nNext Value: " << (this->getNext() == nullptr ? "null" : "exists") << std::endl;
    }
};

class PriorityDoubleNode : public PriorityQueueNode, public DoubleNode {
public:
    PriorityDoubleNode(int val, int prn, Node* prev = nullptr, Node* next = nullptr) 
        : PriorityQueueNode(val, prn, next), DoubleNode(val, next, prev), Node(val, next) {}
    
    const void printNode() const override {
        std::cout << "\nDoubly Linked Priority Queue Node ------" \
                  << "\nPrevious Value: " << (this->getPrevious() == nullptr ? "null\n" : "exists\n") 
                  << (PriorityQueueNode*) this \
                  << "\nNext Value: " << (this->getNext() == nullptr ? "null" : "exists") << std::endl;
    }
};

class LinkedList {
private:
    std::vector<Node>* list;

public:
    LinkedList() {
        this->list = nullptr;
    }
};

int main() {
    // using the class
    Node* node = new Node(50);
    node->printNode();

    Node* pq_node = new PriorityQueueNode(20, 10);
    pq_node->printNode();

    Node* db_node = new DoubleNode(55, pq_node, node);
    db_node->printNode();

    Node* pq_db_node = new PriorityDoubleNode(100, 1, node, pq_node);
    pq_db_node->printNode();

    return 0;
}