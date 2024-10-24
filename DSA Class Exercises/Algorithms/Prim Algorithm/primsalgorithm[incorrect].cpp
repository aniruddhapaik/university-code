#include <unordered_map>
#include <limits>
#include <vector>

#include "../../Data Structures/Graphs/Graph for Prim's Algorithm/FiniteMultiGraph.h"
#include "../../Data Structures/Graphs/Graph for Prim's Algorithm/Vertex.h"
#include "../../Data Structures/Graphs/Graph for Prim's Algorithm/utils.h"

void primsalgorithm(FiniteMultiGraph& graph) {
  Vertex* vertex = graph.allnodes.find(graph.source)->second;
  unsigned mincost = 0;
  unsigned nextvertexchoice = graph.source;

  while(true) {
    if (vertex->visited == false) { 
      graph.path.emplace_back(vertex->key, mincost);

      vertex->visited = true; 
    }
    else { return; }

    mincost = std::numeric_limits<unsigned>::max();

    for (auto& vertexkeycostpair: vertex->linksandcost) {
      if (vertexkeycostpair.second < mincost) {
        if (graph.allnodes.find( vertexkeycostpair.first )->second->visited == false) {
          mincost = vertexkeycostpair.second;
          nextvertexchoice = vertexkeycostpair.first;
        }
      }
    }

    vertex = graph.allnodes.find(nextvertexchoice)->second;
  }
}