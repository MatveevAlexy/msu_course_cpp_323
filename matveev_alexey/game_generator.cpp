#include "game_generator.hpp"
#include <random>
#include "graph.hpp"
#include "graph_generator.hpp"

namespace {
int randomValue(int max) {
  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_int_distribution distribution(0, max);
  return distribution(rng);
}
}  // namespace

namespace uni_course_cpp {
Game GameGenerator::generateGame() const {
  GraphGenerator graph_generator = GraphGenerator(params_);
  const auto map = graph_generator.generate();
  const auto knight_position = map.vertexIdsAtLayer(0).at(
      randomValue(map.vertexIdsAtLayer(0).size() - 1));
  const auto princess_position =
      map.vertexIdsAtLayer(map.depth())
          .at(randomValue(map.vertexIdsAtLayer(map.depth()).size() - 1));
  return Game(map, knight_position, princess_position);
}
}  // namespace uni_course_cpp
