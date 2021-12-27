#include "game.hpp"
#include "graph.hpp"
#include "graph_traverser.hpp"

namespace uni_course_cpp {
GraphPath Game::findShortestPath() const {
  GraphTraverser graph_traverser(map_);
  return graph_traverser.findShortestPath(knight_position_, princess_position_);
}

GraphPath Game::findFastestPath() const {
  GraphTraverser graph_traverser(map_);
  return graph_traverser.findFastestPath(knight_position_, princess_position_);
}
}  // namespace uni_course_cpp
