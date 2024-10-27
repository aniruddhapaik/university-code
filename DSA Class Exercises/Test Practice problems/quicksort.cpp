#include <iostream>
#include <vector>

std::vector<int> list = {10, 5, 8, 2, 7, 4, 3, 9, 1, 6};

int partition(int left, int right) {
  int pivot = list[left];
  int i = left;
  int j = right;

  while (i < j) {
    do {
      i++;
    } while (list[i] <= pivot);

    do {
      j--;
    } while (list[j] > pivot);

    if (i < j) {
      int temp = list[i];
      list[i] = list[j];
      list[j] = temp;
    }
  }
  int temp = list[j];
  list[j] = pivot;
  list[left] = temp;

  return j;
}

void quickSort(int left, int right) {
  if (left < right) {
    int j = partition(left, right);
    quickSort(left, j);
    quickSort(j + 1, right);
  }
}

int main() {
  std::cout << "unorted: ";
  for (auto& i : list) {
    std::cout << i << ' ';
  }

  quickSort(0, list.size());

  std::cout << "\nsorted:  ";
  for (auto& j : list) {
    std::cout << j << ' ';
  }
  std::cout << std::endl;

  return 0;
}