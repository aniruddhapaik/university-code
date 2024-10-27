#include <iostream>
#include <limits>
#include <unordered_set>
#include <vector>

class Dijkstra {
 public:
  void setAdjMatrix(std::vector<std::vector<int>>& adjmatrix) {
    this->adjacencymatrix = adjmatrix;
    this->costmatrix = adjmatrix;
    this->maxvertices = adjmatrix.size();

    this->setPathFromSource();
  }

  const void setSource(size_t src) {
    if (src >= 0 and src < this->maxvertices) {
      this->source = src;
      // -------------------------------------------
      size_t t = this->maxvertices;
      std::unordered_set<size_t> set;
      set.reserve(t);
      for (size_t i = 0; i < t; i++) {
        set.emplace(i);
      }
      // --------------------------------------------
      set.erase(this->source);
      this->findPaths(this->source, set, 0);

      std::cout << "\nCost from source AFTER running algorithm\n";
      std::cout << "-----------------------------------------" << std::endl;
      this->printPathDetails();
    } else {
      std::cout << "Invalid source node" << std::endl;
    }
  }

  const void printPathDetails() const {
    for (size_t i = 0; i < this->maxvertices; i++) {
      std::cout << "Vertex " << i << ": ";
      for (size_t j = 0; j < this->maxvertices; j++) {
        if (i == j) {
          continue;
        }
        std::cout << j;
        if (this->costmatrix[i][j]) {
          std::cout << "(c: " << this->costmatrix[i][j] << ") ";
        } else {
          std::cout << "( .. ) ";
        }
      }
      std::cout << std::endl;
    }

    std::cout << "Path from source for each vertex\n";
    for(size_t i = 0; i < this->maxvertices; i++) {
      if (i == this->source) { continue; }
      std::cout << "Vertex " << i << ": ";
      for (auto& j: this->pathfromsource[i]) {
        std::cout << j << " -> ";
      }
      std::cout << i << std::endl;
    }
  }

 private:
  void findPaths(int i, std::unordered_set<size_t>& set, int costfromsource) {
    if (set.size()) {
      for (auto& j : set) {
        if (this->adjacencymatrix[i][j] != 0) {
          if (this->costmatrix[this->source][j] >
                  costfromsource + this->costmatrix[i][j] or
              this->costmatrix[this->source][j] == 0) {
            this->costmatrix[this->source][j] =
                costfromsource + this->costmatrix[i][j];
          }

          std::unordered_set<size_t> newset = set;
          newset.erase(j);
          findPaths(j, newset,
                    costfromsource + this->costmatrix[this->source][j]);
        }
      }
    }
  }

  void setPathFromSource() {
    for (size_t i = 0; i < this->maxvertices; i++) {
      for (size_t j = 0; j < this->maxvertices; j++) {
        if (this->costmatrix[i][j] != 0) {
          this->pathfromsource[i].emplace_back(j);
        }
      }
    }
  }

 private:
  std::vector<std::vector<int>> adjacencymatrix;
  std::vector<std::vector<int>> costmatrix;
  std::vector<std::vector<size_t>> pathfromsource;
  size_t source = 0;
  size_t maxvertices = 0;
};

int main() {
  std::vector<std::vector<int>> dijkstrasadjmatrix{
      {0, 2, 4, 0, 0, 0}, {0, 0, 1, 7, 0, 0}, {0, 0, 0, 0, 3, 0},
      {0, 0, 0, 0, 0, 1}, {0, 0, 0, 2, 0, 5}, {0, 0, 0, 0, 0, 0}};
  size_t source = 0;

  std::cout << "** Dijkstra's Algorithm with Adjacency Matrix **\n";
  std::cout << "================================================\n";
  std::cout << "------------\n";
  std::cout << "Source: " << source << '\n';
  std::cout << "------------" << std::endl;
  Dijkstra dijalgo;
  dijalgo.setAdjMatrix(dijkstrasadjmatrix);
  std::cout << "Cost from source BEFORE running algorithm\n";
  std::cout << "-----------------------------------------" << std::endl;
  dijalgo.printPathDetails();
  dijalgo.setSource(source);  // 0 to n-1

  return 0;
}