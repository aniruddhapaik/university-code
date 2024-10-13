#pragma once
#include <unordered_map>
#include <vector>
#include <iosfwd>

#include "Vertex.h"
#include "utils.h"

class SimpleGraph {
public:
  SimpleGraph();
  void buildGraph(std::vector<edgelinkcost>&);
  const void setSource(unsigned);
  const void printAdjmatrix() const;

private:
  friend void breadthfirstsearch(SimpleGraph&);
  friend void depthfirstsearch(SimpleGraph&);
  friend void explore(unsigned, SimpleGraph&, std::unordered_map<unsigned, bool>&);

private:
  std::vector<std::vector<int>> adjacencymatrix;
  std::unordered_map<unsigned, bool> vertexvisitedlist; // <vertex, visited true or false>
  std::vector<edgevisit> edgevisitedlist; // sorted according to ascending cost
  unsigned source;

  unsigned minvertexindex;
  unsigned maxvertexindex;
};

std::ostream& operator<<(std::ostream&, SimpleGraph&);