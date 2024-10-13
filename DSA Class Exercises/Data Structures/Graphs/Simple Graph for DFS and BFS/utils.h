#pragma once

#include <utility>

using edgelink = std::pair<unsigned, unsigned>;
using edgelinkcost = std::pair<edgelink, int>;
using edgelinkexist = std::pair<edgelink, bool>;
using edgevisit = std::pair<std::pair<unsigned, unsigned>, bool>;