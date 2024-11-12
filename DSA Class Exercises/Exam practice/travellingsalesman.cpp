/*
  - you are given edges list
  - you are given max nodes
  - you are given source

  - build an unordered_set of node ids to pass as argument to show remaining cities that can be chosen 
  - build adjacency matrix based on edges list
  - build patch tracking vector;

  - function findpath (arguments: city c, set of cities available setc, path tracking index pi):
    - if set size is > 0:
      - make mincost = max limit of integer;
      - make possiblechoice of city = c;
      - for (every node j in setc) 
        - create newsetc 
        - remove j from newsetc
        - bestcost returned = findpath(j, newsetc, pi)
        - if (bestcost < mincost) 
          - mincost = bestcost;
          - possiblechoice of city c = j;

      path[pi] = possiblechoice of city c;
      return (mincost + cost of city c to possible choice of city c)
*/

#include <iostream>
#include <vector>
#include <unordered_set>
#include <limits>

std::vector<std::vector<int>> adjmatrix = {
    {0, 16, 11, 6}, 
    {8, 0, 13, 16}, 
    {4, 7, 0, 9}, 
    {5, 12, 2, 0}};

class TravellingSalesman {
private:
  size_t source;
  std::vector<size_t> path;

  int findPath(size_t c, std::unordered_set<size_t> cities, size_t pathindex) {
    if (cities.size()) {
      int mincost = std::numeric_limits<int>::max();
      size_t possiblechoiceofcity = c;

      for (auto& nextcity: cities) {
        std::unordered_set<size_t> newsetofcities = cities;
        newsetofcities.erase(nextcity);
        int cost = this->findPath(nextcity, newsetofcities, pathindex-1);

        if (cost < mincost) {
          mincost = cost;
          possiblechoiceofcity = nextcity;
        }
      }

      this->path[pathindex] = possiblechoiceofcity;
      return (mincost + adjmatrix[c][possiblechoiceofcity]);
    } else {
      return (adjmatrix[c][this->source]);
    }
  }

  const void printPath() const {
    std::cout << "Best path: \n";
    for (auto& city: this->path) {
      std::cout << city << " <-- ";
    }
    std::cout << this->source << std::endl;
  }

public:
  TravellingSalesman(size_t src) {
    this->source = src;
    this->path.resize(adjmatrix.size());

    std::unordered_set<size_t> cities;
    cities.reserve(adjmatrix.size());
    for(size_t i = 0; i < adjmatrix.size(); i++) {
      cities.emplace(i);
    }
    cities.erase(this->source);

    this->findPath(this->source, cities, adjmatrix.size()-1);
    this->printPath();
  }
};

int main() {
  TravellingSalesman* man = new TravellingSalesman(0);
  return 0;
}