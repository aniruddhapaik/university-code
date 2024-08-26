#include "input_utils.h"
#include "infixtopostfix.cpp"
#include "infixtoprefix.cpp"
#include <vector>

enum Menu {inpost=0, inpre, exitprogram};

static bool handleInput(int& input) {
    std::cin >> input;
    if (std::cin.fail()) {
        if (std::cin.eof()) { std::cout << "Reached end of input (EOF)." << std::endl; }
        else { std::cout << "Error: Invalid input, enter valid integer." << std::endl; }
        clearAndResetInputState();
        return false;
    } else {
        clearAndResetInputState();
        return true;
    }
    return false;
}

int main() {
  std::vector<std::string> teststrings = {
    "a+b*c", \
    "(a+b)*(c+d)", \
    "(a+b)*c+(d+e)*(f+g)", \
    "a+(b*c*(d/e^f)*g)*h", \
    "(a + (b - c))* ((d - e)/(f + g - h))", \
    "a^b^c+d*e^f^g*h"
  };

  int input;
  InfixToPostfix* IPost;
  InfixToPrefix* IPre;

  while(1) {
    system("cls");
    std::cout << "Expression Conversion\n";
    //std::cout << test5;
    std::cout << "\nSupported Operators:\n";
    std::cout << "( ) ^ / * + -\n";
    std::cout << "----------------------\n";
    std::cout << inpost << ". Infix to Postfix\n";
    std::cout << inpre << ". Infix to Prefix\n";
    std::cout << "----------------------\n";
    std::cout << exitprogram << ". Exit\n";
    std::cout << "\nEnter Choice: " << std::flush;

    if (handleInput(input)) {
      switch (input) {
        case inpost:
          IPost = new InfixToPostfix;
          for (std::string str : teststrings) {
            IPost->enterInfix(&str);
          }
          break;
        case inpre:
          IPre = new InfixToPrefix;
          for (std::string str : teststrings) {
            IPre->enterInfix(&str);
          }
          //IPre->enterInfix(&(teststrings[1]));
          break;
        case exitprogram:
          return 0;
        default:
          std::cout << "Choose valid menu option!" << std::endl;
        }
    }
    _getch();
  }
    return 0;
}