#pragma once

template <typename T>
class GraphNode {
public:
  GraphNode(T k, int cost) {
    this->key = k;
  }

public:
  T key;
  bool visited = false;
  std::vector<std::pair<char, int>> adjacentnodeslinks;
};

