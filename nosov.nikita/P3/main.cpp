#include <iostream>
#include <fstream>

namespace nosov {
  bool readMatrix(std::istream& in, int* matrix, size_t rows, size_t cols)
  {
    for (size_t i = 0; i < rows * cols; ++i) {
      in >> matrix[i];
      if (!in) {
        return false;
      }
    }
    return true;
  }

  int processMatrix(std::istream& in, int* matrix, size_t rows, size_t cols)
  {
    if (!readMatrix(in, matrix, rows, cols)) {
      std::cerr << "Can not read matrix\n";
      return 2;
    }
    return 0;
  }
}

int main(int argc, char** argv)
{
  const int argumentsCount = 4;
  if (argc < argumentsCount) {
    std::cerr << "Not enough arguments\n";
    return 1;
  }
  if (argc > argumentsCount) {
    std::cerr << "Too many arguments\n";
    return 1;
  }

  const char* num = argv[1];
  const bool isFixed = (num[0] == '1' && num[1] == '\0');
  const bool isDynamic = (num[0] == '2' && num[1] == '\0');
  if (!isFixed && !isDynamic) {
    std::cerr << "First parameter is wrong\n";
    return 1;
  }

  std::ifstream in(argv[2]);
  if (!in) {
    std::cerr << "Can not open input file\n";
    return 2;
  }
  size_t rows = 0;
  size_t cols = 0;
  in >> rows >> cols;
  if (!in) {
    std::cerr << "Can not read matrix size\n";
    return 2;
  }

  if (isFixed) {
    const size_t maxSize = 10000;
    if (rows * cols > maxSize) {
      std::cerr << "Matrix is too big\n";
      return 2;
    }
    int matrix[maxSize] = {};
    return nosov::processMatrix(in, matrix, rows, cols);
  }
  return 0;
}
