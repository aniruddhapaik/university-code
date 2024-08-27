#include <stack>
#include <string>
#include "../input_utils.h"

class InfixToPrefix {
private:
  std::stack<char>* operator_stack = nullptr;
  std::string infix_expression;
  std::string prefix_expression;
  const std::string supported_operators = "()^/*+-";

  bool handleInput() {
    std::getline(std::cin, this->infix_expression);
    if(std::cin.fail()) {
      if (std::cin.eof()) { std::cout << "Reached end of input (EOF)." << std::endl; }
      else { std::cout << "Enter valid input!" << std::endl; }
      return false;
      clearAndResetInputState();
    } else { return true; }
  }

  void reverseString(std::string& str) {
    // to reverse just put elements one by one in a stack, beginning from the left.
    std::stack<char> reverse;
    for (char c : str) {
      reverse.push(c);
    }

    str = "";

    while(not reverse.empty()) {
      str.push_back(reverse.top());
      reverse.pop();
    }
  }

  void convertToPrefix() {
    for(char c : this->infix_expression) {
      //std::cout << this->operator_stack->size() << " " << this->prefix_expression << std::endl;
      if (c == ' ') { continue; }
      if (this->supported_operators.find(c) == std::string::npos) {
        this->prefix_expression.push_back(c); // if the character read is an operand, it will be pushed to the expression buffer
      } else { 
        // Checking which operator it was and its precedence then its associativity 
        //   to perform operations on the operators' stack.
        if (c == '(') { 
            this->popStackUntilClosingBracket();
            continue;
        }
        while (this->checkTopStatus(c) == false) {
            this->prefix_expression.push_back(this->operator_stack->top());
            this->operator_stack->pop();
        }
        this->operator_stack->push(c);
      }
    }
    while(not this->operator_stack->empty()) {
        this->prefix_expression.push_back(this->operator_stack->top());
        this->operator_stack->pop();
    }
    this->reverseString(this->prefix_expression);
    this->printPrefixExpression();
  }

  bool checkTopStatus(char c) {
    if (this->operator_stack->empty()) { return true; } // next incoming operator can be pushed without further check
    else if (c == ')') { return true;}
    else if (c == '^') {
      if (this->operator_stack->top() == '^') { return false; } // because associativity for this is right to left
      else { return true; }
    } else if (c == '/' or c == '*') {
      if (((std::string)"^").find(this->operator_stack->top()) != std::string::npos) { return false; } // precedence lower
      else if (((std::string)")/*+-").find(this->operator_stack->top()) != std::string::npos) { return true; } // precedence equal or higher
    } else if (c == '+' or c == '-') {
      if (((std::string)"^/*").find(this->operator_stack->top()) != std::string::npos) { return false; }
      else if (((std::string)")+-").find(this->operator_stack->top()) != std::string::npos) { return true; }
    }
    return false;
  }

  void popStackUntilClosingBracket() {
    if (not this->operator_stack->empty()) {
      while(this->operator_stack->top() != ')') {
        // std::cout << this->operator_stack->size() << " | ";
        // std::cout << this->operator_stack->top();
        char top = this->operator_stack->top();
        this->prefix_expression.push_back(top);
        this->operator_stack->pop();

         if (this->operator_stack->empty()) { 
           std::cout << "Matching brackets error!" << std::endl;
           return; 
         }
      }
      this->operator_stack->pop(); // because ')' is at the top.
    }
  }

  const void printPrefixExpression() const {
    std::cout << "\nPrefix Expression:\n  ";
    std::cout << this->prefix_expression << "\n----------------\n" << std::endl;
  }

public:
  InfixToPrefix() {
    if (this->operator_stack == nullptr) { this->operator_stack = new std::stack<char>; }
    else {
      delete this->operator_stack;
      this->operator_stack = new std::stack<char>;
    }
    this->infix_expression = "";
    this->prefix_expression = "";
  }

  InfixToPrefix(std::string& infixexpr) {
    std::cout << "** Infix to Prefix **" << std::endl;

    if (this->operator_stack == nullptr) { this->operator_stack = new std::stack<char>; }
    else {
      delete this->operator_stack;
      this->operator_stack = new std::stack<char>;
    }
    this->infix_expression = infixexpr;
    this->prefix_expression = "";
    
    this->convertToPrefix();
  }

  void enterInfix(std::string* expr = nullptr) {
    if (expr == nullptr) {
      std::cout << "Enter expression: " << std::flush;
      if (this->handleInput()) {
        std::cout << "You Entered Infix Expression:\n" << this->infix_expression << std::endl;
        this->reverseString(this->infix_expression);
        this->convertToPrefix();
      }
    } else {
      this->infix_expression = *expr;
      this->prefix_expression = "";
      std::cout << "\nTesting:\n  " << this->infix_expression << std::endl;
      if (this->operator_stack == nullptr) { this->operator_stack = new std::stack<char>; }
      else {
        delete this->operator_stack;
        this->operator_stack = new std::stack<char>;
      }
      this->reverseString(this->infix_expression);
      std::cout << "Reversed:\n  " <<  this->infix_expression << std::endl;
      this->convertToPrefix();
    }
  }
};