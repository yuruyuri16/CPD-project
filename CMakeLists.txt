cmake_minimum_required(VERSION 3.26.4)
project(cpd_project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

set(OpenMP_CXX "${CMAKE_CXX_COMPILER}")
set(OpenMP_CXX_FLAGS "-Xclang -fopenmp -I/opt/homebrew/opt/libomp/include")
set(OpenMP_CXX_LIB_NAMES "libomp")
set(OpenMP_libomp_LIBRARY "omp")

link_directories("/opt/homebrew/opt/libomp/lib")

add_executable(cpd_project
        main.cpp
        TSPSolver.hpp
        TSPSolver.cpp
        CSVReader.cpp
        CSVReader.hpp)

find_package(OpenMP REQUIRED)
if (OpenMP_CXX_FOUND)
    message("OpenMP found")
    target_link_libraries(cpd_project PUBLIC OpenMP::OpenMP_CXX)
endif ()