#include "FiniteMultiGraph.h"

FiniteMultiGraph::FiniteMultiGraph() {
	this->edges = nullptr;
	this->graph = new std::vector<Node*>;
}

void FiniteMultiGraph::buildGraph(std::vector<std::pair<size_t, size_t>>* edgelist) {
	this->edges = edgelist;
	auto number_of_edges = edgelist->size();
		
	for (size_t i{}; i < number_of_edges; i++) {
		auto first = edgelist->at(i).first;
		auto second = edgelist->at(i).second;
		auto res = std::max(first, second);
			
		if (this->graph->size() < ++res) { this->graph->resize(res, nullptr); }

		if (this->graph->at(first) == nullptr) { this->graph->at(first) = new Node(first); }
		this->graph->at(first)->linkstonode->push_back(second);

		if (this->graph->at(second) == nullptr) { this->graph->at(second) = new Node(second); }
		this->graph->at(second)->linkstonode->push_back(first);
	}
}