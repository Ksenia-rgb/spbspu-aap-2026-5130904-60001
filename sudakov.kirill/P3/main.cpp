#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>

namespace sudakov {
  bool readMatrix(std::ifstream& input, int* matrix, size_t size)
  {
    for (size_t i = 0; i < size; ++i) {
      input >> matrix[i];
    }
    return !input.fail();
  }

  size_t cntLocMax(const int* matrix, size_t rows, size_t cols)
  {
    size_t count = 0;
    for (size_t row = 1; row + 1 < rows; ++row) {
      for (size_t col = 1; col + 1 < cols; ++col) {
        const size_t pos = row * cols + col;
        const int value = matrix[pos];
        bool is_max = true;
        if (value <= matrix[pos - cols - 1]) {
          is_max = false;
        }
        if (value <= matrix[pos - cols]) {
          is_max = false;
        }
        if (value <= matrix[pos - cols + 1]) {
          is_max = false;
        }
        if (value <= matrix[pos - 1]) {
          is_max = false;
        }
        if (value <= matrix[pos + 1]) {
          is_max = false;
        }
        if (value <= matrix[pos + cols - 1]) {
          is_max = false;
        }
        if (value <= matrix[pos + cols]) {
          is_max = false;
        }
        if (value <= matrix[pos + cols + 1]) {
          is_max = false;
        }
        if (is_max) {
          ++count;
        }
      }
    }
    return count;
  }

  size_t cntLocMin(const int* matrix, size_t rows, size_t cols)
  {
    size_t count = 0;
    for (size_t row = 1; row + 1 < rows; ++row) {
      for (size_t col = 1; col + 1 < cols; ++col) {
        const size_t pos = row * cols + col;
        const int value = matrix[pos];
        if (value < matrix[pos - cols - 1] and value < matrix[pos - cols] and value < matrix[pos - cols + 1]
            and value < matrix[pos - 1] and value < matrix[pos + 1] and value < matrix[pos + cols - 1]
            and value < matrix[pos + cols] and value < matrix[pos + cols + 1]) {
          ++count;
        }
      }
    }
    return count;
  }
}

int main(int argc, char* argv[])
{
  constexpr size_t max_size = 10000;

  if (argc != 4) {
    std::cerr << "Invalid number of arguments\n";
    return 1;
  }

  int mode = 0;
  if (argv[1][0] == '\0' or argv[1][1] != '\0') {
    std::cerr << "First parameter is not a number\n";
    return 1;
  }
  if (argv[1][0] == '1') {
    mode = 1;
  } else if (argv[1][0] == '2') {
    mode = 2;
  } else {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  if (!input.is_open()) {
    std::cerr << "Cannot open input file\n";
    return 2;
  }

  std::ofstream output(argv[3]);
  if (!output.is_open()) {
    std::cerr << "Cannot open output file\n";
    return 2;
  }

  int rows_raw = 0;
  int cols_raw = 0;
  input >> rows_raw >> cols_raw;
  if (!input or rows_raw < 0 or cols_raw < 0 or ((rows_raw == 0) != (cols_raw == 0))) {
    std::cerr << "Invalid matrix size\n";
    return 2;
  }

  const size_t rows = static_cast< size_t >(rows_raw);
  const size_t cols = static_cast< size_t >(cols_raw);
  const size_t size = rows * cols;

  if (mode == 1 and size > max_size) {
    std::cerr << "Matrix is too large\n";
    return 2;
  }

  int fixed[max_size] = {};
  int* matrix = fixed;
  if (mode == 2) {
    matrix = static_cast< int* >(malloc(size * sizeof(int)));
    if (matrix == nullptr and size != 0) {
      std::cerr << "Not enough memory\n";
      return 2;
    }
  }

  if (!sudakov::readMatrix(input, matrix, size)) {
    if (mode == 2) {
      free(matrix);
    }
    std::cerr << "Invalid matrix\n";
    return 2;
  }

  output << sudakov::cntLocMax(matrix, rows, cols) << '\n';
  output << sudakov::cntLocMin(matrix, rows, cols) << '\n';

  if (mode == 2) {
    free(matrix);
  }

  if (!output) {
    std::cerr << "Cannot write result\n";
    return 2;
  }
}
