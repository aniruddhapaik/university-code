#include <vector>
#include <iostream>
#include <iosfwd>
#include "FiniteMultiGraph.h"
#include "utils.h"
#include "Vertex.h"

void FiniteMultiGraph::builGraph(std::vector<edgewithcost>& edges) {
  for (auto& pair: edges) {
    if (this->allnodes.find(pair.first.first) == this->allnodes.end()) {
      this->allnodes.emplace(pair.first.first, new Vertex(pair.first.first));
    }

    if (this->allnodes.find(pair.first.second) == this->allnodes.end()) {
      this->allnodes.emplace(pair.first.second, new Vertex(pair.first.second));
    }

    Vertex* first = this->allnodes.find(pair.first.first)->second;
    Vertex* second = this->allnodes.find(pair.first.second)->second;

    if (first->linksandcost.find( pair.first.second ) == first->linksandcost.end()) {
      first->linksandcost.emplace( pair.first.second, pair.second );
    }

    if (second->linksandcost.find( pair.first.first ) == second->linksandcost.end()) {
      second->linksandcost.emplace( pair.first.first, pair.second );
    }
  }
}

const void FiniteMultiGraph::setSource(unsigned vertexkey) {
  if (this->allnodes.find( vertexkey ) != this->allnodes.end()) {
    this->source = vertexkey;
    std::cout << "Source set to: " << this->source << std::endl;
  } else {
    std::cout << "Error: Vertex not found in graph; source not set." << std::endl;
  }
}

const void FiniteMultiGraph::printPath() const {
  unsigned totalcost = 0;
  std::cout << "Format: [ VERTEX ]--(EDGE COST)-->[ VERTEX ]\n" << std::endl;
  for(auto& vertex: this->path) {
    std::cout << "--(" << vertex.second << ")-->[ " << vertex.first << " ]";
    totalcost += vertex.second;
  }
  std::cout << "\n\nTotal cost: " << totalcost << std::endl;
}

std::ostream& operator<<(std::ostream& COUT, FiniteMultiGraph& graph) {
  graph.printPath();
  return COUT;
}