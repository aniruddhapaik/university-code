#include <vector>
#include <utility>
#include <iostream>
#include <iosfwd>
#include <limits>

#include "SimpleGraph.h"
#include "utils.h"

SimpleGraph::SimpleGraph(): source(0), minvertexindex(std::numeric_limits<unsigned>::max()), maxvertexindex(0) {}

const void SimpleGraph::setSource(unsigned start) {
  this->source = start;
}

void SimpleGraph::buildGraph(std::vector<edgelinkcost>& edgeinfo) {
  this->maxvertexindex = 0;
  this->minvertexindex = std::numeric_limits<unsigned>::max();

  for(auto& edge: edgeinfo) {
    if (edge.first.first > this->maxvertexindex or edge.first.second > this->maxvertexindex) {
      this->maxvertexindex = std::max(edge.first.first, edge.first.second);
    }

    if (edge.first.first < this->minvertexindex or edge.first.second < this->minvertexindex) {
      this->minvertexindex = std::min(edge.first.first, edge.first.second);
    }
  }

  this->maxvertexindex++;
  this->adjacencymatrix.resize(this->maxvertexindex);
  for(auto& ithrow: this->adjacencymatrix) {
    ithrow.resize(this->maxvertexindex);
  }

  // undirected graph

  for(auto& edge: edgeinfo) {
    if (edge.first.first != edge.first.second) { // not allowing self loops cost
      this->adjacencymatrix[edge.first.first][edge.first.second] = edge.second;
      this->adjacencymatrix[edge.first.second][edge.first.first] = edge.second;
    }
  }
}

const void SimpleGraph::printAdjmatrix()  const {
  for(unsigned s = this->minvertexindex; s < this->maxvertexindex; s++) {
    std::cout << s << ' ';
  }
  std::cout << std::endl;

  for (unsigned i = this->minvertexindex; i < this->maxvertexindex; i++) {
    for (unsigned j = this->minvertexindex; j < this->maxvertexindex; j++) {
      if (this->adjacencymatrix[i][j] != 0) {
        std::cout << this->adjacencymatrix[i][j] << ' ';
      } else {
        std::cout << '_' << ' ';
      }
    }
    std::cout << " :" << i << std::endl;
  }
}

std::ostream& operator<<( std::ostream& COUT, SimpleGraph& graph) {
  graph.printAdjmatrix();
  return COUT;
}
