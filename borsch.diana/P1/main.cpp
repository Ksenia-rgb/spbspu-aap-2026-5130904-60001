#include <cstddef>
#include <fstream>
#include <iostream>
#include <memory>
#include <new>

namespace borsch {
  constexpr std::size_t maxFixedSize = 10000;

  static bool readElements(std::istream& in, int* matrix, const std::size_t count)
  {
    for (std::size_t i = 0; i < count; ++i) {
      if (!(in >> matrix[i])) {
        return false;
      }
    }
    return true;
  }

  static bool isLowerTriangular(const int* matrix, const int rows, const int cols)
  {
    const int size = (rows < cols) ? rows : cols;
    if (size == 0) {
      return false;
    }
    for (int row = 0; row < size; ++row) {
      for (int col = row + 1; col < size; ++col) {
        if (matrix[row * cols + col] != 0) {
          return false;
        }
      }
    }
    return true;
  }

  static bool isLocalMaximum(const int* matrix, const int cols, const int row, const int col)
  {
    const int radius = 1;
    const int value = matrix[row * cols + col];
    for (int i = row - radius; i <= row + radius; ++i) {
      for (int j = col - radius; j <= col + radius; ++j) {
        const bool isSelf = (i == row) && (j == col);
        if (!isSelf && (matrix[i * cols + j] >= value)) {
          return false;
        }
      }
    }
    return true;
  }

  static std::size_t countLocalMaxima(const int* matrix, const int rows, const int cols)
  {
    const int border = 1;
    std::size_t count = 0;
    for (int row = border; row < rows - border; ++row) {
      for (int col = border; col < cols - border; ++col) {
        if (isLocalMaximum(matrix, cols, row, col)) {
          ++count;
        }
      }
    }
    return count;
  }

  static bool writeResults(const char* path, const int* matrix, const int rows, const int cols)
  {
    std::ofstream output(path);
    if (!output) {
      return false;
    }
    output << std::boolalpha << isLowerTriangular(matrix, rows, cols) << '\n';
    output << countLocalMaxima(matrix, rows, cols) << '\n';
    return output.good();
  }
}

int main(int argc, char* argv[])
{
  const int exitBadArguments = 1;
  const int exitBadData = 2;
  const int argCount = 4;
  const int modeArg = 1;
  const int inputArg = 2;
  const int outputArg = 3;
  const char fixedMode = '1';
  const char dynamicMode = '2';

  if (argc != argCount) {
    std::cerr << "Usage: ./lab num input output\n";
    return exitBadArguments;
  }

  const char* mode = argv[modeArg];
  const bool isFixed = (mode[0] == fixedMode) && (mode[1] == '\0');
  const bool isDynamic = (mode[0] == dynamicMode) && (mode[1] == '\0');
  if (!isFixed && !isDynamic) {
    std::cerr << "First parameter must be 1 or 2\n";
    return exitBadArguments;
  }

  std::ifstream input(argv[inputArg]);
  if (!input) {
    std::cerr << "Cannot open input file\n";
    return exitBadData;
  }

  int rows = 0;
  int cols = 0;
  if (!(input >> rows >> cols) || (rows < 0) || (cols < 0)) {
    std::cerr << "Invalid matrix size\n";
    return exitBadData;
  }
  const std::size_t count = static_cast< std::size_t >(rows) * static_cast< std::size_t >(cols);

  try {
    bool isWritten = false;
    if (isFixed) {
      if (count > borsch::maxFixedSize) {
        std::cerr << "Matrix is too big for fixed array\n";
        return exitBadData;
      }
      int matrix[borsch::maxFixedSize] = {};
      if (!borsch::readElements(input, matrix, count)) {
        std::cerr << "Invalid matrix elements\n";
        return exitBadData;
      }
      isWritten = borsch::writeResults(argv[outputArg], matrix, rows, cols);
    } else {
      const std::unique_ptr< int[] > matrix = std::make_unique< int[] >(count);
      if (!borsch::readElements(input, matrix.get(), count)) {
        std::cerr << "Invalid matrix elements\n";
        return exitBadData;
      }
      isWritten = borsch::writeResults(argv[outputArg], matrix.get(), rows, cols);
    }
    if (!isWritten) {
      std::cerr << "Cannot write output file\n";
      return exitBadData;
    }
  } catch (const std::bad_alloc&) {
    std::cerr << "Not enough memory\n";
    return exitBadData;
  }
  return 0;
}
