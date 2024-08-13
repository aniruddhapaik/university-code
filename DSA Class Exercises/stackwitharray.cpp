#include <iostream>
#include <vector>
#include <limits>
#include <conio.h>

#define DEFAULT -1;

class Stack {
private:
    std::vector<int> stack;
    int last_popped;
    int last_input;

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
        std::cout << "Stack is empty!" << std::endl;
        return;
    }

    const void printReturnDefault() const {
        std::cout << "-> returning default value..." << std::endl;
        return;
    }

public:
    Stack() {
        this->stack = {};
        this->last_input = 0;
        this->last_popped = 0;
    }

    void push() {
        if(this->getInput()) { this->stack.push_back(this->last_input); }
        return;
    }

    int pop() {
        if (this->stack.size()) {
            this->last_popped = this->stack.back();
            std::cout << "Popping last element: " << this->last_popped << std::endl;
            this->stack.pop_back();
            return this->last_popped;
        } else {
            this->printStackIsEmpty();
            this->printReturnDefault();
            return DEFAULT;
        }
    }

    int topElement() {
        if(this->stack.size()) {
            std::cout << "Top element is " << this->stack.back() << std::endl;
            return this->stack.back();
        } else {
            this->printStackIsEmpty();
            this->printReturnDefault();
            return DEFAULT;
        }
    }

    int getStackSize() {
        if (this->stack.size()) { std::cout << "Stack size is: " << this->stack.size(); }
        else {this->printStackIsEmpty(); }
        return this->stack.size();
    }

    int peek() {
        size_t stacksize = this->stack.size();
        if (this->stack.size()) {
            std::cout << "There are " << stacksize << " element in the stack" << std::endl;
            std::cout << "Enter index between 0 and " << (stacksize-1) << ": ";
            this->getInput();
            if (this->last_input >= 0 and this->last_input < stacksize) {
                std::cout << "Element at index " << this->last_input << " is " << this->stack.at(this->last_input) << std::endl;
                return this->stack.at(this->last_input);
            } else {
                std::cout << "index is out of bounds!" << std::endl;
                this->printReturnDefault();
                return DEFAULT;
            }
        } else {
            this->printStackIsEmpty();
            this->printReturnDefault();
            return DEFAULT;
        }
    }

    const void printStack() const {
        if (this->stack.size()) {
            std::cout << "Elements in the stack:" << std::endl;
            for (int i: this->stack) {
                std::cout << i << " | ";
            }
            std::cout << std::endl;
        } else { this->printStackIsEmpty(); }
        return;
    }
};

int main() {
    Stack stack;
    int input{};

    enum menu {push=0, pop, top_element, peek, printstack, sizeofstack, exitprogram};

    while(1) {
        system("cls");
        std::cout << "Stack implementation with std::vector\n";
        std::cout << "Menu:\n";
        std::cout << "0 : Push\n";
        std::cout << "1 : Pop\n";
        std::cout << "2 : Top element\n";
        std::cout << "3 : Peek at index\n";
        std::cout << "4 : Print stack\n";
        std::cout << "5 : Get size of stack\n";
        std::cout << "6 : Exit program\n";
        std::cout << "\nEnter menu choice >> " << std::flush;

        if(std::cin >> input) {
            switch (input)
            {
            case push:
                stack.push();
                break;
            case pop:
                stack.pop();
                break;
            case top_element:
                stack.topElement();
                break;
            case peek:
                stack.peek();
                break;
            case printstack:
                stack.printStack();
                break;
            case sizeofstack:
                stack.getStackSize();
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