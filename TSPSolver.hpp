#pragma once

#include <cmath>
#include <fstream>
#include <limits>
#include <string>
#include <utility>
#include <vector>

class TSPSolver {
 public:
  TSPSolver();
  ~TSPSolver();

 private:
  constexpr static auto INF = std::numeric_limits<double>::infinity();

 public:
  using Node = std::pair<double, double>;
  using Nodes = std::vector<Node>;
  using Graph = std::vector<std::vector<double>>;

  static Nodes parse_file(std::ifstream &file);
  static Graph convert_to_graph(Nodes nodes);

  static double solve_with_graph(const Graph &graph);
  static double solve_with_graph_bb(const Graph &graph);

 private:
  static double solve_with_graph(const Graph &graph, int current,
                                 std::vector<bool> &visited, size_t count,
                                 size_t n, double cost);
  static double solve_with_graph_bb(const Graph &graph, int current,
                                    std::vector<bool> &visited, size_t count,
                                    size_t n, double cost, double &best_cost);
  inline static double euclidean_distance(Node node1, Node node2);
};
