#pragma once
#include <unordered_map>
#include <vector>

class Vertex {
public:
  unsigned int label;
  bool visited;
  std::unordered_map<unsigned int, unsigned int> linksandcost;
  unsigned int cost_from_source;
  std::vector<unsigned int> path_from_source;

  Vertex() = delete;
  Vertex(unsigned int);
  Vertex(const Vertex&) = delete;
};