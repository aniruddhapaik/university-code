#include <vector>
#include <string>

#include "../Arithmetic Expression Conversion/input_utils.h"
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
	"- * + 15 3 2 4", \
	"/ + - 20 5 3 2", \
	"- + * 12 3 4 2", \
	"/ - + 18 2 3 5", \
	"^ - * 25 5 2 3", \
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

enum Menu {postfixeval=0, prefixeval, inputstring, loadteststrings, exitprogram};

bool handleInput(short int& choice) {
	std::cin >> choice;
	if (std::cin.fail()) {
		if (std::cin.eof()) { std::cout << "Reached end of input (EOF)." << std::endl; }
		else { std::cout << "Enter valid integer!" << std::endl; }
		clearAndResetInputState();
		return false;
	} else { return true; }
}

void printMenu() {
	EvaluateExpression post;
	EvaluateExpression pre;
	short int choice{};
	while(1) {
		system("cls");
		std::cout << "** Expression Evaluation **\n";
		std::cout << "Menu ----------------------\n";
		std::cout << postfixeval << " . Postfix Evaluation\n";
		std::cout << prefixeval << " . Prefix Evaluation\n";
		std::cout << "---------------------------\n";
		std::cout << exitprogram << " . Exit Program\n";
		std::cout << "Enter choice: " << std::flush;
		handleInput(choice);

		switch(choice) {
			case postfixeval:
				for (std::string str : posfixteststrings) {
					post.loadPostfixTestStrings(str);
				}
				break;
			case prefixeval:
				for (std::string str : prefixteststrings) {
					pre.loadPrefixTestStrings(str);
				}
				break;
			case exitprogram:
				return;
				break;
			default:
				std::cout << "Choose valid option!" << std::endl;
		}
	}
}

int main() {
	printMenu();

	return 0;
}