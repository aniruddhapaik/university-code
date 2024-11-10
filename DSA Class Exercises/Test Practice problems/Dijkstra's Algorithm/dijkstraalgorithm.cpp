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
  int key;
  int costfromsource;
  std::vector<size_t> pathfromsource;

  Node(int k) {
    this->key = k;
    this->costfromsource = std::numeric_limits<int>::max();
  }
};

class Dijkstra {
 public:
  void buildAdj(std::vector<std::vector<int>>& edgesandcost, size_t maxv,
                size_t src) {
    this->maxvertices = maxv;
    this->source = src;

    this->adjmatrix.resize(this->maxvertices);  // resizing the adj matrix
    for (auto& row : this->adjmatrix) {         //  for storage
      row.resize(this->maxvertices);
    }

    for (auto& edge : edgesandcost) {  // updating edge costs in adj matrix
      this->adjmatrix[edge[0]][edge[1]] = edge[2];
      this->adjmatrix[edge[1]][edge[0]] = edge[2];
    }
  }

  void explore() {
    Node* node = new Node(this->source);
    node->costfromsource = 0;
    this->pqueue.emplace_back(node);

    while (this->pqueue.size()) {
      node = this->pqueue[0];  // first node in priority queue
      this->visitednodes.emplace(node->key, node);  // marking the node visited
      this->pqueue.erase(this->pqueue.begin());     // removing it from pqueue

      for (size_t col = 0; col < this->maxvertices; col++) {
        int cost = this->adjmatrix[node->key][col];
        if (cost != 0) {
          if (this->visitednodes.find(col) == this->visitednodes.end()) {
            Node* newnode = new Node(col);
            newnode->costfromsource = node->costfromsource + cost;  // relax
            newnode->pathfromsource = node->pathfromsource;  // update path
            newnode->pathfromsource.emplace_back(node->key);
            this->addToPQueue(newnode); // adding new node to pqueue
          } else {
            Node* oldnode = this->visitednodes.find(col)->second;
            if (node->costfromsource + cost < oldnode->costfromsource) {
              oldnode->costfromsource = node->costfromsource + cost;  // relax
              oldnode->pathfromsource = node->pathfromsource;  // update path
              oldnode->pathfromsource.emplace_back(node->key);

              for (size_t j = 0; j < this->pqueue.size(); j++) {
                Node* old = this->pqueue[j];
                if (old->key == oldnode->key) {
                  this->pqueue.erase(this->pqueue.begin() + j);
                  break;
                }
              } // updating old node's position in pqueue:
              this->addToPQueue(oldnode);
            }
          }
        }
      }
    }
  }

  const void printNodeInfo() const {
    for (auto& node : this->visitednodes) {
      std::cout << this->source << " to ";
      std::cout << node.second->key << " Cost=" << node.second->costfromsource;
      for (auto& v : node.second->pathfromsource) {
        std::cout << ' ' << v << " -->";
      }
      std::cout << ' ' << node.first << std::endl;
    }
  }

 private:
  void addToPQueue(Node* vertex) {
    size_t i = 0;
    while (i < this->pqueue.size()) {
      if (vertex->costfromsource < this->pqueue[i]->costfromsource) {
        this->pqueue.emplace(this->pqueue.begin() + i, vertex);
        return;
      }
      i++;
    }
    this->pqueue.emplace_back(vertex);
  }

 private:
  std::vector<std::vector<int>> adjmatrix;
  size_t maxvertices = 0;
  size_t source = 0;
  std::vector<Node*> pqueue;
  std::unordered_map<size_t, Node*> visitednodes;
};

int main() {
  size_t maxvertices = 9;
  size_t source = 0;

  Dijkstra dijkstra;
  dijkstra.buildAdj(edgesandcost, maxvertices, source);
  dijkstra.explore();
  dijkstra.printNodeInfo();

  return 0;
}

// Extra Test Graphs
//std::vector<std::vector<int>> edgeinfo1 = {{0, 1, 2}, {0, 2, 4}, {1, 2, 1},
//                                           {1, 3, 7}, {2, 4, 3}, {3, 5, 1},
//                                           {4, 3, 2}, {4, 5, 5}};
//
//std::vector<std::vector<int>> edgeinfo2 = {{0, 1, 7},  {0, 2, 9},  {0, 5, 14},
//                                           {1, 2, 10}, {1, 3, 15}, {2, 3, 11},
//                                           {2, 5, 2},  {3, 4, 6},  {4, 5, 9}};