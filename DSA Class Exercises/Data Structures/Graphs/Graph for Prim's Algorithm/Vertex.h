#pragma once

#include <unordered_map>

class Vertex {
public:
  unsigned key;
  bool visited;
  std::unordered_map<unsigned, unsigned> linksandcost;

  Vertex();
  Vertex(int);
};