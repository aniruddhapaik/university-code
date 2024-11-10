#include <iostream>
#include <unordered_set>
#include <utility>
#include <vector>

enum class nodelabel : size_t { a, b, c, d, e, f, g, h, i };

std::vector<std::vector<size_t>> edgesandcost = {
    {0, 1, 1}, {0, 2, 5},  {1, 2, 4}, {1, 4, 7}, {1, 3, 8},  {2, 3, 6},
    {2, 5, 2}, {3, 4, 11}, {3, 5, 9}, {4, 5, 3}, {4, 6, 10}, {5, 6, 12}};

class Prim {
  std::vector<std::vector<size_t>> adjmatrix;
  std::unordered_set<size_t> visited;
  std::vector<std::vector<size_t>> pqueue;
  size_t maxvertices = 0;
  size_t source = 0;

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
  }

 private:
  void addToPqueue(size_t node) {
    for (size_t col = 0; col < this->maxvertices; col++) {
      size_t cost = this->adjmatrix[node][col];
      if (cost != 0) {
        if (not this->pqueue.size()) {
          this->pqueue.emplace(this->pqueue.begin(),
                               std::vector<size_t>{node, col, cost});
          continue;
        }
        size_t qedge = 0;
        while (this->pqueue.size()) {
          if (cost < this->pqueue[qedge][2] and
              this->visited.find(col) == this->visited.end()) {
            this->pqueue.emplace(this->pqueue.begin() + qedge,
                                 std::vector<size_t>{node, col, cost});
            break;
          }
          qedge++;
        }
      }
    }
  }
};

int main() {
  size_t maxvertices = 7;
  size_t source = 0;
  Prim prim;
  prim.buildAdj(edgesandcost, 7, 0);
  prim.explore();
  return 0;
}