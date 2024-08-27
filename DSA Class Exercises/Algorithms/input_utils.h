#pragma once
#include <iostream>
#include <limits>
#include <conio.h>

static void clearAndResetInputState() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return;
}