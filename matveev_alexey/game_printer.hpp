#pragma once

#include <string>
#include "game.hpp"
#include "graph.hpp"

namespace uni_course_cpp {

class GamePrinter {
 public:
  GamePrinter(const Game& game) : game_(game) {}

  std::string printGame() const;
  std::string printMap() const;
  std::string printLocations() const;

 private:
  const Game& game_;
};
}  // namespace uni_course_cpp
