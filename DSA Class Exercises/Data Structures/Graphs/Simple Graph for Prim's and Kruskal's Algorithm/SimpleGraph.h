#pragma once

#include <utility>
#include <vector>

#include "../../Different Types of Queues/\
Priority Queue - Min Heap/MinHeapPriorityQueue.h"

using edge = std::pair<char, char>;
using edgeandcost = std::pair<edge, int>;

class SimpleGraph {
 public:
  void buildGraph(std::vector<edgeandcost>& graphdetails) {
    
  }

  void setSource(char src) { this->source = src; }

 private:
 private:
  char source = '\0';

};