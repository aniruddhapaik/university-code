#include "Node.h"

Node::Node (size_t& val) {
	this->label = val;
	this->linkstonode = new std::vector<size_t>;
}