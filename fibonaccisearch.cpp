#include <iostream>
#include <vector>
#include <limits>
#include <conio.h>

#define GOLDEN_RATIO 1.618

class FibonacciSearch {
private:
    std::vector<int> fibseries;
    std::vector<int>* arr;

    size_t arr_size;
    int offset;
    int index;
    int fm2;
    int right;
    int key;

void resetAndCalculateTrackers() {
    this->offset = -1;
    int range = (this->arr_size / GOLDEN_RATIO) + 1;
    this->generateFibonacciSeries(range);
    // this->printFib();
    this->right = this->arr_size - 1;
    this->fm2 = this->seekfm2();
}

void generateFibonacciSeries(int range) {
    this->fibseries.push_back(0);
    this->fibseries.push_back(1);

    std::cout << "range: " << range << std::endl;

    for (int i = 2; i <= range; i++) {
        int prev2 = this->fibseries.at(i-2);
        int prev1 = this->fibseries.at(i-1);

        this->fibseries.push_back(prev2 + prev1);
    }
}

int seekfm2() {
    size_t fib_size = this->fibseries.size();
    for (int i = 0; i < fib_size; i++) {
        if (this->fibseries.at(i) >= this->arr_size) {
            return this->fibseries.at(i-2);
        }
    }
    return 0;
}

public:
    FibonacciSearch(std::vector<int>& arr) {
        this->arr = &arr;

        this->arr_size = this->arr->size();
        this->resetAndCalculateTrackers();
    }

    const void setKey(int key) {
        this->key = key;
    }

    const void printFib() const {
        for (int i: this->fibseries) {
            std::cout << i << ", ";
        }
        std::cout << std::endl;
    }
};


int main() {
    std::vector<int> arr {2,5,9,10,13,16,21,25,27,34};

    FibonacciSearch fib(arr);

    int key{};
    while(1) {
        // system("cls");
        std::cout << "Fibonacci Search\nPress CTRL+C to quit" << std::endl;
        std::cout << "Enter a value to search in array: ";
        if (std::cin >> key) {
            fib.setKey(key);
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter a valid number!" << std::endl;
        }
        _getch();
    }

    return 0;
}