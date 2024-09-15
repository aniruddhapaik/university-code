#pragma once
#include <vector>

class Node {
public:
	size_t label;
	std::vector<size_t>* linkstonode;

	Node(size_t& val);
};