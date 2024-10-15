#pragma once

#include <vector>
#include <iostream>
#include <utility>
#include <string>
#include <sstream>
#include <iomanip>
#include <iosfwd>
#include <ios>

class Item{
public:
  unsigned itemnumber;
  float weight;
  float profit;
  bool toinclude = false;
  std::string fraction = "--";

  Item(unsigned itno, float w, float p) {
    this->itemnumber = itno;
    this->weight = w;
    this->profit = p;
    this->toinclude = false;
  }
};

class KnapSack{
public:
  void getItemList(float maxcap, std::vector<std::pair<float, float>>& itlist) {
    this->maxcapacity = maxcap;
    this->buildList(itlist);
    std::cout << "Before Sorting according to ratio\n";
    this->printList(this->sortedlist);

    this->mergeSort(0, itlist.size()-1);

    //std::cout << "After Sorting according to ratio\n";
    //this->printList(this->sortedlist);

    this->fillBag();
  }

private:
  void buildList(std::vector<std::pair<float, float>>& itlist) {
    unsigned i = 1;
    for (auto& pair: itlist) {
      Item* temp = new Item(i, pair.first, pair.second);
      this->itemlist.emplace_back(temp);
      this->sortedlist.emplace_back(temp);
      i++;
    }
  }

  void mergeSort(size_t left, size_t right) {
    if (left < right) {
      size_t mid = (left + right) / 2;
      mergeSort(left, mid);
      mergeSort(mid+1, right);
      merge(left, mid, right);
    }
  }

  void merge(size_t left, size_t mid, size_t right) {
    size_t i = left;
    size_t j = mid+1;

    std::vector<Item*> templist;

    while (i <= left and j <= right) {
      float ratio1 = this->sortedlist[i]->profit / this->sortedlist[i]->weight;
      float ratio2 = this->sortedlist[j]->profit / this->sortedlist[j]->weight;

      if (ratio1 > ratio2) {
        templist.emplace_back(this->sortedlist[j]);
        j++;
      } else {
        templist.emplace_back(this->sortedlist[i]);
        i++;
      }
    }

    while (i <= mid) {
      templist.emplace_back(this->sortedlist[i]);
      i++;
    }

    while (j <= right) {
      templist.emplace_back(this->sortedlist[j]);
      j++;
    }

    size_t t = 0;
    for (size_t k = left; k <= right; k++) {
      this->sortedlist[k] = templist[t];
      t++;
    }
  }

  const void printList(std::vector<Item*>& list) {
    std::cout << "Format: [Item Number: WEIGHT|PROFIT]" << std::endl;
    for (auto& item: list) {
      std::cout << '[' << item->itemnumber << ": " 
                << item->weight << '|' << item->profit << "]\n";
    }
    std::cout << std::endl;
  }

  void fillBag() {
    float maxcap = this->maxcapacity;
    this->totalprofit = 0;

    while(maxcap > 0) {
      if ((maxcap - this->sortedlist.back()->weight) >= 0) {
        maxcap -= this->sortedlist.back()->weight;
        this->totalprofit += this->sortedlist.back()->profit;

        this->sortedlist.back()->toinclude = true;
        this->sortedlist.back()->fraction = "1";
        this->sortedlist.pop_back();
      } else {
        float takefractionofprofit = maxcap / this->sortedlist.back()->weight;
        this->totalprofit += this->sortedlist.back()->profit * takefractionofprofit;
        
        this->sortedlist.back()->toinclude = true;

        std::ostringstream ossr;
        ossr << std::fixed << std::setprecision(2) << maxcap / this->sortedlist.back()->weight;

        this->sortedlist.back()->fraction = ossr.str();
        maxcap = 0;
      }
    }

    std::cout << "Consider taking these items: ";
    for (auto& item: this->itemlist) {
      if (item->toinclude) {
        std::cout << item->itemnumber << "). " << item->fraction << " | ";
      } else {
        std::cout << item->itemnumber << "). __ | ";
      }
    }
    std::cout << std::endl;
  }

private:
  std::vector<Item*> itemlist;
  std::vector<Item*> sortedlist;
  float maxcapacity = 0;
  float totalprofit = 0;
};
