#include "KnapSack.h"

#include <vector>
#include <utility>
#include <iostream>
#include <iosfwd>

void KnapSack::getItemsInfo(std::vector<std::pair<float, float>>& itemsinfo, unsigned maxbagcap) {
  this->list.resize(itemsinfo.size());
  this->sortedlist.resize(itemsinfo.size());

  this->maxbagcapacity = maxbagcap;

  this->buildList(itemsinfo);
  this->sortedlist = this->list;
  
  this->mergeSort(0, this->list.size()-1);

  for(auto& pair: this->sortedlist) {
    std::cout << pair.second.first << '|' << pair.second.second << ' ';
  }

  //this->fillBag();
}

const void KnapSack::printItemList() const {
  size_t listsize = this->list.size();

  /*std::cout << "item: ";
  for (size_t i = 1; i <= listsize; i++) {
    std::cout << i << "  ";
  }
  std::cout << std::endl;

  std::cout << "Weight: ";
  for (size_t i = 0; i < listsize; i++) {
    std::cout << this->list[i].first << "  ";
  }
  std::cout << std::endl;

  std::cout << "Profit: ";
  for (size_t i = 0; i < listsize; i++) {
    std::cout << this->list[i].second << "  ";
  }
  std::cout << '\n' << std::endl;*/
}

void KnapSack::buildList(std::vector<std::pair<float, float>>& itemsinfo) {
  size_t t = 1;
  for (auto& pair: itemsinfo) {
    this->list[t-1] = {t, pair};
    t++;
  }
}

void KnapSack::mergeSort(size_t l, size_t r) {
  if (l < r) {
    size_t mid = (l+r)/2;
    this->mergeSort(l, mid);
    this->mergeSort(mid+1, r);
    this->merge(l, mid, r);
  }
}

void KnapSack::merge(size_t l, size_t mid, size_t r) {
  size_t m = l;
  size_t n = mid+1;

  std::vector<std::pair<unsigned, std::pair<float, float>>> temp;

  while(m <= mid and n <= r) {
    float ratio1 = this->sortedlist[m].second.second / this->sortedlist[m].second.first;
    float ratio2 = this->sortedlist[n].second.second / this->sortedlist[n].second.first;

    if (ratio1 > ratio2) {
      temp.emplace_back(this->sortedlist[n]);
      n++;
    } else {
      temp.emplace_back(this->sortedlist[m]);
      m++;
    }
  }

  while (m <= mid) {
    temp.emplace_back(this->sortedlist[m]);
    m++;
  }

  while (n <= r) {
    temp.emplace_back(this->sortedlist[n]);
    n++;
  }

  size_t t = 0;
  for (size_t k = l; k <= r; k++) {
    this->sortedlist[k] = temp[t];
    t++;
  }
}

void KnapSack::fillBag() {
  std::cout << *this;

  size_t index = this->list.size()-1;
  unsigned maxcap = this->maxbagcapacity;

  while (index >= 0) {
    if ((maxcap - this->list[index].first) >= 0) {
      maxcap -= this->list[index].second.first;
      std::
    }

    index--;
  }
}

std::ostream& operator<<(std::ostream& COUT, KnapSack& sack) {
  sack.printItemList();
  return COUT;
}