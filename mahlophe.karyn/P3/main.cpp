#include <cstddef>
#include <fstream>
#include <iostream>
#include <limits>
#include <new>

namespace mahlophe {
  const std::size_t MAX_SIZE = 10000;

  bool isValidMode(const char * mode)
  {
    return mode[1] == '\0' && (mode[0] == '1' || mode[0] == '2');
  }

  std::size_t countNonZeroDiagonals(const long long * matrix, std::size_t rows, std::size_t cols)
  {
    std::size_t count = 0;

    for (std::size_t offset = 1; offset < cols; ++offset) {
      bool containsZero = false;
      const std::size_t length = (rows < cols - offset) ? rows : cols - offset;

      for (std::size_t i = 0; i < length; ++i) {
        const std::size_t index = i * cols + i + offset;

        if (matrix[index] == 0) {
          containsZero = true;
          break;
        }
      }

      if (!containsZero) {
        ++count;
      }
    }

    for (std::size_t offset = 1; offset < rows; ++offset) {
      bool containsZero = false;
      const std::size_t length = (rows - offset < cols) ? rows - offset : cols;

      for (std::size_t j = 0; j < length; ++j) {
        const std::size_t index = (j + offset) * cols + j;

        if (matrix[index] == 0) {
          containsZero = true;
          break;
        }
      }

      if (!containsZero) {
        ++count;
      }
    }

    return count;
  }

  void transformMatrix(long long * matrix, std::size_t rows, std::size_t cols)
  {
    for (std::size_t i = 0; i < rows; ++i) {
      for (std::size_t j = 0; j < cols; ++j) {
        const std::size_t top = i;
        const std::size_t left = j;
        const std::size_t bottom = rows - 1 - i;
        const std::size_t right = cols - 1 - j;

        std::size_t layer = top;

        if (left < layer) {
          layer = left;
        }

        if (bottom < layer) {
          layer = bottom;
        }

        if (right < layer) {
          layer = right;
        }

        const std::size_t index = i * cols + j;
        matrix[index] += static_cast< long long >(layer + 1);
      }
    }
  }

  void writeMatrix(std::ostream & output, const long long * matrix, std::size_t rows, std::size_t cols)
  {
    output << rows << ' ' << cols << '\n';

    for (std::size_t i = 0; i < rows; ++i) {
      for (std::size_t j = 0; j < cols; ++j) {
        const std::size_t index = i * cols + j;
        output << matrix[index] << ' ';
      }

      output << '\n';
    }
  }

  bool processMatrix(std::ifstream & input, std::ofstream & output, long long * matrix, std::size_t rows,
      std::size_t cols, std::size_t size)
  {
    for (std::size_t i = 0; i < size; ++i) {
      if (!(input >> matrix[i])) {
        std::cerr << "Error: invalid or incomplete matrix data\n";
        return false;
      }
    }

    char extraData = '\0';

    if (input >> extraData) {
      std::cerr << "Error: unexpected data after matrix\n";
      return false;
    }

    const std::size_t diagonalCount = countNonZeroDiagonals(matrix, rows, cols);

    transformMatrix(matrix, rows, cols);

    output << diagonalCount << '\n';
    writeMatrix(output, matrix, rows, cols);

    if (!output) {
      std::cerr << "Error: writing output failed\n";
      return false;
    }

    return true;
  }
}

int main(int argc, char * argv[])
{
  if (argc != 4) {
    std::cerr << "Error: expected 3 arguments\n";
    return 1;
  }

  if (!mahlophe::isValidMode(argv[1])) {
    std::cerr << "Error: invalid mode\n";
    return 1;
  }

  const bool useHeap = argv[1][0] == '2';

  std::ifstream input(argv[2]);

  if (!input.is_open()) {
    std::cerr << "Error: cannot open input file\n";
    return 2;
  }

  long long rowsValue = 0;
  long long colsValue = 0;

  if (!(input >> rowsValue >> colsValue) || rowsValue < 0 || colsValue < 0) {
    std::cerr << "Error: invalid matrix dimensions\n";
    return 2;
  }

  const std::size_t rows = static_cast< std::size_t >(rowsValue);
  const std::size_t cols = static_cast< std::size_t >(colsValue);
  if (cols != 0 && rows > std::numeric_limits< std::size_t >::max() / cols) {
    std::cerr << "Error: matrix is too large\n";
    return 2;
  }

  const std::size_t size = rows * cols;

  if (!useHeap) {
    if (size > mahlophe::MAX_SIZE) {
      std::cerr << "Error: matrix exceeds fixed array capacity\n";
      return 2;
    }

    long long fixedMatrix[mahlophe::MAX_SIZE];

    std::ofstream output(argv[3]);

    if (!output.is_open()) {
      std::cerr << "Error: cannot open output file\n";
      return 2;
    }

    if (!mahlophe::processMatrix(input, output, fixedMatrix, rows, cols, size)) {
      return 2;
    }
  } else {
    long long * dynamicMatrix = new (std::nothrow) long long[size];

    if (dynamicMatrix == nullptr) {
      std::cerr << "Error: memory allocation failed\n";
      return 2;
    }

    std::ofstream output(argv[3]);

    if (!output.is_open()) {
      std::cerr << "Error: cannot open output file\n";
      delete[] dynamicMatrix;
      return 2;
    }

    const bool success = mahlophe::processMatrix(input, output, dynamicMatrix, rows, cols, size);

    delete[] dynamicMatrix;

    if (!success) {
      return 2;
    }
  }

  return 0;
}
