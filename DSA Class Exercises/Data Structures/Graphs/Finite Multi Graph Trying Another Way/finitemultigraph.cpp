#include "finitemultigraph.h"
#include <utility>
#include <vector>
#include "vertex.h"
#include "directionenum.h"
#include <iostream>
#include <iosfwd>
#include <limits>

FiniteMultiGraph::FiniteMultiGraph() {
  this->direction = Direction::directed;
  this->source = 0;
  this->current_visiting_node = 0;
}

const void FiniteMultiGraph::getEdgeList(Direction dir, std::vector<edgecost>& edgelist) {
  this->direction = dir;
  this->buildGraph(edgelist);
}

const void FiniteMultiGraph::setSource(unsigned int src) {
  auto result = this->allnodes.find(src);
  if (result == this->allnodes.end()) {
    std::cout << "No such node found!" << std::endl;
  } else {
    this->source = src;
    this->current_visiting_node = this->source;

    (*result).second->cost_from_source = 0;
    (*result).second->visited = true;
    std::cout << "Source set: " << this->source << std::endl;
  }
}

const void FiniteMultiGraph::printVerticesInfo() const {
  for (auto& pair: this->allnodes) {
    std::cout << "Vertex " << pair.second->label << std::endl;

    if (pair.second->cost_from_source == std::numeric_limits<unsigned int>::max())  {
      std::cout << "  Source to Vertex cost: INFINITY\n";
    } else {
      std::cout << "  Source to Vertex cost: " << pair.second->cost_from_source << '\n';
    }

    std::cout << "  Links to Vertex(Edge Cost): ";
    for (auto& pair: pair.second->linksandcost) {
      std::cout << pair.first << '(' << pair.second << ") | ";
    }
    std::cout << "\n---------" << std::endl;
  }
}

void FiniteMultiGraph::buildGraph(std::vector<edgecost>& edgelist) {
  for (edgecost& pair: edgelist) {
    // creating a vertex if it already does not exist
    if (this->allnodes.find(pair.first.first) == this->allnodes.end()) {
      this->allnodes.emplace(pair.first.first, new Vertex(pair.first.first));
    } 
    
    // creating a vertex if it already does not 
    if (this->allnodes.find(pair.first.second) == this->allnodes.end()) {
      this->allnodes.emplace(pair.first.second, new Vertex(pair.first.second));
    }

    // making the directed link between previous two vertices
    // setting vertex 1's neighbor: vertex 2
    this->allnodes.find(pair.first.first)->second->linksandcost.emplace(pair.first.second, pair.second);
  
    if (this->direction == Direction::undirected) {
      // setting vertex 2's neighbor: vertex 1 (if the graph is undirected)
      this->allnodes.find(pair.first.second)->second->linksandcost.emplace(pair.first.first, pair.second);
    }
  }
}

void FiniteMultiGraph::Explore() {
  Vertex* current_node = this->allnodes.find(this->current_visiting_node)->second;
  if (current_node->visited == true) {
    this->Relax(current_node);
  }
}

void FiniteMultiGraph::Relax(Vertex* vertex) {
  unsigned int choose_next_node_to_visit {vertex->label};
  for (auto& pair: vertex->linksandcost) {
    Vertex* exploring_vertex = this->allnodes.find(pair.first)->second;
    if (exploring_vertex->visited == false) {
      if ((vertex->cost_from_source + pair.second) < exploring_vertex->cost_from_source) {
        exploring_vertex->cost_from_source = vertex->cost_from_source + pair.second;
      }

    }
  }
}

std::ostream& operator<<(std::ostream& COUT, const FiniteMultiGraph& graph) {
  graph.printVerticesInfo();
  return COUT;
}
