#include <iostream>
#include <limits>
#include <unordered_set>
#include <vector>

std::vector<std::vector<int>> adjmatrix = {
    {0, 16, 11, 6}, 
    {8, 0, 13, 16}, 
    {4, 7, 0, 9}, 
    {5, 12, 2, 0}};

class TravellingSalesman {
 public:
  void setSource(int src) {
    if (src >= 0 and src < adjmatrix.size()) {
      this->source = src;
      this->path.resize(adjmatrix.size());

      std::unordered_set<int> newset = {};
      newset.reserve(adjmatrix.size());
      for (int i = 0; i < adjmatrix.size(); i++) {
        newset.emplace(i);
      }
      // --------------------------------------------------------------
      newset.erase(this->source);
      int besttotalcost =
          this->findPath(this->source, newset, adjmatrix.size() - 1);
      // --------------------------------------------------------------
      this->printPath(besttotalcost);
    }
  }

  const void printPath(int cost) const {
    std::cout << "Adjacency Matrix:\n";
    for (auto& row : adjmatrix) {
      for (auto& cell : row) {
        if (cell == 0) {
          std::cout << ". ";
        } else {
          std::cout << cell << ' ';
        }
      }
      std::cout << '\n';
    }
    std::cout << std::endl;

    std::cout << "Best Path: " << this->source;
    int prev = this->source;
    int i = this->path.size() - 1;
    for (; i >= 0; i--) {
      std::cout << " --(c:" << adjmatrix[prev][i] << ")--> " << this->path[i];
      prev = i;
    }
    std::cout << "\nBest Total Cost: " << cost << std::endl;
  }

 private:
  int findPath(int i, std::unordered_set<int>& set, int pathindex) {
    if (set.size()) {
      int mintotalweight = std::numeric_limits<int>::max();
      int possiblechoiceofcity = i;

      for (auto& j : set) {
        std::unordered_set<int> newset = set;

        newset.erase(j);
        int weight = findPath(j, newset, pathindex - 1);

        if (weight < mintotalweight) {
          mintotalweight = weight;
          possiblechoiceofcity = j;
        }
      }

      this->path[pathindex] = possiblechoiceofcity;
      return (mintotalweight + adjmatrix[i][possiblechoiceofcity]);
    }

    return adjmatrix[i][this->source];
  }

 private:
  int source = -1;
  std::vector<int> path;
};

int main() {
  TravellingSalesman salesman;
  salesman.setSource(0);

  return 0;
}