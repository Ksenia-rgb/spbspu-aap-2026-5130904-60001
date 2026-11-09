#include <cstddef>
#include <fstream>
#include <iostream>
#include <new>

namespace nosov {
  std::istream& readMatrix(std::istream& in, int* matrix, std::size_t size)
  {
    for (std::size_t i = 0; i < size; ++i) {
      in >> matrix[i];
    }
    return in;
  }

  std::ostream& writeMatrix(std::ostream& out, const int* matrix, std::size_t rows, std::size_t cols)
  {
    out << rows << " " << cols;
    for (std::size_t i = 0; i < rows * cols; ++i) {
      out << " " << matrix[i];
    }
    return out;
  }

  std::size_t findSeriesColumn(const int* matrix, std::size_t rows, std::size_t cols)
  {
    if (rows == 0 || cols == 0) {
      return 0;
    }
    std::size_t best_column = 0;
    std::size_t best_length = 1;
    for (std::size_t j = 0; j < cols; ++j) {
      std::size_t length = 1;
      for (std::size_t i = 1; i < rows; ++i) {
        if (matrix[i * cols + j] == matrix[(i - 1) * cols + j]) {
          ++length;
        } else {
          length = 1;
        }
        if (length > best_length) {
          best_length = length;
          best_column = j;
        }
      }
    }
    return best_column + 1;
  }
}

int main(int argc, char** argv)
{
  if (argc < 4) {
    std::cerr << "Not enough arguments\n";
    return 1;
  }
  if (argc > 4) {
    std::cerr << "Too many arguments\n";
    return 1;
  }

  const char* const num = argv[1];
  if ((num[0] != '1' && num[0] != '2') || num[1] != '\0') {
    std::cerr << "First parameter is wrong\n";
    return 1;
  }

  std::ifstream in(argv[2]);
  if (!in) {
    std::cerr << "Can not open input file\n";
    return 2;
  }
  std::size_t rows = 0;
  std::size_t cols = 0;
  if (!(in >> rows >> cols)) {
    std::cerr << "Can not read matrix size\n";
    return 2;
  }

  const std::size_t fixed_capacity = 10000;
  int fixed_matrix[fixed_capacity] = {};
  int* dynamic_matrix = nullptr;
  int* matrix = fixed_matrix;

  if (num[0] == '1') {
    if (rows * cols > fixed_capacity) {
      std::cerr << "Matrix is too big\n";
      return 2;
    }
  } else {
    try {
      dynamic_matrix = new int[rows * cols];
    } catch (const std::bad_alloc&) {
      std::cerr << "Not enough memory\n";
      return 2;
    }
    matrix = dynamic_matrix;
  }

  if (!nosov::readMatrix(in, matrix, rows * cols)) {
    std::cerr << "Can not read matrix\n";
    delete[] dynamic_matrix;
    return 2;
  }

  std::ofstream out(argv[3]);
  nosov::writeMatrix(out, matrix, rows, cols) << "\n";
  out << nosov::findSeriesColumn(matrix, rows, cols) << "\n";
  delete[] dynamic_matrix;
  return 0;
}
