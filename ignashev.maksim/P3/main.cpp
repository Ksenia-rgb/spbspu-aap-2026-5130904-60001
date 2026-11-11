#include <iostream>
#include <fstream>
#include <stdexcept>

namespace ignashev {
  int countLocalMax(const int* const* matrix, int rows, int cols)
  {
    if (rows < 3 || cols < 3) {
      return 0;
    }
    int count = 0;
    for (int i = 1; i < rows - 1; ++i) {
      for (int j = 1; j < cols - 1; ++j) {
        const int current = matrix[i][j];
        const bool isGreaterVertical = (current > matrix[i - 1][j]) && (current > matrix[i + 1][j]);
        const bool isGreaterHorizontal = (current > matrix[i][j - 1]) && (current > matrix[i][j + 1]);
        if (isGreaterVertical && isGreaterHorizontal) {
          ++count;
        }
      }
    }
    return count;
  }
  void transformLeftBotClockwise(int** matrix, int rows, int cols)
  {
    if (rows <= 0 || cols <= 0) {
      return;
    }
    int top = 0;
    int bottom = rows - 1;
    int left = 0;
    int right = cols - 1;
    int r = bottom;
    int c = left;
    int decrement = 1;
    const int dirUp = 0;
    const int dirRight = 1;
    const int dirDown = 2;
    const int dirLeft = 3;
    int direction = dirUp;
    const int totalElements = rows * cols;
    for (int step = 0; step < totalElements; ++step) {
      matrix[r][c] -= decrement;
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
  void freeMatrix(int** matrix, int rows)
  {
    if (matrix == nullptr) {
      return;
    }
    for (int i = 0; i < rows; ++i) {
      delete[] matrix[i];
    }
    delete[] matrix;
  }
  int** allocateMatrix(int rows, int cols)
  {
    int** const matrix = new int*[rows];
    for (int i = 0; i < rows; ++i) {
      matrix[i] = nullptr;
    }
    try {
      for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[cols];
      }
    } catch (const std::bad_alloc&) {
      freeMatrix(matrix, rows);
      throw;
    }
    return matrix;
  }
  void readMatrix(std::istream& in, int** matrix, int rows, int cols)
  {
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        if (!(in >> matrix[i][j])) {
          throw std::runtime_error("failed to read matrix element");
        }
      }
    }
  }
  void printMatrix(std::ostream& out, const int* const* matrix, int rows, int cols)
  {
    out << rows << " " << cols;
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        out << " " << matrix[i][j];
      }
    }
    out << "\n";
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
    task_num = std::stoi(argv[1], &pos);
    if (argv[1][pos] != '\0' || (task_num != 1 && task_num != 2)) {
      std::cerr << "first argument must be 1 or 2\n";
      return 1;
    }
  } catch (const std::exception&) {
    std::cerr << "invalid task number\n";
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
  int rows = 0;
  int cols = 0;
  if (!(input >> rows >> cols) || rows < 0 || cols < 0) {
    std::cerr << "invalid matrix dimensions\n";
    return 2;
  }
  if (rows == 0 && cols == 0) {
    if (task_num == 1) {
      output << 0 << "\n";
    } else {
      output << "0 0\n";
    }
    return 0;
  }
  if (rows == 0 || cols == 0) {
    std::cerr << "invalid zero dimension\n";
    return 2;
  }
  int** matrix = nullptr;
  try {
    matrix = ignashev::allocateMatrix(rows, cols);
    ignashev::readMatrix(input, matrix, rows, cols);
    if (task_num == 1) {
      output << ignashev::countLocalMax(matrix, rows, cols) << "\n";
    } else {
      ignashev::transformLeftBotClockwise(matrix, rows, cols);
      ignashev::printMatrix(output, matrix, rows, cols);
    }
  } catch (const std::exception& e) {
    ignashev::freeMatrix(matrix, rows);
    std::cerr << e.what() << "\n";
    return 2;
  }
  ignashev::freeMatrix(matrix, rows);
  return 0;
}
