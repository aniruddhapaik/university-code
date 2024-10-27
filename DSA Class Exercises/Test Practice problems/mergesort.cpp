#include <iostream>
#include <vector>

std::vector<int> list = {10, 5, 8, 2, 7, 4, 3, 9, 1, 6};

void merge(int left, int mid, int right) {
  int i = left;
  int j = mid + 1;

  std::vector<int> temp;

  while (i <= mid and j <= right) {
    if (list[i] > list[j]) {
      temp.emplace_back(list[j]);
      j++;
    } else {
      temp.emplace_back(list[i]);
      i++;
    }
  }

  while (i <= mid) {
    temp.emplace_back(list[i]);
    i++;
  }

  while (j <= right) {
    temp.emplace_back(list[j]);
    j++;
  }

  int t = 0;
  for (int k = left; k <= right; k++) {
    list[k] = temp[t];
    t++;
  }
}

void mergeSort(int left, int right) {
  if (left < right) {
    int mid = (left + right) / 2;
    mergeSort(left, mid);
    mergeSort(mid + 1, right);
    merge(left, mid, right);
  }
}

int main() {
  std::cout << "unsorted: ";
  for (auto& i : list) {
    std::cout << i << ' ';
  }

  mergeSort(0, list.size() - 1);

  std::cout << "\nsorted:   ";
  for (auto& j : list) {
    std::cout << j << ' ';
  }

  std::cout << std::endl;

  return 0;
}