#pragma once
#include <cstdint>
#include <utility>

enum class Direction : uint8_t { undirected = 0, directed = 1 };

using directededge = std::pair<unsigned int, unsigned int>;
using edgecost = std::pair<directededge, unsigned int>;