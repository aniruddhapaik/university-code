#include <vector>
#include <string>

#include "../input_utils.h"
#include "prefixandpostfixtovalue.cpp"

std::vector<std::string> posfixteststrings = {
	"2 3 +" , \
	"4 2 *" , \
	"10 2 3 + *", \
	"7 2 1 + -", \
	"9 4 2 - /", \
	"3 4 * 2 5 * +", \
	"15 3 2 + 4 * -", \
	"18 2 3 + 4 - /", \
	"20 5 3 + 2 ^ 4 * -", \
	"30 4 2 + 5 * 3 - /", \
	"25 3 2 - 4 ^ 2 + *", \
	"18 2 3 + 5 - 2 ^ /", \
	"40 5 3 + 2 * 4 - ^", \
	"50 3 2 + 5 * 2 - 4 ^ 3 /", \
	"30 4 2 - 5 + 3 ^ 2 * /", \
	"45 3 2 - 5 ^ 2 + 4 * -",
	"2 3 + 4 * 5 - 6 / 7 ^", \
	"5 4 - 7 + 8 * 9 - 10 /", \
	"8 2 / 3 ^ 4 + 5 - 6 *"
	};

std::vector<std::string> prefixteststrings = {
	"+ 2 3", \
	"- 8 1", \
	"* + 10 2 3"
	"- + 7 2 1", \
	"/ - 9 4 2", \
	"+ * 6 3 2", \
	"/ + 8 2 4", \
	"- * + 150 3.5 2 4", \
	"/ + - 20 5 3 2", \
	"- + * 12 3 4 2", \
	"/ - + 18 2 3 5", \
	"^ - * 25.5 5 2.8 3", \
	"/ * + - 50 3 2 5 2", \
	"- + ^ * 30 4 2 5 3", \
	"* - + ^ 45 3 2 5 2", \
	"/ + - * 60 5 3 2 4", \
	"^ / + - * 75 4 2 3 5", \
	"- * 3 4 + 2 5", \
	"^ * + 3 4 - 5 2", \
	"+ * 3 (4 - 2) 5", \
	"^ * + 3 (4 - 5) 2", \
	"- * + 3 4 2 ^ 5 2", \
	"^ * + 3 (4 - 5) 2 ^ 3 2"
};

enum Menu {postfixeval=0, prefixeval, inputstring, poststring, \
						prestring, goback, exitprogram};

bool handleInput(short int& choice) {
	std::cin >> choice;
	if (std::cin.fail()) {
		if (std::cin.eof()) { std::cout << "Reached end of input (EOF)." << std::endl; }
		else { std::cout << "Enter valid integer!" << std::endl; }
		clearAndResetInputState();
		return false;
	} else { 
		clearAndResetInputState();
		return true; 
	}
}

bool enterExpressionString(std::string& str) {
	std::getline(std::cin, str);
	if (std::cin.fail()) {
		if (std::cin.eof()) { std::cout << "Reached end of input (EOF)." << std::endl; }
		else { std::cout << "Enter valid integer!" << std::endl; }
		clearAndResetInputState();
		return false;
	} else { return true; }
}

Menu inputString(std::string& expression) {
	short int choice{};
	while(1) {
		system("cls");
		std::cout << "Choose which type of string you want to enter --\n";
		std::cout << "-! make sure to separate numbers and operators by spaces\n";
		std::cout << poststring << " . Postfix string\n";
		std::cout << prestring << " . Prefix string\n";
		std::cout << std::string(10, '-') << '\n';
		std::cout << goback << " . Go back\n\n";
		std::cout << "Choice: " << std::flush;
		handleInput(choice);

		switch (choice)	{
			case poststring:
				std::cout << "Enter Postfix Expression: " << std::flush;
				enterExpressionString(expression);
				return postfixeval;
			case prestring:
				std::cout << "Enter Prefix Expression: " << std::flush;
				enterExpressionString(expression);
				return prefixeval;
				break;
			case goback:
				return goback;
				break;
			default:
				std::cout << "Choose a valid option!" << std::endl;
		}
		 std::cout << "\n\nPress ENTER to continue..." << std::flush;
		 _getch();
	}
}

void printMenu() {
	EvaluateExpression Evaluator;
	std::string expression;
	short int choice{};
	while(1) {
		system("cls");
		std::cout << "** Expression Evaluation **\n";
		std::cout << "Menu ----------------------\n";
		std::cout << postfixeval << " . Postfix Evaluation Tests\n";
		std::cout << prefixeval << " . Prefix Evaluation Tests\n";
		std::cout << inputstring << " . Enter Expression\n";
		std::cout << "---------------------------\n";
		std::cout << exitprogram << " . Exit Program\n";
		std::cout << "Enter choice: " << std::flush;
		handleInput(choice);

		switch(choice) {
			case postfixeval:
				for (std::string str : posfixteststrings) {
					Evaluator.loadPostfixTestStrings(str);
				}
				break;
			case prefixeval:
				for (std::string str : prefixteststrings) {
					Evaluator.loadPrefixTestStrings(str);
				}
				break;
			case inputstring:
				choice = inputString(expression);
				if (choice == postfixeval) {
					Evaluator.loadPostfixTestStrings(expression);
				} else if (choice == prefixeval) {
					Evaluator.loadPrefixTestStrings(expression);
				} else if (choice == goback) {
					continue;
				}
				break;
			case exitprogram:
				return;
				break;
			default:
				std::cout << "Choose valid option!" << std::endl;
		}
		std::cout << "\n\nPress ENTER to continue..." << std::flush;
		_getch();
	}
}

int main() {
	printMenu();

	return 0;
}