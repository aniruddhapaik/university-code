#include <iostream>
#include <vector>
#include <limits>
#include <conio.h>

#define DEFAULT -1;

struct Node {
    int value;
    Node* next;

    Node() {
        value = 0;
        next = nullptr;
    }
    Node(int val) {
        value = val;
        next = nullptr;
    }
    Node(int val, Node* ptr) {
        value = val;
        next = ptr;
    }
};

class Queue {
private:
    Node* head;
    Node* tail;
    int last_input;
    int last_dequeued;
    int queuesize;

    bool getInput() {
        std::cout.flush();
        std::cout << "Enter value: ";
        if (std::cin >> this->last_input) { return true; } 
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter valid integer input!" << std::endl;
            return false;
        }
    }

    const void printStackIsEmpty() const {
        std::cout << "Queue is empty!" << std::endl;
        return;
    }

    const void printReturnDefault() const {
        std::cout << "-> returning default value..." << std::endl;
        return;
    }

public:
    Queue() {
        this->head = nullptr;
        this->tail =  nullptr;
        this->last_input = 0;
        this->last_dequeued = 0;
        this->queuesize = 0;
    }

    void enqueue() {
        if (this->getInput()) {
            if (this->queuesize) {
                this->tail->next = new Node(this->last_input);
                this->tail = this->tail->next;
            } else {
                this->head = new Node(this->last_input);
                this->tail = this->head;
            }
            this->queuesize++;
        }
        return;
    }

    int dequeue() {
        if (this->queuesize) {
            std::cout << "Dequeueing first element: " << this->head->value << std::endl;
            this->last_dequeued = this->head->value;
            Node* temp = this->head;
            this->head = this->head->next;
            if (temp == this->tail) { this->tail = this->head; }
            delete temp;
            this->queuesize--;
            return this->last_dequeued;
        } else {
            this->printStackIsEmpty();
            this->printReturnDefault();
            return DEFAULT;
        }
    }

    int firstElement() {
        if(this->queuesize) {
            std::cout << "First element is " << this->head->value << std::endl;
            return this->head->value;
        } else {
            this->printStackIsEmpty();
            this->printReturnDefault();
            return DEFAULT;
        }
    }

    int lastElement() {
        std::cout << "The last element in the Queue is " << this->tail->value << std::endl;
        return this->tail->value;
    }

    int getQueueSize() {
        std::cout << "The size of the Queue is " << this->queuesize << std::endl;
        return this->queuesize;
    }

    int peek() {
        if (this->queuesize) {
            std::cout << "There are " << this->queuesize << " element in the queue." << std::endl;
            if (this->queuesize > 1) { std::cout << "Enter index between 0 and " << (this->queuesize-1) << ".\n"; }
            else { std::cout << "The only index available to peek at is 0.\n"; }
            if(this->getInput()) {
                int counter = this->last_input;
                Node* temp = this->head;
                if (counter >= 0 and counter < this->queuesize) {
                    while(temp->next != nullptr) {
                        temp = temp->next;
                        counter--;
                    }
                    std::cout << "The element at index " << this->last_input << " is " << temp->value << std::endl;
                    return temp->value;
                } else {
                    std::cout << "index is out of bounds!" << std::endl;
                }
            }
        } else { this->printStackIsEmpty(); }
        this->printReturnDefault();
        return DEFAULT;
    }

    const void printQueue() const {
        if (this->queuesize) {
            std::cout << "Element in queue:\n";
            Node* temp = this->head;
            while(temp != nullptr) {
                std::cout << temp->value << ", ";
                temp = temp->next;
            }
        } else { this->printStackIsEmpty(); }
    }
};

int main() {
    Queue queue;
    int input{};

    enum menu {enqueue=0, dequeue, first_element, last_element, peek, printstack, sizeofstack, exitprogram};

    while(1) {
        system("cls");
        std::cout << "Queue implementation with singly linked list\n";
        std::cout << "Menu:\n";
        std::cout << "0 : Enqueue\n";
        std::cout << "1 : Dequeue\n";
        std::cout << "2 : First element\n";
        std::cout << "3 : Last element\n";
        std::cout << "4 : Peek at index\n";
        std::cout << "5 : Print queue\n";
        std::cout << "6 : Get size of queue\n";
        std::cout << "7 : Exit program\n";
        std::cout << "\nEnter menu choice >> " << std::flush;

        if(std::cin >> input) {
            switch (input)
            {
            case enqueue:
                queue.enqueue();
                break;
            case dequeue:
                queue.dequeue();
                break;
            case first_element:
                queue.firstElement();
                break;
            case last_element:
                queue.lastElement();
                break;
            case peek:
                queue.peek();
                break;
            case printstack:
                queue.printQueue();
                break;
            case sizeofstack:
                queue.getQueueSize();
                break;
            case exitprogram:
                return 0;
            default:
                std::cout << "Enter valid option!" << std::endl;
                break;
            }
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter valid input!" << std::endl;
        }
        _getch();
    }

    return 0;
}