#include <iostream>
#include <vector>

#include "finitemultigraph.h"
#include "directionenum.h"

int main() {
  FiniteMultiGraph graph;

  std::vector<edgecost> edgeinfo1 {
    {{1,2}, 2}, {{1,3}, 4}, {{2,3}, 1}, {{2,4}, 7}, 
    {{3,5}, 3}, {{4,6}, 1}, {{5,4}, 2}, {{5,6}, 5}
  };

  std::vector<edgecost> edgeinfo2 {
    {{1,2}, 7}, {{1,3}, 9}, {{1,6}, 14}, {{2,3}, 10}, {{2,4}, 15},
    {{3,4}, 11}, {{3,6}, 2}, {{4,5}, 6}, {{5,6}, 9}
  };

  graph.getEdgeList(Direction::undirected, edgeinfo2);
  graph.setSource(1);
  std::cout << graph;
  Explore(graph);
  std::cout << graph;
  
  return 0;
}