#include "../../input_utils.h"
#include <vector>
#include <utility>
#include <queue>

struct Node {
	size_t label;
	std::vector<size_t>* linkstonode;

	Node (size_t val) { 
		this->label = val;
		this->linkstonode = new std::vector<size_t>; 
	}
};

class FiniteMultigraph {
private:
	std::vector<std::pair<size_t, size_t>>* edges;
	std::vector<Node*>* graph;

public:
	FiniteMultigraph() {
		this->edges = new std::vector<std::pair<size_t, size_t>>;
		this->graph = new std::vector<Node*>;
	}
	
	void buildGraph(std::vector<std::pair<size_t, size_t>>* edgelist) {
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

	void operator=(std::vector<std::pair<size_t, size_t>>* edgelist) { this->buildGraph(edgelist); }

	friend void BFS(FiniteMultigraph);
	friend void DFS(FiniteMultigraph);
};

inline std::ostream& operator<< (std::ostream& COUT, const Node* node) {
	COUT << node->label;
	return COUT;
}

void BFS(FiniteMultigraph graph) {
	std::queue<Node*> queue;
	std::vector<Node*> visited;

	queue.push(graph.graph->at(0));
	while (queue.size()) {
		std::cout << queue.front();
		visited.push_back(queue.front());
		// push into queue elements that are neighbor of last node visited
	}
}

void DFS(FiniteMultigraph graph) {
	
}