#pragma once

#include <vector>
#include <utility>
#include <iosfwd>

class KnapSack {
public:
  void getItemsInfo(std::vector<std::pair<float, float>>&, unsigned); // <weight, profit>
  const void printItemList() const;

private:
  void buildList(std::vector<std::pair<float, float>>&);
  void mergeSort(size_t, size_t);
  void merge(size_t, size_t, size_t);
  void fillBag();


private:
  std::vector<std::pair<unsigned, std::pair<float, float>>> list; // <weight, profit>
  std::vector<std::pair<unsigned, std::pair<float, float>>> sortedlist;

  unsigned maxbagcapacity = 0;
};

std::ostream& operator<<(std::ostream&, KnapSack&);