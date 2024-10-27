#pragma once

#include <iosfwd>
#include <unordered_map>
#include <vector>

#include "directionenum.h"
#include "vertex.h"

// Another way to implement graphs adjacency matrix with cost as cells
// Not using adjacency matrix here.
// Might use adjacency matrix for Floyd Warshall's Algorithm.

// Using it here as a directed graph
class SimpleGraph {
 public:
  SimpleGraph();
  const void getEdgeList(Direction, std::vector<edgecost>&);
  const void setSource(unsigned int);
  const void printVerticesInfo() const;

 private:
  void buildGraph(std::vector<edgecost>&);
  friend void Explore(SimpleGraph&);
  friend void Relax(SimpleGraph&, Vertex*);

 private:
  std::unordered_map<unsigned int, Vertex*> allnodes;
  Direction direction;
  unsigned int source;
  unsigned int current_visiting_node;
};

std::ostream& operator<<(std::ostream&, const SimpleGraph&);