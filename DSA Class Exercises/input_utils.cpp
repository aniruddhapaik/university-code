#include <iostream>
#include <limits>

// #define PRINTS(x) std::cout << x;
// #define PRINTM(x, ...) std::cout << x << __VA_ARGS__;
// #define PRINTSNL(x) std::cout << x << std::endl;
// #define PRINTMNL(x, ...) std::cout << x << __VA_ARGS__ << std::endl;
// #define PRINTEMPTY std::cout << "The list is empty!" << std::endl;
// #define PRINTRETURNDEFAULT std::cout << "Returning default value..." << std::endl;
// #define INPUTMESSAGE(x) std::cout << x << std::flush;

void clearAndResetInputState() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return;
}