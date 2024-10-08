#include "Vertex.h"

Vertex::Vertex() {
  this->key = 0;
  this->visited = false;
}

Vertex::Vertex(int keyval) {
  this->key = keyval;
  this->visited = false;
}