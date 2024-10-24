#include <iostream>
#include <unordered_set>
#include <utility>
#include <vector>

class PrimAlgo {
 public:
  PrimAlgo(int v, std::vector<std::pair<std::pair<int, int>, int>>& edgedetails,
           int src) {
    this->maxvertices = v;    // max number of vertices
    this->adjlist.resize(v);  // preparing adjacency list for each vertex

    // creating adjacency matrix
    this->adjmatrix.resize(v);
    for (auto& row : this->adjmatrix) {
      row.resize(v, 0);
    }

    // filling up the adjacency matrix to represent an undirected graph
    for (auto& edge : edgedetails) {
      this->adjmatrix[edge.first.first][edge.first.second] = edge.second;
      this->adjmatrix[edge.first.second][edge.first.first] = edge.second;
    }

    this->source = src;  // source vertex

    this->buildMST(this->source);  // going ahead to build the MST
  }

  const void printAdjMatrix() const {
    for (auto& row : this->adjmatrix) {
      for (auto& cell : row) {
        std::cout << cell << ' ';
      }
      std::cout << std::endl;
    }
  }

  const void printMST() const {
    int totalcost = 0;
    for (auto& edge : this->mst) {
      std::cout << '(' << edge.first << ',' << edge.second << ") ";
      totalcost += this->adjmatrix[edge.first][edge.second];
    }
    std::cout << "\nTotal cost: " << totalcost << std::endl;
  }

 private:
  void buildMST(int fromv) {  // parameter means: from vertex
    this->visited.emplace(fromv);

    int tov = 0;  // to vertex
    while (tov < this->maxvertices) {
      // checking which edges exists, if 0 that means edge does not exist
      if (this->adjmatrix[fromv][tov] != 0) {
        if (this->enqueue({{fromv, tov}, this->adjmatrix[fromv][tov]})) {
          this->adjlist[fromv].emplace(tov);
        }
      }
      tov++;
    }

    int index = 0;
    while (index < this->pqueue.size()) {
      // starting with first element in queue
      if ((this->adjlist[fromv].find(this->pqueue[index].first.first) !=
           this->adjlist[fromv].end()) and
          this->visited.find(this->pqueue[index].first.first) ==
              this->visited.end()) {
        if (this->visited.find(this->pqueue[index].first.second) !=
            this->visited.end()) {
          this->mst.emplace_back(this->pqueue[index].first.second,
                                 this->pqueue[index].first.first);
          this->buildMST(this->pqueue[index].first.first);
        }
      } else if ((this->adjlist[fromv].find(this->pqueue[index].first.second) !=
                  this->adjlist[fromv].end()) and
                 this->visited.find(this->pqueue[index].first.second) ==
                     this->visited.end()) {
        if (this->visited.find(this->pqueue[index].first.first) !=
            this->visited.end()) {
          this->mst.emplace_back(this->pqueue[index].first.first,
                                 this->pqueue[index].first.second);
          this->buildMST(this->pqueue[index].first.second);
        }
      }
      index++;
    }
  }

  bool enqueue(std::pair<std::pair<int, int>, int> edge) {
    if (this->pqueue.size()) {
      if (this->visited.find(edge.first.second) != this->visited.end()) {
        return false;
      }

      int index = 0;

      while (index < this->pqueue.size()) {
        if (edge.second < this->pqueue[index].second) {
          this->pqueue.emplace(this->pqueue.begin() + index, edge);
          return true;
        }
        index++;
      }
      this->pqueue.emplace_back(edge);
      return true;
    } else {
      this->pqueue.emplace_back(edge);
    }
    return true;
  }

 private:
  std::vector<std::vector<int>> adjmatrix;
  std::vector<std::pair<std::pair<int, int>, int>> pqueue;

  std::unordered_set<int> visited;
  std::vector<std::unordered_set<int>> adjlist;

  std::vector<std::pair<int, int>> mst;

  int maxvertices;
  int source;
};

int main() {
  std::vector<std::pair<std::pair<int, int>, int>> edgedetails = {
      {{1, 0}, 1}, {{1, 2}, 6},  {{0, 2}, 6}, {{0, 3}, 5}, {{2, 4}, 7},
      {{3, 5}, 2}, {{3, 6}, 10}, {{6, 7}, 7}, {{5, 7}, 8}, {{4, 7}, 12},
      {{2, 5}, 3}, {{7, 8}, 8},  {{6, 8}, 3}};

  PrimAlgo prim(9, edgedetails, 1);
  prim.printMST();

  std::vector<std::pair<std::pair<int, int>, int>> edgedetails2 = {
      {{1, 6}, 10}, {{1, 2}, 28}, {{2, 3}, 16}, {{2, 7}, 14}, {{3, 4}, 12},
      {{7, 4}, 18}, {{4, 5}, 22}, {{7, 5}, 24}, {{6, 5}, 25}};

  PrimAlgo prim2(8, edgedetails2, 1);
  prim2.printMST();

  return 0;
}

// a b c d e f g h i
// 0 1 2 3 4 5 6 7 8