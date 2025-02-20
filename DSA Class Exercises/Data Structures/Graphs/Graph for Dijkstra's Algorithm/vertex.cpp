#include "vertex.h"

#include <limits>

Vertex::Vertex(unsigned int key) {
  this->label = key;
  this->visited = false;
  this->cost_from_source = std::numeric_limits<unsigned int>::max();
}
