#pragma once

#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>
#include "vertex.h"
#include "directionenum.h"
#include <iosfwd>

using directededge = std::pair<unsigned int, unsigned int>;
using edgecost = std::pair<directededge, unsigned int>;

// Another way to implement graphs: adjacency matrix with cost as cells

// Using it here as a directed graph
class FiniteMultiGraph {
public:
  FiniteMultiGraph();
  const void getEdgeList(Direction, std::vector<edgecost>&);
  const void setSource(unsigned int);
  const void printVerticesInfo() const;
  void Explore();
  
private:
  void buildGraph(std::vector<edgecost>&);
  void Relax(Vertex*);

private:
  std::unordered_map<unsigned int, Vertex*> allnodes;
  Direction direction;
  unsigned int source;
  unsigned int current_visiting_node;
};

std::ostream& operator<< (std::ostream&, const FiniteMultiGraph&);