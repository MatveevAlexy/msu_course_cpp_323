#pragma once

#include "game.hpp"
#include "graph_generator.hpp"

namespace uni_course_cpp {
class GameGenerator {
 public:
  GameGenerator(const GraphGenerator::Params& params) : params_(params) {}
  Game generateGame() const;

 private:
  const GraphGenerator::Params& params_;
};
}  // namespace uni_course_cpp
