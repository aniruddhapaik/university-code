/*
- you have bag capacity w
- you have items {itemid, weight, value, consideration}

- arrange the items according to weight

- in a for loop until bag cant hold full weight items:
  - fill the bag with items from the queue with full weight;
  - mark the item considered = 1;

- if (current bag weight < max bag cap) 
  - get the difference
  - get the loop number where the loop stopped
  - if (loop number < maxitems)
    - get the difference of max bag cap - current bag weight = diff
    - mark this loop numberth item considered = diff;

- display list of items and consideration ratio
*/

#include <iostream>
#include <vector>

class KnapSack {
  float maxbagcap = 0;
  std::vector<std::vector<float>> itemlist;

public:
  KnapSack(std::vector<std::vector<float>> items, float maxcap) {
    float id = 0;
    this->maxbagcap = maxcap;
    while(items.size()) {
      size_t selected = 0;
      for (size_t i = 1; i < items.size(); i++) {
        float sw = items[selected][1] / items[selected][0]; // v/w
        float nw = items[i][1] / items[i][0];
        if (nw > sw) {
          selected = i;
        }
      }
      this->itemlist.emplace_back(std::vector<float>{id, items[selected][0], items[selected][1], static_cast<float>(0)});
      items.erase(items.begin()+selected);
      id++;
    }

    this->fillBag();
    this->printList(this->itemlist);
  }

private:
  void fillBag() {
    size_t i = 0;
    while (i < this->itemlist.size()) {
      auto& item = this->itemlist[i];
      if (this->maxbagcap > item[1]) {
        this->maxbagcap -= item[1];
        this->itemlist[i][3] = 1;
      } else {
        break;
      }
      i++;
    }

    if (this->maxbagcap > 0) {
      this->itemlist[i][3] = this->maxbagcap / this->itemlist[i][1];
    }
  }

  const void printList(std::vector<std::vector<float>>& list) {
    float profitcounter = 0;
    for (auto& item: list) {
      std::cout << "id: " << item[0] << " w: " << item[1] << " v: " << item[2] << " take: " << item[3] << std::endl;
      if (item[3] > 0) {
        profitcounter += item[3] * item[2];
      }
    }
    std::cout << "Total profit: " << profitcounter << std::endl;
  }
};

int main() {
  std::vector<std::vector<float>> items = { 
    {2, 10}, {3, 5}, {5, 15}, {7, 7}, {1, 6}, {4, 18}, {1, 3}
  };

  float maxcapacity = 15;
  KnapSack* sack = new KnapSack(items, maxcapacity);
  return 0;
}