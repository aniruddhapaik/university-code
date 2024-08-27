#include "../input_utils.h"
#include <stack>
#include <string>
#include <cmath>

class EvaluateExpression {
private:
	std::string expression;
	size_t expression_size;

	std::stack<double> operands_stack;
	const std::string expected_operators = "^/*+-";
	double left_operand, right_operand, result;
	bool result_is_good;

	double evaluatePostfix() {
		size_t counter{};
		std::string temp_term("");

		while(counter < this->expression_size) {
			char* current_char = &(this->expression.at(counter));

			if (*current_char == ' ') { 
				if (not temp_term.empty()) { 
					this->operands_stack.push(std::stod(temp_term));
					temp_term = "";
				}
			} else if (static_cast<int>(*current_char) > 47 and static_cast<int>(*current_char) < 58 \
								 or *current_char == '.') {
				// evaluates to true if current_char is not an operator.
				temp_term.push_back(*current_char);
			} else if (*current_char == '(' or *current_char == ')') {
				std::cout << "Unsupported operation: " << *current_char;
				return -1;
			} else {
				// probably an operator, in that case
				if (not temp_term.empty()) {
					this->operands_stack.push(std::stod(temp_term));
					temp_term = "";
				}

				if (this->operands_stack.size() < 2) {
					std::cout << "Something is wrong with the expression!\n-> operand to operator ratio mismatch\n-> ratio should be operands (n):(n-1) operators" << std::endl;
					return -1;
				} else {
					this->right_operand = this->operands_stack.top();
					this->operands_stack.pop();
					this->left_operand = this->operands_stack.top();
					this->operands_stack.pop();

					switch (*current_char) {
						case '^':
							this->result = std::pow(this->left_operand, this->right_operand);
							break;
						case '/':
							if (this->right_operand == 0) {
								std::cout << "Warning: Division by zero!" << std::endl;
								return -1;
							}
							this->result = this->left_operand / this->right_operand;
							break;
						case '*':
							this->result = this->left_operand * this->right_operand;
							break;
						case '+':
							this->result = this->left_operand + this->right_operand;
							break;
						case '-':
							this->result = this->left_operand - this->right_operand;
							break;
						default:
							std::cout << "Unsupported operation: " << *current_char;
							return -1;
					}
					this->operands_stack.push(this->result);
				}
			}
			counter++;
		}

		if (not temp_term.empty()) { this->operands_stack.push(std::stod(temp_term)); }

		if (this->operands_stack.size() == 1) { // making sure the postfix expression was correctly input
			this->result_is_good = true;
			std::cout << "Result: " << this->operands_stack.top() << '\n';
			return this->operands_stack.top();
		} else {
			std::cout << "Bad test string!\n-> operand to operator ratio mismatch\n-> ratio should be operands (n):(n-1) operators" << std::endl;
			return -1; 
		}
	}

	double evaluatePrefix() {
		size_t counter{this->expression_size-1};
		std::string temp_term("");

		while(counter >= 0 and counter < this->expression_size) {
			char* current_char = &(this->expression.at(counter));

			if (*current_char == ' ') { 
				if (not temp_term.empty()) { 
					this->operands_stack.push(std::stod(temp_term));
					temp_term = "";
				}
			} else if (static_cast<int>(*current_char) > 47 and static_cast<int>(*current_char) < 58 \
								 or *current_char == '.') {
				/*
				in the else if statement above I am making sure that every character read,
				that is not an operand, is between ASCII value ]47, 58[, 
				which are ASCII values for characters 0 to 9
				or the current character is a '.' which means there is a rational number in the expression
				that we need to read correctly.
				*/
				// evaluates to true if current_char is not an operator.
				temp_term.push_back(*current_char);
			} else if (*current_char == '(' or *current_char == ')') {
				std::cout << "Unsupported operation: " << *current_char;
				return -1;
			} else {
				// probably an operator, in that case
				if (not temp_term.empty()) {
					this->operands_stack.push(std::stod(temp_term));
					temp_term = "";
				}

				if (this->operands_stack.size() < 2) {
					std::cout << "Something is wrong with the expression!\n-> operand to operator ratio mismatch\n-> ratio should be operands (n):(n-1) operators" << std::endl;
					return -1;
				} else {
					this->left_operand = this->operands_stack.top();
					this->operands_stack.pop();
					this->right_operand = this->operands_stack.top();
					this->operands_stack.pop();

					switch (*current_char) {
						case '^':
							this->result = std::pow(this->left_operand, this->right_operand);
							break;
						case '/':
							if (this->right_operand == 0) {
								std::cout << "Warning: Division by zero!" << std::endl;
								return -1;
							}
							this->result = this->left_operand / this->right_operand;
							break;
						case '*':
							this->result = this->left_operand * this->right_operand;
							break;
						case '+':
							this->result = this->left_operand + this->right_operand;
							break;
						case '-':
							this->result = this->left_operand - this->right_operand;
							break;
						default:
							std::cout << "Unsupported operation: " << *current_char;
							return -1;
					}
					this->operands_stack.push(this->result);
				}
			}
			counter--;
			//std::cout << "after counter decrement" << std::endl;
		}

		if (not temp_term.empty()) { this->operands_stack.push(std::stod(temp_term)); }

		if (this->operands_stack.size() == 1) { // making sure the prefix expression was correctly input
			this->result_is_good = true;
			std::cout << "Result: " << this->operands_stack.top() << '\n';
			return this->operands_stack.top();
		} else {
			std::cout << "Bad test string!\n-> operand to operator ratio mismatch\n-> ratio should be operands (n):(n-1) operators" << std::endl;
			return -1; 
		}
	}

public:
	EvaluateExpression() {
		this->expression = "";
		this->expression_size = 0;

		this->left_operand = 0;
		this->right_operand = 0;
		this->result = 0;
		this->result_is_good = false;
	}

	void loadPostfixTestStrings(std::string& expression) {
		this->expression = expression;
		this->expression_size = this->expression.size();
		this->left_operand = this->right_operand = this->result = 0;
		this->result_is_good = false;

		while (not this->operands_stack.empty()) { this->operands_stack.pop(); }

		std::cout << '\n' << std::string(10, '-') << '\n';
		std::cout << "Test String: " << this->expression << std::endl;

		this->evaluatePostfix();
	}

	void loadPrefixTestStrings(std::string& expression) {
		this->expression = expression;
		this->expression_size = this->expression.size();
		this->left_operand = this->right_operand = this->result = 0;
		this->result_is_good = false;

		while (not this->operands_stack.empty()) { this->operands_stack.pop(); }

		std::cout << '\n' << std::string(10, '-') << '\n';
		std::cout << "Test String: " << this->expression << std::endl;

		this->evaluatePrefix();
	}

};