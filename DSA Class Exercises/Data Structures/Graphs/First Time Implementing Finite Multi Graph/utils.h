#pragma once
#include <iostream>
#include "Node.h"
#include "FiniteMultiGraph.h"
#include "../../../Algorithms/Graph Traversal Algorithms/breadthfirstsearch.h"
#include "../../../Algorithms/Graph Traversal Algorithms/depthfirstsearch.h"

std::ostream& operator<< (std::ostream& COUT, const Node* node) {
	if (node == nullptr) { COUT << "Node is null" << std::endl; }
	else { COUT << node->label; }
	return COUT;
}