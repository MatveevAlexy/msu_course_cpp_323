#pragma once

#include "graph.hpp"
#include "graph_path.hpp"

namespace uni_course_cpp {
class Game {
 public:
  GraphPath findShortestPath() const;
  GraphPath findFastestPath() const;
  Game(Graph map, VertexId knight_position, VertexId princess_position)
      : map_(map),
        knight_position_(knight_position),
        princess_position_(princess_position) {}
  const Graph& map() const { return map_; }
  const VertexId& knight_position() const { return knight_position_; }
  const VertexId& princess_position() const { return princess_position_; }

 private:
  const Graph map_;
  const VertexId knight_position_;
  const VertexId princess_position_;
};
}  // namespace uni_course_cpp
