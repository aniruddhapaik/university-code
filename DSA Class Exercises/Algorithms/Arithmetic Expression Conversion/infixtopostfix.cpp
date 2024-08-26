#include <stack>
#include <string>
#include "input_utils.h"

class InfixToPostfix {
private:
  std::stack<char>* operator_stack = nullptr;
  std::string infix_expression;
  std::string postfix_expression;
  const std::string supported_operators = "()^/*+-";

  bool handleInput() {
    std::getline(std::cin, this->infix_expression);
    if(std::cin.fail()) {
      if (std::cin.eof()) { std::cout << "Reached end of input (EOF)." << std::endl; }
      else { std::cout << "Enter valid input!" << std::endl; }
      return false;
      clearAndResetInputState();
    } else {
      clearAndResetInputState();
      return true;
    }
  }

  void convertToPostfix() {
    for(char c : this->infix_expression) {
      //std::cout << this->operator_stack->size() << " " << this->postfix_expression << std::endl;
      if (c == ' ') { continue; }
      if (this->supported_operators.find(c) == std::string::npos) {
        this->postfix_expression.push_back(c); // if the character read is an operand, it will be pushed to the expression buffer
      } else { 
        // Checking which operator it was and its precedence then its associativity 
        //   to perform operations on the operators' stack.
        if (c == ')') { 
            this->popStackUntilOpeningBracket();
            continue;
        }
        while (this->checkTopStatus(c) == false) {
            this->postfix_expression.push_back(this->operator_stack->top());
            this->operator_stack->pop();
        }
        this->operator_stack->push(c);
      }
    }
    while(not this->operator_stack->empty()) {
        this->postfix_expression.push_back(this->operator_stack->top());
        this->operator_stack->pop();
    }
    this->printPostfixExpression();
  }

  bool checkTopStatus(char c) {
    if (this->operator_stack->empty()) { return true; } // next incoming operator can be pushed without further check
    else if (c == '(') { return true;}
    else if (c == '^') {
      if (this->operator_stack->top() == '^') { return true; } // because associativity for this is right to left
      else { return true; }
    } else if (c == '/' or c == '*') {
      if (((std::string)"^/*").find(this->operator_stack->top()) != std::string::npos) { return false; } // precedence equal or lower
      else if (((std::string)"(+-").find(this->operator_stack->top()) != std::string::npos) { return true; } // precedence higher
    } else if (c == '+' or c == '-') {
      if (((std::string)"^/*+-").find(this->operator_stack->top()) != std::string::npos) { return false; }
      else if (((std::string)"(").find(this->operator_stack->top()) != std::string::npos) { return true; }
    }
    return false;
  }

  void popStackUntilOpeningBracket() {
    if (not this->operator_stack->empty()) {
      while(this->operator_stack->top() != '(') {
        // std::cout << this->operator_stack->size() << " | ";
        // std::cout << this->operator_stack->top();
        char top = this->operator_stack->top();
        this->postfix_expression.push_back(top);
        this->operator_stack->pop();
        // if (this->operator_stack->empty()) { return; }
      }
      this->operator_stack->pop(); // because '(' is at the top.
    }
  }

  const void printPostfixExpression() const {
    std::cout << "\nPostfix Expression:\n  ";
    std::cout << this->postfix_expression << "\n----------------\n" << std::endl;
  }

public:
  InfixToPostfix() {
    if (this->operator_stack == nullptr) { this->operator_stack = new std::stack<char>; }
    else {
      delete this->operator_stack;
      this->operator_stack = new std::stack<char>;
    }
    this->infix_expression = "";
    this->postfix_expression = "";
  }

  InfixToPostfix(std::string& infixexpr) {
    std::cout << "** Infix to Postfix **" << std::endl;

    if (this->operator_stack == nullptr) { this->operator_stack = new std::stack<char>; }
    else {
      delete this->operator_stack;
      this->operator_stack = new std::stack<char>;
    }
    this->infix_expression = infixexpr;
    this->postfix_expression = "";
    
    this->convertToPostfix();
  }

  void enterInfix(std::string* expr = nullptr) {
    if (expr == nullptr) {
      std::cout << "Enter expression: " << std::flush;
      if (this->handleInput()) {
        std::cout << "You Entered Infix Expression:\n" << this->infix_expression << std::endl;
        this->convertToPostfix();
      }
    } else {
      this->infix_expression = *expr;
      this->postfix_expression = "";
      std::cout << "\nTesting:\n  " << this->infix_expression << std::flush;
      if (this->operator_stack == nullptr) { this->operator_stack = new std::stack<char>; }
      else {
        delete this->operator_stack;
        this->operator_stack = new std::stack<char>;
      }
      this->convertToPostfix();
    }
  }
};