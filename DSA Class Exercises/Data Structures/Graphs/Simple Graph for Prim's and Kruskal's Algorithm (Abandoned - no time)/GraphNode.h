#pragma once

#include <unordered_map>
#include <utility>

template <typename T>
class GraphNode {
public:
  GraphNode(T k) {
    this->key = k;
  }

public:
  T key;

  bool visited = false;
  std::unordered_map<T, int> adjacentedgeandcost;
};

