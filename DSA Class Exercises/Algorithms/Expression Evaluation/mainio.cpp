#include <stack>

#include "../../input_utils.cpp"
#include "infixtopostfix.cpp"
#include "infixtoprefix.cpp"

enum Menu {inpost=0, inpre, exitprogram};

bool handleInput(int& input) {
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
    std::string test1 = "a+b*c";
    std::string test2 = "(a+b)*(c+d)";
    std::string test3 = "(a+b)*c+(d+e)*(f+g)";
    std::string test4 = "a+(b*c*(d/e^f)*g)*h";
    int input;
    InfixToPostfix* IPost;
    InfixToPrefix* IPre;

    while(1) {
        system("cls");
        std::cout << "Expression Evalutation\n";
        std::cout << test4;
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
                    IPost = new InfixToPostfix(test4);
                    break;
                case inpre:
                    IPre = new InfixToPrefix;
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