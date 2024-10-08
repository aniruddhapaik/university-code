#pragma once
#include <vector>

class Node {
public:
	size_t label;
	std::vector<size_t>* linkstonode;

	// Add visited variable(bool)
	// : bool visited;

	// cost from starting node data structure
	// : std::pair<Node*, cost>;

	Node(size_t& val);
};