#include <iostream>

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
        std::cout << this << " | Next Value: " << (this->next == nullptr ? "null" : "exists") << std::endl;
    }

    const int getValue() const { return this->value; }
    const Node* getNext() const { return this->next; }

    // non-member, operator overloading
    friend std::ostream& operator<< (std::ostream&, const Node*);
};

// operator overloading
inline std::ostream& operator<< (std::ostream& COUT, const Node* node) {
    COUT << "Value: " << node->value;
    return COUT;
}

// inheritance
class PriorityQueueNode : public Node {
private:
    int priority;

public:
    PriorityQueueNode(int val, int prn) : Node(val) {
        this->priority = prn;
    }

    PriorityQueueNode(int val, int prn, Node* nextptr) : Node(val, nextptr) {
        this->priority = prn;
    }

    // override keyword ensures correct function overriding
    const void printNode() const override {
        std::cout << this << " | Next Value: " << (this->getNext() == nullptr ? "null" : "exists") << std::endl;
    }

    friend std::ostream& operator<< (std::ostream&, const PriorityQueueNode*);
};

inline std::ostream& operator<< (std::ostream& COUT, const PriorityQueueNode* node) {
    std::cout << "Value: " << node->getValue() << ", Priority: " << node->priority;
    return COUT;
}

int main() {
    // using the class
    Node* node = new Node(50);
    node->printNode();

    Node* pq_node = new PriorityQueueNode(20, 10);
    pq_node->printNode();

    return 0;
}