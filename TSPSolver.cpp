#include "TSPSolver.hpp"

TSPSolver::TSPSolver() = default;

TSPSolver::~TSPSolver() = default;

TSPSolver::Nodes TSPSolver::parse_file(std::ifstream &file) {
  Nodes res;
  int index;
  double x, y;
  while (file >> index >> x >> y) res.emplace_back(x, y);
  return res;
}

TSPSolver::Graph TSPSolver::convert_to_graph(TSPSolver::Nodes nodes) {
  auto n = nodes.size();
  Graph graph(n, std::vector<double>(n));
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < i + 1; ++j)
      if (i not_eq j) {
        graph[i][j] = euclidean_distance(nodes[i], nodes[j]);
        graph[j][i] = euclidean_distance(nodes[i], nodes[j]);
      } else
        graph[i][j] = INF;
  return graph;
}

double TSPSolver::euclidean_distance(Node node1, Node node2) {
  return std::sqrt(std::pow(node1.first - node2.first, 2) +
      std::pow(node1.second - node2.second, 2));
}

double TSPSolver::solve_with_graph_p(const Graph &graph) {
  auto n = graph.size();
  auto visited = std::vector(n, false);
  visited[0] = true;
  auto best_cost = INF;
  return solve_with_graph_p(graph, 0, visited, 1, n, 0.0, best_cost);
}

double TSPSolver::solve_with_graph_p(const Graph &graph, int current,
                                     std::vector<bool> &visited, size_t count,
                                     size_t n, double cost, double &best_cost) {

  if (cost > best_cost)
    return INF;

  if (count == n) {

    auto res = cost + graph[current][0];
#pragma omp critical
    best_cost = std::min(best_cost, res);

    return res;
  }

  auto min_cost = INF;
#pragma omp parallel for reduction(min:min_cost) firstprivate(visited)
  for (int i = 0; i < n; ++i)
    if (not visited[i]) {
      visited[i] = true;
      auto new_cost = solve_with_graph_bb(graph, i, visited, count + 1, n, cost + graph[current][i], best_cost);
      min_cost = std::min(min_cost, new_cost);
      visited[i] = false;
    }

  return min_cost;
}

double TSPSolver::solve_with_graph_bb(const TSPSolver::Graph &graph) {
  auto n = graph.size();
  auto visited = std::vector(n, false);
  visited[0] = true;
  auto best_cost = INF;
  return solve_with_graph_bb(graph, 0, visited, 1, n, 0.0, best_cost);
}

double TSPSolver::solve_with_graph_bb(const TSPSolver::Graph &graph,
                                      int current,
                                      std::vector<bool> &visited,
                                      size_t count,
                                      size_t n,
                                      double cost,
                                      double &best_cost) {
  if (cost > best_cost)
    return INF;

  if (count == n) {
    auto res = cost + graph[current][0];
    best_cost = std::min(best_cost, res);
    return res;
  }

  auto min_cost = INF;

  for (int i = 0; i < n; ++i)
    if (not visited[i]) {
      visited[i] = true;
      auto new_cost = solve_with_graph_bb(graph, i, visited, count + 1, n, cost + graph[current][i], best_cost);
      min_cost = std::min(min_cost, new_cost);
      visited[i] = false;
    }

  return min_cost;
}
