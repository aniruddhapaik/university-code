#include <limits>
#include <vector>

#include "../../Data Structures/Graphs/Graph for Dijkstra's Algorithm/simplegraph.h"
#include "../../Data Structures/Graphs/Graph for Dijkstra's Algorithm/vertex.h"

void Explore(SimpleGraph& graph) {
  // The vertex we are currently visiting to explore vertices connected to it.
  Vertex* current_node =
      graph.allnodes.find(graph.current_visiting_node)->second;
  if (current_node->visited == false) {
    current_node->visited = true;
    Relax(graph, current_node);
    Explore(graph);
  }
}

void Relax(SimpleGraph& graph, Vertex* vertex) {
  unsigned int choose_next_node_to_visit{vertex->label};
  unsigned int mincost{std::numeric_limits<unsigned int>::max()};
  for (auto& pair :
       vertex->linksandcost) {  // Exploring all connected neighbor vertices
    Vertex* exploring_vertex = graph.allnodes.find(pair.first)->second;
    if (exploring_vertex->visited ==
        false) {  // Exploring vertex only if it has not been visited
      if ((vertex->cost_from_source + pair.second) <
          exploring_vertex->cost_from_source) {
        // If a better cost effective path is found
        exploring_vertex->cost_from_source =
            vertex->cost_from_source + pair.second;
        exploring_vertex->path_from_source.clear();

        exploring_vertex->path_from_source.insert(
            exploring_vertex->path_from_source.begin(),
            vertex->path_from_source.begin(), vertex->path_from_source.end());
        exploring_vertex->path_from_source.emplace_back(
            exploring_vertex->label);
      }

      // Selecting the path with the least cost
      //   after the all neighbor vertices have been visited
      if (exploring_vertex->cost_from_source < mincost) {
        mincost = exploring_vertex->cost_from_source;
        choose_next_node_to_visit = exploring_vertex->label;
      }
    }
  }
  if (graph.allnodes.find(choose_next_node_to_visit)->second->visited ==
      false) {
    graph.current_visiting_node = choose_next_node_to_visit;
  }
}
