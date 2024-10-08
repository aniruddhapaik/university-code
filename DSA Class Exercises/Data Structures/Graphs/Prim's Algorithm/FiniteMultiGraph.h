#pragma once

#include <vector>
#include <unordered_map>
#include <iosfwd>

#include "Vertex.h"
#include "utils.h"

class FiniteMultiGraph {
public:
  void builGraph(std::vector<edgewithcost>&);
  const void setSource(unsigned);
  const void printPath() const;

private:
  friend void primsalgorithm(FiniteMultiGraph& graph);

private:
  std::unordered_map<unsigned, Vertex*> allnodes;
  std::vector<vertexandcost> path;
  unsigned source = 0;
};

std::ostream& operator<<(std::ostream&, FiniteMultiGraph&);