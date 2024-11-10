#include <iostream>
#include <unordered_set>
#include <vector>
#include <utility>

enum class nodelabel : size_t { a, b, c, d, e, f, g, h, i };

std::vector<std::vector<size_t>> edgesandcost = {
    {0, 1, 1}, {0, 2, 5},  {1, 2, 4}, {1, 4, 7}, {1, 3, 8},  {2, 3, 6},
    {2, 5, 2}, {3, 4, 11}, {3, 5, 9}, {4, 5, 3}, {4, 6, 10}, {5, 6, 12}};

std::vector<std::vector<size_t>> edgesandcost2 = {
    {1, 0, 1}, {1, 2, 6},  {0, 2, 6}, {0, 3, 5}, {2, 4, 7},
    {3, 5, 2}, {3, 6, 10}, {6, 7, 7}, {5, 7, 8}, {4, 7, 12},
    {2, 5, 3}, {7, 8, 8},  {6, 8, 3}};

class Prim {
  std::vector<std::vector<size_t>> adjmatrix;
  std::unordered_set<size_t> visited;
  std::vector<std::vector<size_t>> pqueue;
  size_t maxvertices = 0;
  size_t source = 0;

  std::vector<std::vector<size_t>> mst;

 public:
  void buildAdj(std::vector<std::vector<size_t>>& edgesandcost, size_t maxv,
                size_t src) {
    this->maxvertices = maxv;
    this->source = src;
    this->adjmatrix.resize(this->maxvertices);
    for (auto& row : this->adjmatrix) {
      row.resize(this->maxvertices);
    }

    for (auto& edge : edgesandcost) {
      this->adjmatrix[edge[0]][edge[1]] = edge[2];
      this->adjmatrix[edge[1]][edge[0]] = edge[2];
    }
  }

  void explore() {
    size_t selectednode = this->source;
    this->visited.emplace(selectednode);
    this->addToPqueue(selectednode);

    size_t index = 0;
    while (index < this->pqueue.size()) {
      auto& edge = this->pqueue[index];
      if (this->visited.find(edge[0]) != this->visited.end()) {
        if (this->visited.find(edge[1]) == this->visited.end()) {
          this->addToMST(edge);
          this->visited.emplace(edge[1]);
          selectednode = edge[1];
          this->addToPqueue(selectednode);
          index = 0;
        }
      } else if (this->visited.find(edge[1]) != this->visited.end()) {
        if (this->visited.find(edge[0]) == this->visited.end()) {
          this->addToMST(edge);
          this->visited.emplace(edge[0]);
          selectednode = edge[0];
          this->addToPqueue(selectednode);
          index = 0;
        }
      }
      index++;
    }
  }

  const void printMST() const {
    size_t cost = 0;
    for (auto& edge : this->mst) {
      std::cout << edge[0] << " - " << edge[1] << " cost=" << edge[2]
                << std::endl;
      cost += edge[2];
    }
    std::cout << "-----\nTotal Cost = " << cost << std::endl;
  }

 private:
  void addToPqueue(size_t node) {
    for (size_t col = 0; col < this->maxvertices; col++) {
      bool inserted = false;
      size_t cost = this->adjmatrix[node][col];
      if (cost != 0) {
        size_t qedge = 0;
        while (qedge < this->pqueue.size()) {
          if (cost < this->pqueue[qedge][2] and
              this->visited.find(col) == this->visited.end()) {
            this->pqueue.emplace(this->pqueue.begin() + qedge,
                                 std::vector<size_t>{node, col, cost});
            break;
          }
          qedge++;
        }
        if (qedge == this->pqueue.size()) {
          this->pqueue.emplace_back(std::vector<size_t>{node, col, cost});
          continue;
        }
      }
    }
  }

  void addToMST(std::vector<size_t>& edge) { this->mst.emplace_back(edge); }
};

int main() {
  size_t maxvertices = 7;
  size_t source = 0;
  Prim prim;
  prim.buildAdj(edgesandcost, maxvertices, source);
  prim.explore();
  prim.printMST();
  return 0;
}