#include "game_printer.hpp"
#include <string>
#include "game.hpp"
#include "graph.hpp"
#include "graph_printer.hpp"

namespace uni_course_cpp {

std::string GamePrinter::printGame() const {
  return "{\n" + printMap() + printLocations() + "}\n";
}

std::string GamePrinter::printMap() const {
  const Graph graph = game_.map();
  std::string string = "  map: {\n";
  string += "   depth: " + std::to_string(game_.map().depth()) + ",\n";
  string +=
      "   vertices: " + std::to_string(game_.map().vertexes().size()) + ", [";
  for (int j = 0; j <= game_.map().depth(); j++) {
    string += std::to_string(game_.map().vertexIdsAtLayer(j).size()) + ", ";
  }
  string.pop_back();
  string.pop_back();
  string += "],\n";
  string += "   edges: " + std::to_string(game_.map().edges().size()) + ", {";
  for (const auto& color : uni_course_cpp::Edge::ALL_COLORS) {
    string += uni_course_cpp::GraphPrinter::colorToString(color) + ": ";
    string += std::to_string(game_.map().colorEdges(color).size()) + ", ";
  }
  string.pop_back();
  string.pop_back();
  string += "},\n  },\n";
  return string;
}

std::string GamePrinter::printLocations() const {
  std::string string = "  knight position: {vertex id: " +
                       std::to_string(game_.knight_position());
  string += ", depth: " +
            std::to_string(game_.map().vertexDepth(game_.knight_position())) +
            "},\n";
  string += "  princess position: {vertex id: " +
            std::to_string(game_.princess_position());
  string += ", depth: " +
            std::to_string(game_.map().vertexDepth(game_.princess_position())) +
            "},\n";
  return string;
}

}  // namespace uni_course_cpp
