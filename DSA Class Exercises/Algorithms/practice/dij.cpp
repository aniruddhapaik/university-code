#include <iostream>
#include <limits>
#include <unordered_map>
#include <vector>

std::vector<std::vector<int>> edgesandcost = {
    {0, 1, 4}, {0, 4, 8},  {1, 4, 11}, {1, 2, 8}, {4, 5, 1},
    {4, 8, 7}, {2, 8, 2},  {8, 5, 6},  {5, 6, 2}, {2, 6, 4},
    {2, 3, 7}, {3, 6, 14}, {3, 7, 9},  {6, 7, 10}};

class Node {
 public:
  size_t key;
  int costfromsource = std::numeric_limits<int>::max();
  std::vector<size_t> pathfromsource;

  Node(size_t k) { this->key = k; }
};

class Dijkstra {
  std::vector<std::vector<int>> adjmatrix;
  size_t source = 0;
  size_t maxvertices = 0;
  std::unordered_map<size_t, Node*> visitednodes;
  std::vector<Node*> pqueue;

 public:
  void buildAdj(std::vector<std::vector<int>>& edgesandcost, size_t maxv,
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
    Node* node = new Node(this->source);
    node->costfromsource = 0;
    this->pqueue.emplace_back(node);

    while (this->pqueue.size()) {
      node = this->pqueue[0];
      this->visitednodes.emplace(node->key, node);
      this->pqueue.erase(this->pqueue.begin());

      for (size_t col = 0; col < this->maxvertices; col++) {
        int cost = this->adjmatrix[node->key][col];
        if (cost != 0) {
          if (this->visitednodes.find(col) == this->visitednodes.end()) {
            Node* newnode = new Node(col);
            newnode->costfromsource = node->costfromsource + cost;
            newnode->pathfromsource = node->pathfromsource;
            newnode->pathfromsource.emplace_back(node->key);
            this->addToPQueue(newnode);
          } else {
            Node* oldnode = this->visitednodes.find(col)->second;
            if (node->costfromsource + cost < oldnode->costfromsource) {
              oldnode->costfromsource = node->costfromsource + cost;
              oldnode->pathfromsource = node->pathfromsource;
              oldnode->pathfromsource.emplace_back(node->key);

              for (size_t j = 0; j < this->pqueue.size(); j++) {
                Node* old = this->pqueue[j];
                if (oldnode->key == old->key) {
                  this->pqueue.erase(this->pqueue.begin() + j);
                  break;
                }
              }
              this->addToPQueue(oldnode);
            }
          }
        }
      }
    }
  }

  const void printNodeInfo() const {
    for (auto& pair : this->visitednodes) {
      std::cout << this->source << " to " << pair.first;
      std::cout << ": Cost=" << pair.second->costfromsource;
      for (auto& pn : pair.second->pathfromsource) {
        std::cout << ' ' << pn << " -->";
      }
      std::cout << ' ' << pair.first << std::endl;
    }
  }

 private:
  void addToPQueue(Node* node) {
    size_t i = 0;
    while (i < this->pqueue.size()) {
      Node* pnode = this->pqueue[i];
      if (node->costfromsource < pnode->costfromsource) {
        this->pqueue.emplace(this->pqueue.begin() + i, node);
        return;
      }
      i++;
    }
    this->pqueue.emplace_back(node);
  }
};

int main() {
  size_t maxvertices = 9;
  size_t source = 0;
  Dijkstra dijkstra;
  dijkstra.buildAdj(edgesandcost, maxvertices, source);
  dijkstra.explore();
  dijkstra.printNodeInfo();
}