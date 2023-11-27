#pragma once

#include <fstream>
#include <string>

class CSVReader {
 public:
  CSVReader();
  ~CSVReader();

  static std::ifstream open_csv(const std::string &filename);
};
