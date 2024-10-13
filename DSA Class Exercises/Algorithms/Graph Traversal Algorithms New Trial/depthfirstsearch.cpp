#include "../../Data Structures/Graphs/Simple Graph for DFS and BFS/SimpleGraph.h"
#include <unordered_map>
#include <iostream>

void explore(unsigned row, SimpleGraph& graph, std::unordered_map<unsigned, bool>& stack) {
  if (graph.vertexvisitedlist.find(row) == graph.vertexvisitedlist.end()) {
    stack.emplace(row, true);
    std::cout << row << ' ';
    for(unsigned col = graph.minvertexindex; col < graph.maxvertexindex; col++) {
      if (stack.find(col) == stack.end() and graph.adjacencymatrix[row][col] != 0) {
        explore(col, graph, stack);
        stack.erase(col);
      }
    }
    graph.vertexvisitedlist.emplace(row, true);
  }
}

void depthfirstsearch(SimpleGraph& graph) {
  graph.vertexvisitedlist.clear();

  std::unordered_map<unsigned, bool> stack;
  explore(graph.source, graph, stack);
}