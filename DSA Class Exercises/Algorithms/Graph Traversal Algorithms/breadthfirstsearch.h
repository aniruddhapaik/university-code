#pragma once
// please refer to Data Structures folder Finite Multi Graph implementation
#include <iostream>

void BFS(const FiniteMultigraph& graph) {
	std::queue<const Node*> queue;
	std::unordered_map<size_t, const Node*> visited_map;
	std::queue<size_t> visited_queue;

	size_t numofnodes{};
	while (numofnodes >= 0 and numofnodes < graph.graph->size()) {
		if (graph.graph->at(numofnodes) != nullptr) { queue.push(graph.graph->at(numofnodes)); break; }
		numofnodes++;
	}

	while (queue.size()) {
		//std::cout << queue.front();
		auto insertsuccess = visited_map.emplace(queue.front()->label, queue.front());
		if (insertsuccess.second == false) {
			queue.pop();
			continue;
		} else { visited_queue.push(queue.front()->label); }
		
		// push into queue elements that are neighbor of last node visited_map
		size_t numoflinks{};
		while (numoflinks >= 0 and numoflinks < queue.front()->linkstonode->size()) {
			auto nodelabel = queue.front()->linkstonode->at(numoflinks);
			if (visited_map.find(nodelabel) == visited_map.end()) { queue.push(graph.graph->at(nodelabel)); }
			//else { std::cout << "Already been visited_map: " << nodelabel << std::endl; }
			numoflinks++;
		}
		queue.pop();
	}
	
	while (visited_queue.size()) {
		std::cout << visited_queue.front() << " | ";
		visited_queue.pop();
	}
	std::cout << std::endl;
}