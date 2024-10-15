#include <iostream>
#include <vector>

const std::vector<int> list = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int searchterm = 0;

void binarysearch(int leftindex, int rightindex) {
    if (leftindex < rightindex) {
        int mid = (leftindex + rightindex) / 2;
        if (searchterm == list[mid]) {
            std::cout << "Found search term: " << searchterm << " at index: " << mid << std::endl;
            return;
        } else if (searchterm < list[mid]) {
            binarysearch(leftindex, mid);
        } else {
            binarysearch(mid+1, rightindex);
        }
    } else {
        std::cout << "Not found search term: " << searchterm << std::endl;
    }
}

int main() {
    for (int i = 0; i < list.size()+2; i++) {
        searchterm = i;
        binarysearch(0, list.size());
    }

    return 0;
}