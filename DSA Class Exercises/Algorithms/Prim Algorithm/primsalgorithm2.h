#pragma once

#include <iostream>
#include <utility>
#include <vector>

#include "../../Data Structures/Different Types of Queues/\
Priority Queue With Array Header file/PriorityQueueArray.h"

template <typename T>
class SimpleGraph;

#include <unordered_map>

#include "../../Data Structures/Graphs/\
Simple Graph for Prim's and Kruskal's Algorithm/GraphNode.h"
#include "../../Data Structures/Graphs/\
Simple Graph for Prim's and Kruskal's Algorithm/SimpleGraph.h"

template <typename T>
class Edge {
 public:
  Edge(int cp, T v1, T v2) {
    this->costorpriority = cp;
    this->vertex1 = v1;
    this->vertex2 = v2;
  }

  int costorpriority;
  T vertex1;
  T vertex2;
};

template <typename T>
void primsAlgo(SimpleGraph<T>& graph) {
  GraphNode<T>* node = graph.allnodes.find(graph.source)->second;
  PriorityQueueArray<Edge<GraphNode<T>*>> pq;
  std::unordered_map<T, GraphNode<T>*> visited;

  while (true) {
    if (visited.size() == graph.allnodes.size()) {
      break;
    }

    for (auto& edgecost : node->adjacentedgeandcost) {
      Edge<GraphNode<T>*>* e = new Edge<T>(edgecost.second, node->key, edgecost.first);
      pq.enqueue(e);
    }

    //pq.displayQueue();
    break;
    typename std::vector<Edge<T>*>::iterator it = pq.queue.begin();
    while(it != pq.queue.end()) {
      if (node->adjacentedgeandcost.find(it->vertex1) {
        if (it->vertex)
      }

      if (it->vertex2 == node->key) {
      
      }

      it++;
    }
  }
}