#include <iostream>
#include <utility>
#include <vector>

#include "../../../Algorithms/Prim Algorithm/primsalgorithm2.h"
#include "SimpleGraph.h"

int main() {
  std::vector<std::pair<std::pair<char, char>, int>> graphdetails = {
      {{'b', 'a'}, 1}, {{'b', 'c'}, 6},  {{'a', 'c'}, 6},  {{'a', 'd'}, 5},
      {{'c', 'e'}, 7}, {{'d', 'f'}, 2},  {{'d', 'g'}, 10}, {{'g', 'h'}, 7},
      {{'f', 'h'}, 8}, {{'e', 'h'}, 12}, {{'c', 'f'}, 3},  {{'h', 'i'}, 8},
      {{'g', 'i'}, 3}};

  SimpleGraph<char> graph;

  graph.buildGraph(graphdetails);
  graph.printVertexInfo();
  graph.setSource('b');

  primsAlgo(graph);

  return 0;
}