#include "../../Data Structures/Graphs/Simple Graph for DFS and BFS/SimpleGraph.h"
#include <queue>
#include <iostream>

void breadthfirstsearch(SimpleGraph& graph) {
  graph.vertexvisitedlist.clear();

  std::queue<unsigned> queue;
  queue.push(graph.source);
  graph.vertexvisitedlist.emplace(graph.source, true);

  while(queue.size()) {
    for (unsigned j = graph.minvertexindex; j < graph.maxvertexindex; j++) {
      unsigned cell = graph.adjacencymatrix[queue.front()][j];
      if (cell != 0) {
        if (graph.vertexvisitedlist.find( j ) == graph.vertexvisitedlist.end()) {
          queue.push( j ); // visited
          graph.vertexvisitedlist.emplace(j, true);
        }
      }
    }
    std::cout << queue.front() << ' ';
    queue.pop();
  }
}