#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include "config.hpp"
#include "game.hpp"
#include "game_generator.hpp"
#include "game_printer.hpp"
#include "graph.hpp"
#include "graph_generation_controller.hpp"
#include "graph_generator.hpp"
#include "graph_path.hpp"
#include "graph_printer.hpp"
#include "graph_traversal_controller.hpp"
#include "graph_traverser.hpp"
#include "logger.hpp"

namespace {
int handle_depth_input() {
  int depth;
  std::cout << "Enter depth:" << std::endl;
  std::cin >> depth;
  while (depth < 0) {
    std::cout << "Depth must be not negative. Enter depth again:" << std::endl;
    std::cin >> depth;
  }
  return depth;
}

int handle_new_vertexes_num_input() {
  int new_vertexes_num;
  std::cout << "Enter number of new vertices:" << std::endl;
  std::cin >> new_vertexes_num;
  while (new_vertexes_num < 0) {
    std::cout << "Number of new vertices must be not negative. Enter number of "
                 "new vertexes again:"
              << std::endl;
    std::cin >> new_vertexes_num;
  }
  return new_vertexes_num;
}

int handleNewGraphsCountInput() {
  int new_graphs_num;
  std::cout << "Enter number of new graphs:" << std::endl;
  std::cin >> new_graphs_num;
  while (new_graphs_num < 0) {
    std::cout << "Number of new graphs must be not negative. Enter number of "
                 "new hraphs again:"
              << std::endl;
    std::cin >> new_graphs_num;
  }
  return new_graphs_num;
}

int handleThreadsNum() {
  int threads_num;
  std::cout << "Enter number of threads:" << std::endl;
  std::cin >> threads_num;
  while (threads_num < 1) {
    std::cout << "Number of threads must be positive" << std::endl;
    std::cin >> threads_num;
  }
  return threads_num;
}

void writeToFile(const std::string& string, const std::string& file_name) {
  std::ofstream file(file_name);
  file << string;
  file.close();
}

std::string genStartedString(int i) {
  return "Graph " + std::to_string(i) + ", Generation Started\n";
}

std::string genFinishedString(int i, const uni_course_cpp::Graph& graph) {
  std::string string =
      "Graph " + std::to_string(i) + ", Generation Finished {\n";
  int depth = graph.depth();
  string += " depth: " + std::to_string(depth) + ",\n";
  string += " vertices: " + std::to_string(graph.vertexes().size()) + ", [";
  for (int j = 0; j <= depth; j++) {
    string += std::to_string(graph.vertexIdsAtLayer(j).size()) + ", ";
  }
  string.pop_back();
  string.pop_back();
  string += "],\n";
  string += " edges: " + std::to_string(graph.edges().size()) + ", {";
  for (const auto& color : uni_course_cpp::Edge::ALL_COLORS) {
    string += uni_course_cpp::GraphPrinter::colorToString(color) + ": ";
    string += std::to_string(graph.colorEdges(color).size()) + ", ";
  }
  string.pop_back();
  string.pop_back();
  string += "},\n}\n";
  return string;
}

std::string gameStartedString() {
  return "Game is Preparing\n";
}

std::string gameFinishedString(uni_course_cpp::Game game) {
  uni_course_cpp::GamePrinter game_printer(game);
  return "Game is Ready {\n" + game_printer.printGame() + "}\n";
}

std::string traversalStartedString(int index, std::string fast_or_short) {
  std::string string =
      "Graph" + std::to_string(index) + ", Traversal Started\n";
  string += "  Searching for " + fast_or_short + "path\n";
  return string;
}

std::string traversalFinishedString(int index,
                                    const uni_course_cpp::GraphPath& path,
                                    std::string fast_or_short) {
  std::string string = "Graph " + std::to_string(index) + ", Traversal Ended, ";
  string += fast_or_short + " path: {\n";
  string += "  vertexes: [";
  for (const auto& vertex_id : path.vertex_ids) {
    string += std::to_string(vertex_id) + ", ";
  }
  string.pop_back();
  string.pop_back();
  string += "], distance: " + std::to_string(path.distance()) + ", ";
  string += "duration: " + std::to_string(path.duration) + ",\n";
  string += "}\n";
  return string;
}

void prepareTempDirectory() {
  std::filesystem::create_directory(
      uni_course_cpp::config::TEMP_DIRECTORY_PATH);
}

}  // namespace

int main() {
  const int depth = handle_depth_input();
  const int new_vertexes_num = handle_new_vertexes_num_input();
  prepareTempDirectory();

  const auto params =
      uni_course_cpp::GraphGenerator::Params(depth, new_vertexes_num);
  auto& logger = uni_course_cpp::Logger::getLogger();
  logger.log(gameStartedString());
  const auto game_generator = uni_course_cpp::GameGenerator(params);
  const auto game = game_generator.generateGame();
  logger.log(gameFinishedString(game));

  logger.log(traversalStartedString(0, "Shortest"));
  const auto shortest_path = game.findShortestPath();
  logger.log(traversalFinishedString(0, shortest_path, "Shortest"));

  logger.log(traversalStartedString(0, "Fastest"));
  const auto fastest_path = game.findFastestPath();
  logger.log(traversalFinishedString(0, fastest_path, "Fastest"));

  const auto graph_printer = uni_course_cpp::GraphPrinter(game.map());
  const auto map = graph_printer.print();
  writeToFile(map, uni_course_cpp::config::TEMP_DIRECTORY_PATH + "map.json");
  return 0;
}
