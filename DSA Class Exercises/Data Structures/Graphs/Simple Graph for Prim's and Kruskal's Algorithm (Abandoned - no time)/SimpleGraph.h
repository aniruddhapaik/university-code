#pragma once

#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>
//#include <optional>

#include "../../Different Types of Queues/\
Priority Queue - Min Heap/MinHeapPriorityQueue.h"
#include "GraphNode.h"
#include "../../../Algorithms/Prim Algorithm/primsalgorithm2.h"

using edge = std::pair<char, char>;
using edgeandcost = std::pair<edge, int>;

template <typename T>
void primsAlgo(SimpleGraph<T>&);

template <typename T>
class SimpleGraph {
 public:
  void buildGraph(std::vector<edgeandcost>& graphdetails) {
    for (auto& edge : graphdetails) {
      char firstvertex = edge.first.first;
      char secondvertex = edge.first.second;

      if (firstvertex != secondvertex) {
        GraphNode<T>* tempnode1 = nullptr;
        GraphNode<T>* tempnode2 = nullptr;

        if (this->allnodes.find(firstvertex) == this->allnodes.end()) {
          tempnode1 = new GraphNode<T>(firstvertex);
          this->allnodes.emplace(firstvertex, tempnode1);
        } else {
          tempnode1 = this->allnodes.find(firstvertex)->second;
        }

        if (this->allnodes.find(secondvertex) == this->allnodes.end()) {
          tempnode2 = new GraphNode<T>(secondvertex);
          this->allnodes.emplace(secondvertex, tempnode2);
        } else {
          tempnode2 = this->allnodes.find(secondvertex)->second;
        }

        if (tempnode1->adjacentedgeandcost.find(secondvertex) !=
            tempnode1->adjacentedgeandcost.end()) {
          // edge already existed, removing parallel edge by keeping the
          // least costly one

          if (edge.second <
              tempnode1->adjacentedgeandcost.find(secondvertex)->second) {
            tempnode1->adjacentedgeandcost.find(secondvertex)->second =
                edge.second;

            tempnode2->adjacentedgeandcost.find(firstvertex)->second =
                edge.second;
          }
        }

        tempnode1->adjacentedgeandcost.emplace(secondvertex, edge.second);
        tempnode2->adjacentedgeandcost.emplace(firstvertex, edge.second);
      }
    }
  }

  void setSource(T src) { this->source = src; }

  const void printVertexInfo() const {
    for (auto& vertex : this->allnodes) {
      std::cout << vertex.first << ": ";
      for (auto& adjc : vertex.second->adjacentedgeandcost) {
        std::cout << adjc.first << '(' << adjc.second << "), ";
      }
      std::cout << '\n';
    }
    std::cout << std::endl;
  }

 private:
   friend void primsAlgo<T>(SimpleGraph<T>&);

 private:
  T source = T();
  std::unordered_map<T, GraphNode<T>*> allnodes;
  MinHeapPriorityQueue<GraphNode<T>*> pqueue;
};