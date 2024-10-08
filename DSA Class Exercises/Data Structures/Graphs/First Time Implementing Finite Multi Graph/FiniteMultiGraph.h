#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <queue>
#include <stack>
#include "Node.h"

class FiniteMultiGraph {
public:
	FiniteMultiGraph();
	void buildGraph(std::vector<std::pair<size_t, size_t>>* edgelist);
	void operator=(std::vector<std::pair<size_t, size_t>>* edgelist) { this->buildGraph(edgelist); }
	friend void BFS(const FiniteMultiGraph&);
	friend void DFS(const FiniteMultiGraph&);
	friend void search(const std::vector<Node*>*, std::unordered_map<size_t, const Node*>&, std::stack<const Node*>&);

private:
	// maybe replace site_t with pointers to nodes to denote edges
	// : std::vector<std::pair<Node*, Node*>> edges
	std::vector<std::pair<size_t, size_t>>* edges;
	std::vector<Node*>* graph;
};
