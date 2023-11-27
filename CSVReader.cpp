#include "CSVReader.hpp"

CSVReader::CSVReader() = default;

CSVReader::~CSVReader() = default;

std::ifstream CSVReader::open_csv(const std::string &filename) {
  std::ifstream file(filename);
  if (file.fail()) {
    throw std::runtime_error("Could not open " + filename + ".");
  }
  return file;
}
