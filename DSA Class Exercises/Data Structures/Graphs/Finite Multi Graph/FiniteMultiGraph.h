#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <queue>
#include "Node.h"

class FiniteMultigraph {
public:
	FiniteMultigraph();
	void buildGraph(std::vector<std::pair<size_t, size_t>>* edgelist);
	void operator=(std::vector<std::pair<size_t, size_t>>* edgelist) { this->buildGraph(edgelist); }
	friend void BFS(const FiniteMultigraph&);
	friend void DFS(const FiniteMultigraph&);

private:
	std::vector<std::pair<size_t, size_t>>* edges;
	std::vector<Node*>* graph;
};
