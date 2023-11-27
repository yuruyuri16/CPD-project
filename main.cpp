#include <cstdlib>
#include <iostream>
#include <chrono>
#include <omp.h>

#include "CSVReader.hpp"
#include "TSPSolver.hpp"

int main() {
  omp_set_num_threads(8);
  try {
    std::ifstream file = CSVReader::open_csv("../test5.csv");
    auto nodes = TSPSolver::parse_file(file);
    auto graph = TSPSolver::convert_to_graph(nodes);

    const auto start1 = std::chrono::steady_clock::now();
    const auto w = TSPSolver::solve_with_graph_p(graph);
    const auto end1 = std::chrono::steady_clock::now();

    const std::chrono::duration<double> elapsed_seconds1 = end1 - start1;

    std::cout << "Time (seconds): " << elapsed_seconds1.count() << '\n';

    std::cout << "Minimum: " << w << std::endl;
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    std::exit(EXIT_FAILURE);
  }
  return 0;
}
