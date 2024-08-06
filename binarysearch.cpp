#include <iostream>
#include <conio.h>
#include <vector>
#include <limits>

class BinarySearch {
private:
    std::vector<int>* arr;
    size_t left, right, index;

    void search(int num) {
        if (num == this->arr->at(this->index)) {
            this->valueFound(this->index);
            return;
        } else if ((this->right - this->left) <= 1) {
            if (num == this->arr->at(this->right)) {
                this->valueFound(this->right);
                return;
            } else {
                std::cout << "Value not found in array!" << std::endl;
                return;
            }
        } else if (num < this->arr->at(this->index)) {
            this->right = this->index;
            this->setIndex();
            this->search(num);
        } else if (num > this->arr->at(this->index)) {
            this->left = this->index;
            this->setIndex();
            this->search(num);
        }
    }

    void setIndex() {
        this->index = (this->left + this->right) / 2;
    }

    const void valueFound(size_t at_index) const {
        std::cout << "Value has been found at index: " << at_index << std::endl;
        return;
    }
    
    void resetIndexes() {
        this->left = 0;
        this->right = this->arr->size()-1;
        this->setIndex();
    }

public:
    BinarySearch(std::vector<int>& values) {
        this->arr = &values;
    }
    void getKey(int num) {
        this->resetIndexes();
        this->search(num);
    }
};

int main() {
    std::vector<int> arr {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    BinarySearch bsearch(arr);
    
    int key{};
    while(1) {
        system("cls");
        std::cout << "Press CTRL+C to quit" << std::endl;
        std::cout << "Enter a value to search in array: ";
        if (std::cin >> key) {
            bsearch.getKey(key);
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter a valid number!" << std::endl;
        }
        _getch();
    }

    return 0;
}