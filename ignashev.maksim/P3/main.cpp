#include <iostream>
#include <fstream>
#include <cstddef>
#include <memory>
#include <stdexcept>

namespace ignashev {
  std::size_t countLocalMax(const int* matrix, std::size_t rows, std::size_t cols)
  {
    if (rows < 3 || cols < 3) {
      return 0;
    }
    std::size_t count = 0;
    for (std::size_t i = 1; i < rows - 1; ++i) {
      for (std::size_t j = 1; j < cols - 1; ++j) {
        const int current = matrix[i * cols + j];
        const bool isGreaterTop = current > matrix[(i - 1) * cols + j];
        const bool isGreaterBottom = current > matrix[(i + 1) * cols + j];
        const bool isGreaterVertical = isGreaterTop && isGreaterBottom;
        const bool isGreaterLeft = current > matrix[i * cols + (j - 1)];
        const bool isGreaterRight = current > matrix[i * cols + (j + 1)];
        const bool isGreaterHorizontal = isGreaterLeft && isGreaterRight;
        if (isGreaterVertical && isGreaterHorizontal) {
          ++count;
        }
      }
    }
    return count;
  }
  void transformLeftBotClockwise(int* matrix, std::size_t rows, std::size_t cols)
  {
    if (rows == 0 || cols == 0) {
      return;
    }
    std::size_t top = 0;
    std::size_t bottom = rows - 1;
    std::size_t left = 0;
    std::size_t right = cols - 1;
    std::size_t r = bottom;
    std::size_t c = left;
    int decrement = 1;
    const int dirUp = 0;
    const int dirRight = 1;
    const int dirDown = 2;
    const int dirLeft = 3;
    int direction = dirUp;
    const std::size_t totalElements = rows * cols;
    for (std::size_t step = 0; step < totalElements; ++step) {
      matrix[r * cols + c] -= decrement;
      ++decrement;
      if (direction == dirUp) {
        if (r > top) {
          --r;
        } else {
          direction = dirRight;
          ++left;
          ++c;
        }
      } else if (direction == dirRight) {
        if (c < right) {
          ++c;
        } else {
          direction = dirDown;
          ++top;
          ++r;
        }
      } else if (direction == dirDown) {
        if (r < bottom) {
          ++r;
        } else {
          direction = dirLeft;
          --right;
          --c;
        }
      } else if (direction == dirLeft) {
        if (c > left) {
          --c;
        } else {
          direction = dirUp;
          --bottom;
          --r;
        }
      }
    }
  }
  std::istream& readMatrix(std::istream& in, int* matrix, std::size_t rows, std::size_t cols)
  {
    const std::size_t totalElements = rows * cols;
    for (std::size_t i = 0; i < totalElements; ++i) {
      if (!(in >> matrix[i])) {
        return in;
      }
    }
    return in;
  }
  std::ostream& printMatrix(std::ostream& out, const int* matrix, std::size_t rows, std::size_t cols)
  {
    out << rows << " " << cols;
    const std::size_t totalElements = rows * cols;
    for (std::size_t i = 0; i < totalElements; ++i) {
      out << " " << matrix[i];
    }
    return out;
  }
}
int main(int argc, char* argv[])
{
  if (argc != 4) {
    std::cerr << "invalid number of arguments\n";
    return 1;
  }
  int task_num = 0;
  try {
    std::size_t pos = 0;
    task_num = std::stoi(argv[1], std::addressof(pos));
    if (argv[1][pos] != '\0' || (task_num != 1 && task_num != 2)) {
      std::cerr << "first argument must be 1 or 2\n";
      return 1;
    }
  } catch (const std::invalid_argument&) {
    std::cerr << "invalid task number\n";
    return 1;
  } catch (const std::out_of_range&) {
    std::cerr << "task number is out of range\n";
    return 1;
  }
  std::ifstream input(argv[2]);
  if (!input.is_open()) {
    std::cerr << "cannot open input file\n";
    return 2;
  }
  std::ofstream output(argv[3]);
  if (!output.is_open()) {
    std::cerr << "cannot open output file\n";
    return 2;
  }
  std::size_t rows = 0;
  std::size_t cols = 0;
  if (!(input >> rows >> cols)) {
    std::cerr << "invalid matrix dimensions\n";
    return 2;
  }
  if (rows == 0 && cols == 0) {
    output << 0 << "\n";
    output << "0 0\n";
    return 0;
  }
  if (rows == 0 || cols == 0) {
    std::cerr << "invalid zero dimension\n";
    return 2;
  }
  const std::size_t maxFixedSize = 10000;
  int fixed_matrix[maxFixedSize] = {};
  int* dynamic_matrix = nullptr;
  int* matrix = nullptr;
  if (task_num == 1) {
    if (rows * cols > maxFixedSize) {
      std::cerr << "matrix size exceeds fixed limit\n";
      return 2;
    }
    matrix = fixed_matrix;
  } else {
    try {
      dynamic_matrix = new int[rows * cols];
      matrix = dynamic_matrix;
    } catch (const std::bad_alloc& e) {
      std::cerr << e.what() << "\n";
      return 2;
    }
  }
  if (!ignashev::readMatrix(input, matrix, rows, cols)) {
    delete[] dynamic_matrix;
    std::cerr << "failed to read matrix element\n";
    return 2;
  }
  output << ignashev::countLocalMax(matrix, rows, cols) << "\n";
  ignashev::transformLeftBotClockwise(matrix, rows, cols);
  ignashev::printMatrix(output, matrix, rows, cols) << "\n";
  delete[] dynamic_matrix;
  return 0;
}
