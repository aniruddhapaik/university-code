#include <vector>
#include <iostream>

#include "SimpleGraph.h"
#include "utils.h"

int main() {
  SimpleGraph graph;

  std::vector<edgelinkcost> edgeinfo = {
    {{1,4},1},{{1,2},2},{{4,3},3},{{2,3},4},{{3,10},5},{{3,9},6},{{2,5},7},
    {{2,8},8},{{5,8},9},{{5,7},1},{{8,7},2},{{5,6},3},{{2,7},4}
  };

  graph.buildGraph(edgeinfo);

  std::cout << graph;

  graph.setSource(1);

  std::cout << "\nBreadth First Search: \n";
  breadthfirstsearch(graph);
  std::cout << std::endl;

  std::cout << "\nDepth First Search: \n";
  depthfirstsearch(graph);
  std::cout << std::endl;

  return 0;
}