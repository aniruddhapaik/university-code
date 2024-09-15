#include "FiniteMultiGraph.h"
#include "utils.h"

int main() {
	FiniteMultigraph graph;

	graph = new std::vector<std::pair<size_t, size_t>> 
	{
		{1,4},{1,2},{4,3},{3,10},{3,9},{2,3},{2,5},
		{2,7},{2,8},{5,6},{5,7},{5,8},{7,8}
	};

	BFS(graph);

	return 0;
}