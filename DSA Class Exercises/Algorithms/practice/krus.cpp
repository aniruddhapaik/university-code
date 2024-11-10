#include <iostream>
#include <unordered_set>
#include <vector>

std::vector<std::vector<size_t>> edgesandcost = {
    {0, 1, 1}, {0, 2, 5},  {1, 2, 4}, {1, 4, 7}, {1, 3, 8},  {2, 3, 6},
    {2, 5, 2}, {3, 4, 11}, {3, 5, 9}, {4, 5, 3}, {4, 6, 10}, {5, 6, 12}};

std::vector<std::vector<size_t>> edgesandcost2 = {
    {1, 0, 1}, {1, 2, 6},  {0, 2, 6}, {0, 3, 5}, {2, 4, 7},
    {3, 5, 2}, {3, 6, 10}, {6, 7, 7}, {5, 7, 8}, {4, 7, 12},
    {2, 5, 3}, {7, 8, 8},  {6, 8, 3}};

class Kruskal {
  std::vector<std::vector<size_t>> adjmatrix;
  std::unordered_set<size_t> visited;
  std::vector<std::vector<size_t>> pqueue;
  size_t maxnodes = 0;

  std::vector<std::vector<size_t>> mst;

 public:
  void buildAdj(std::vector<std::vector<size_t>>& edgesandcost, size_t maxv) {
    this->maxnodes = maxv;
    this->adjmatrix.resize(this->maxnodes);
    for (auto& row : this->adjmatrix) {
      row.resize(this->maxnodes);
    }

    for (auto& edge : edgesandcost) {
      this->adjmatrix[edge[0]][edge[1]] = edge[2];
      this->adjmatrix[edge[1]][edge[0]] = edge[2];
    }

    this->sortToPQueue(edgesandcost);
  }

  void buildMST() {
    size_t index = 0;
    this->visited.emplace(this->pqueue[0][0]);
    this->visited.emplace(this->pqueue[0][1]);
    this->addToMST(this->pqueue[0]);

    while (index < this->pqueue.size()) {
      auto& edge = this->pqueue[index];
      if (this->visited.find(edge[0]) != this->visited.end() and
          this->visited.find(edge[1]) == this->visited.end()) {
        this->visited.emplace(edge[1]);
        this->addToMST(edge);
        index = 0;
      } else if (this->visited.find(edge[1]) != this->visited.end() and
                 this->visited.find(edge[0]) == this->visited.end()) {
        this->visited.emplace(edge[0]);
        this->addToMST(edge);
        index = 0;
      }
      index++;
    }
  }

  const void printMST() const {
    size_t cost = 0;
    for (auto& edge : this->mst) {
      std::cout << edge[0] << " to " << edge[1] << " cost=" << edge[2]
                << std::endl;
      cost += edge[2];
    }
    std::cout << "----\nTotal Cost = " << cost << std::endl;
  }

 private:
  void sortToPQueue(std::vector<std::vector<size_t>>& edgesandcost) {
    for (auto& edge : edgesandcost) {
      size_t index = 0;
      while (index < this->pqueue.size()) {
        if (edge[2] < this->pqueue[index][2]) {
          this->pqueue.emplace(this->pqueue.begin() + index, edge);
          break;
        }
        index++;
      }
      if (index == this->pqueue.size()) {
        this->pqueue.emplace(this->pqueue.end(), edge);
      }
    }
  }

  void addToMST(std::vector<size_t>& edge) { this->mst.emplace_back(edge); }
};

int main() {
  size_t maxnodes = 7;
  Kruskal kruskal;
  kruskal.buildAdj(edgesandcost, maxnodes);
  kruskal.buildMST();
  kruskal.printMST();
  return 0;
}