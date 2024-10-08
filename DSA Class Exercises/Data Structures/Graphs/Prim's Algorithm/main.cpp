#include <vector>
#include <iostream>

#include "FiniteMultiGraph.h"
#include "utils.h"

void primsalgorithm(FiniteMultiGraph& graph);

int main() {
  FiniteMultiGraph graph;

  std::vector<edgewithcost> graphinfo1 = {
    {{6,1},10}, {{1,2},28}, {{2,3},16}, {{3,4},12}, {{4,5}, 22},
    {{2,7},14}, {{7,5},24}, {{6,5},25}, {{4,7},18}
  };

  graph.builGraph(graphinfo1);
  graph.setSource(1);
  primsalgorithm(graph);
  std::cout << graph << std::endl;

  return 0;
}