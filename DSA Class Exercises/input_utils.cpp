#include <iostream>
#include <limits>

void clearAndResetInputState() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return;
}