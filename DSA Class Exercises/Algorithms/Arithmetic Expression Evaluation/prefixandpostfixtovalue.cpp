#include "../Arithmetic Expression Conversion/input_utils.h"
#include <stack>
#include <string>
#include <cmath>

class EvaluateExpression {
private:
	std::string postfixexpression;
	size_t expression_size;

	std::stack<double> operands_stack;
	const std::string expected_operators = "^/*+-";
	double left_operand, right_operand, result;

	int evaluatePostfix() {
		size_t counter{};
		std::string temp_term("");

		while(counter < this->expression_size) {
			char* current_char = &(this->postfixexpression.at(counter));

			if (*current_char == ' ') { 
				if (not temp_term.empty()) { 
					this->operands_stack.push(std::stod(temp_term));
					temp_term = "";
				}
				continue; 
			} else if (this->expected_operators.find(*current_char) == std::string::npos) {
				// evaluates to true if current_char is not an operator.
				if (*(current_char+1) == ' ') {
					operands_stack.push(static_cast<double>(*current_char));
				} else if (this->expected_operators.find(*(current_char+1)) == std::string::npos) {
					temp_term.push_back(*current_char);
				}
			} else {
				// probably an operator, in that case
				if (this->operands_stack.size() < 2) {
					std::cout << "Something is wrong with the expression: " << this->postfixexpression << std::endl;
					return;
				} else {
					this->right_operand = this->operands_stack.top();
					this->operands_stack.pop();
					this->left_operand = this->operands_stack.top();
					this->operands_stack.pop();

					double result{};

					switch (*current_char) {
						case '^':
							result = std::pow(this->left_operand, this->right_operand);
							break;
						case '/':
							result = this->left_operand / this->right_operand;
							break;
						case '*':
							result = this->left_operand * this->right_operand;
							break;
						case '+':
							result = this->left_operand + this->right_operand;
							break;
						case '-':
							result = this->left_operand - this->right_operand;
							break;
						default:
							std::cout << "Unsupported operation: " << *current_char;
							return;
					}
					this->operands_stack.push(result);
				}
			}
			counter++;
		}

		return -1;
	}

	int evaluatePrefix() {
		
		return 0;
	}

public:
	EvaluateExpression() {
		this->postfixexpression = "";
		this->expression_size = 0;

		this->left_operand = 0;
		this->right_operand = 0;
		this->result = 0;
	}

	void loadPostfixTestStrings(std::string& expression) {
		this->postfixexpression = expression;
		this->expression_size = this->postfixexpression.size();
		this->left_operand = this->right_operand = this->result = 0;

		if (this->evaluatePostfix() == -1) {
			return;
		}
	}

	void loadPrefixTestStrings(std::string& expression) {
		
	}

};