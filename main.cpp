#include <cstdlib>
#include <iostream>
#include <chrono>
#include <omp.h>

#include "CSVReader.hpp"
#include "TSPSolver.hpp"

int main() {
  try {
    std::ifstream file = CSVReader::open_csv("../test3.csv");
    auto nodes = TSPSolver::parse_file(file);
    auto graph = TSPSolver::convert_to_graph(nodes);

//    const auto start = std::chrono::steady_clock::now();
//    const auto w = TSPSolver::solve_with_graph(graph);
//    const auto end = std::chrono::steady_clock::now();
//
//    const std::chrono::duration<double> elapsed_seconds = end - start;
//
//    std::cout << elapsed_seconds.count() << '\n';
//    std::cout << "Minimum: " << w << std::endl;

    const auto start1 = std::chrono::steady_clock::now();
    const auto w1 = TSPSolver::solve_with_graph_bb(graph);
    const auto end1 = std::chrono::steady_clock::now();

    const std::chrono::duration<double> elapsed_seconds1 = end1 - start1;

    std::cout << elapsed_seconds1.count() << '\n';

    std::cout << "Minimum: " << w1 << std::endl;
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    std::exit(EXIT_FAILURE);
  }
  return 0;
}
