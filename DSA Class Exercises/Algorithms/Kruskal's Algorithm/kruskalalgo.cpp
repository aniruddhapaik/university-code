#include <iostream>
#include <unordered_set>
#include <utility>
#include <vector>

class KruskalAlgo {
 public:
  KruskalAlgo(
      size_t v,
      std::vector<std::pair<std::pair<size_t, size_t>, int>>& edgedetails) {
    this->maxvertices = v;
    this->adjlinks.resize(v);

    this->enqueueAll(edgedetails);
    this->buildMST();
  }

  const void printMSTEdges() const {
    std::cout << "** Minimum Spanning Tree with Kruskal's Algorithm **\n";
    std::cout << "====================================================\n";
    for (auto& edge : this->mstlinks) {
      std::cout << '(' << edge.first << ',' << edge.second << ") ";
    }
    std::cout << "\nTotal cost: " << this->totalcost << '\n' << std::endl;
  }

 private:
  void buildMST() {
    for (auto& edge : this->pqueue) {
      if (this->visited.find(edge.first.first) != this->visited.end() and
          this->visited.find(edge.first.second) != this->visited.end()) {
        if (this->detectCycle(edge.first.first, edge.first.first,
                              edge.first.second)) {
          continue;
        } else {
          this->mstlinks.emplace_back(edge.first.first, edge.first.second);

          this->adjlinks[edge.first.first].emplace(edge.first.second);
          this->adjlinks[edge.first.second].emplace(edge.first.first);
          this->totalcost += edge.second;
        }
      } else if (this->visited.find(edge.first.first) == this->visited.end() and
                 this->visited.find(edge.first.second) != this->visited.end()) {
        this->visited.emplace(edge.first.first);
        this->mstlinks.emplace_back(edge.first.first, edge.first.second);

        this->adjlinks[edge.first.second].emplace(edge.first.first);
        this->adjlinks[edge.first.first].emplace(edge.first.second);
        this->totalcost += edge.second;
      } else if (this->visited.find(edge.first.first) != this->visited.end() and
                 this->visited.find(edge.first.second) == this->visited.end()) {
        this->visited.emplace(edge.first.second);
        this->mstlinks.emplace_back(edge.first.first, edge.first.second);

        this->adjlinks[edge.first.second].emplace(edge.first.first);
        this->adjlinks[edge.first.first].emplace(edge.first.second);
        this->totalcost += edge.second;
      } else {
        this->visited.emplace(edge.first.first);
        this->visited.emplace(edge.first.second);
        this->adjlinks[edge.first.second].emplace(edge.first.first);

        this->adjlinks[edge.first.first].emplace(edge.first.second);
        this->mstlinks.emplace_back(edge.first.first, edge.first.second);
        this->totalcost += edge.second;
      }
    }
  }

  bool detectCycle(size_t vertex, size_t previousvertex, size_t lookforv) {
    std::unordered_set<size_t>& vertexadjs = this->adjlinks[vertex];
    if (vertexadjs.find(lookforv) == vertexadjs.end()) {
      for (auto& v : vertexadjs) {
        if (v != previousvertex) {
          if (this->detectCycle(v, vertex, lookforv)) {
            return true;
          }
        }
      }
    } else {
      return true;
    }
    return false;
  }

  void enqueueAll(
      std::vector<std::pair<std::pair<size_t, size_t>, int>>& edgedetails) {
    for (auto& edge : edgedetails) {
      if (this->pqueue.size()) {
        size_t index = 0;
        bool inserted = false;
        while (index < this->pqueue.size()) {
          // checking which edge's cost is lower
          if (edge.second < this->pqueue[index].second) {
            this->pqueue.emplace(this->pqueue.begin() + index, edge);
            inserted = true;
            break;
          }
          index++;
        }
        if (not inserted) {
          this->pqueue.emplace_back(edge);
        }
      } else {
        this->pqueue.emplace_back(edge);
      }
    }
  }

 private:
  std::vector<std::pair<std::pair<size_t, size_t>, int>> pqueue;

  size_t maxvertices;

  std::unordered_set<size_t> visited;
  std::vector<std::unordered_set<size_t>> adjlinks;
  std::vector<std::pair<size_t, size_t>> mstlinks;
  int totalcost = 0;
};

int main() {
  std::vector<std::pair<std::pair<size_t, size_t>, int>> edgedetails = {
      {{1, 0}, 1}, {{1, 2}, 6},  {{0, 2}, 6}, {{0, 3}, 5}, {{2, 4}, 7},
      {{3, 5}, 2}, {{3, 6}, 10}, {{6, 7}, 7}, {{5, 7}, 8}, {{4, 7}, 12},
      {{2, 5}, 3}, {{7, 8}, 8},  {{6, 8}, 3}};

  std::cout << "> Graph 1\n";
  std::cout << "---------\n";
  KruskalAlgo krus(9, edgedetails);
  krus.printMSTEdges();

  std::vector<std::pair<std::pair<size_t, size_t>, int>> edgedetails2 = {
      {{1, 6}, 10}, {{1, 2}, 28}, {{2, 3}, 16}, {{2, 7}, 14}, {{3, 4}, 12},
      {{7, 4}, 18}, {{4, 5}, 22}, {{7, 5}, 24}, {{6, 5}, 25}};

  std::cout << "> Graph 2\n";
  std::cout << "---------\n";
  KruskalAlgo krus2(8, edgedetails2);
  krus2.printMSTEdges();

  return 0;
}