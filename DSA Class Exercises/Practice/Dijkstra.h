#pragma once
#include <vector>
#include <iostream>
#include <unordered_set>

class Dijkstra {
public:
  void getAdjMatrix(std::vector<std::vector<int>>& adjmatrix) {
    this->adjacencymatrix = adjmatrix;
    this->costmatrix = adjmatrix;
  }

  const void setSource(size_t src) {
    if (src > 0 and src < this->adjacencymatrix.size()) {
      this->source = src-1;
      // -------------------------------------------
      size_t t = this->adjacencymatrix.size();
      std::unordered_set<size_t> set;
      set.reserve(t);
      for(size_t i = 0; i < t; i++) { set.emplace(i); }
      // --------------------------------------------
      set.erase(this->source);
      this->findPaths(this->source, set, 0);

      for (auto& list: this->costmatrix) {
        for (auto& i: list) {
          std::cout << i << ' ';
        }
        std::cout << std::endl;
      }

    } else {
      std::cout << "Invalid source node" << std::endl;
    }
  }

private:
  void findPaths(int i, std::unordered_set<size_t>& set, int costfromsource) {
    if (set.size()) {
      for (auto& j : set) {
        if (this->adjacencymatrix[i][j] != 0) {
          if (this->costmatrix[this->source][j] > costfromsource+this->costmatrix[i][j]
               or !(this->costmatrix[this->source][j] == 0)) {
            this->costmatrix[this->source][j] = costfromsource+this->costmatrix[i][j];
          }

          std::unordered_set<size_t> newset = set;
          newset.erase(j);
          findPaths(j, newset, costfromsource+this->costmatrix[i][j]);
        }
      }
    }
  }

private:
  std::vector<std::vector<int>> adjacencymatrix;
  std::vector<std::vector<int>> costmatrix;
  size_t source = 0;
};