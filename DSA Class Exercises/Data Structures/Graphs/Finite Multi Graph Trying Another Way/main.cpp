#include <iostream>
#include <limits>
#include "finitemultigraph.h"
#include "directionenum.h"
#include <vector>

int main() {
  FiniteMultiGraph graph;

  std::vector<edgecost> edgeinfo {
    {{1,2}, 2}, {{1,3}, 4}, {{2,3}, 1}, {{2,4}, 7}, 
    {{3,5}, 3}, {{4,6}, 1}, {{5,4}, 2}, {{5,6}, 5}
  };

  graph.getEdgeList(Direction::directed, edgeinfo);
  graph.setSource(1);
  std::cout << graph;
  graph.Explore();
  std::cout << graph;
  
  return 0;
}