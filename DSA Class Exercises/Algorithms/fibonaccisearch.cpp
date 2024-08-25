#include <iostream>
#include <vector>
#include <limits>
#include <conio.h>

// #define GOLDEN_RATIO 1.618

class FibonacciSearch {
private:
    std::vector<int> fibseries;
    std::vector<int>* arr;

    size_t arr_size; // n
    int offset;
    size_t k; // using as index for the Fibonacci series
    int n1; // n - 1
    int key; // search term

    void resetAndCalculateTrackers() {
        this->offset = -1;
        this->k = 0;

        // Generating fibonacci numbers only as many as required.
        if (this->fibseries.empty()) {
            this->generateFibonacciSeries(); 
        }
        this->k = this->fibseries.size()-1;
        /*
            Knowing that the last element in the this->fibseries array will be the
            smallest value that is greater or equal to the size of the search array this->arr,
            and in consequence that will be the fm value we start off with.
            So, to keep track of the index of fm in the fibseries array, 
            this->k is at last updated to match the index of the last element in this->fibseries,
            which is the first fm value we start the algorithm with.
        */
        this->n1 = this->arr_size - 1; // n-1
    }

    void generateFibonacciSeries() {
        int fm2 = 0;
        int fm1 = 1;
        int fm = fm2 + fm1;
        // the numbers in the this->fibseries will act as indeces to access elements in this->arr
        this->fibseries.push_back(fm2);
        this->fibseries.push_back(fm1);
        this->fibseries.push_back(fm);
        
        while(fm < this->arr_size) {
            fm2 = fm1;
            fm1 = fm;
            fm = fm2 + fm1;

            this->fibseries.push_back(fm);
        }
        return;
    }

    int search() {
        if (this->k < 2) { return -1; }
        int i = std::min((this->offset+this->fibseries.at(this->k-2)), this->n1);

        if (this->key == this->arr->at(i)) { return i; } 
        else if (this->key > this->arr->at(i)) { // if the element that we are looking for is > what is at index i in the array
            this->offset = i;
            this->k--;
            return this->search();
        } else if (this->key < this->arr->at(i)) { // if the element we are looking for is < what is at index i in the array
            this->k = this->k - 2;
            return this->search();
        } 
        if (this->key == this->arr->at(this->offset+1)) { return (this->offset+1); }
        return -1;
    }

    /*const void printTelemetry(int i) const {
        std::cout << "k:   " << this->k << " | F(k): "<< this->fibseries.at(this->k) << std::endl;
        std::cout << "k-2: " << this->k-2 << " | F(k-2): " << this->fibseries.at(this->k-2) << " | offset: " << this->offset << std::endl;
        std::cout << "i: " << i << " | A[i]: " << this->arr->at(i) << std::endl;
        this->printFib();

        return;
    }

    const void printFib() const {
        std::cout << "Fib: ";
        for (int i: this->fibseries) {
            std::cout << i << ", ";
        }
        std::cout << '\n' << std::endl;
    }*/

public:
    FibonacciSearch(std::vector<int>& arr) {
        this->arr = &arr; // setting the search array
        this->arr_size = this->arr->size(); // n
    }

    const void setKey(int key) {
        this->key = key;
        this->resetAndCalculateTrackers();
        if (this->k) { 
            int i = this->search();
            if (i != -1) {
                std::cout << "Found key " << key << " at index: " << i << std::endl;
            } else {
                std::cout << "Element not found" << std::endl;
            }
        }
        return;
    }
};

int main() {
    std::vector<int> arr {2,5,9,10,13,16,21,25,27,34};
    FibonacciSearch fib(arr);

    int key{};
    while(1) {
        system("cls");
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