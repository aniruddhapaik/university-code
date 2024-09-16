#pragma once
// please refer to Data Structures folder Finite Multi Graph implementation
#include <iostream>
#include <stack>

void search(const std::vector<Node*>* graph, std::unordered_map<size_t, const Node*>& visited, std::stack<const Node*>& stack) {
	size_t numoflinks{};
	const Node* top = stack.top();
	
	while(numoflinks < top->linkstonode->size()) {
		size_t link = top->linkstonode->at(numoflinks);
		if (visited.find(link) == visited.end()) {
			visited.emplace(link, graph->at(link));
			std::cout << link << " | ";
			if (graph->at(link)->linkstonode->size()) {
				stack.push(graph->at(link));
				search(graph, visited, stack);
			}
		}
		numoflinks++;
	}
}

void DFS(const FiniteMultiGraph& graph) {
	const std::vector<Node*>* graphnodes = graph.graph;
	std::stack<const Node*> stack;
	std::unordered_map<size_t, const Node*> visited_map;

	size_t numofnodes{};
	while (numofnodes >= 0 and numofnodes < graph.graph->size()) {
		if (graph.graph->at(numofnodes) != nullptr) { 
			visited_map.emplace(numofnodes, graph.graph->at(numofnodes));
			std::cout << numofnodes << " | ";
			if (graph.graph->at(numofnodes)->linkstonode->size()) {
				// since the node has edges connected, we push that node
				//   onto the stack for further exploration
				stack.push(graph.graph->at(numofnodes));
			}
			break; 
		}
		numofnodes++;
	}
	
	search(graphnodes, visited_map, stack);
}