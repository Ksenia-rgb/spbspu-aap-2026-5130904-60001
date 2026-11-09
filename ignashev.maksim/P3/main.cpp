#include <iostream>

namespace ignashev {
  int countLocalMax(const int* const* const matrix, const int rows, const int cols)
  {
    int count = 0;
    for (int i = 1; i < rows - 1; ++i) {
      for (int j = 1; j < cols - 1; ++j) {
        const int current = matrix[i][j];
        if ((current > matrix[i - 1][j]) &&
            (current > matrix[i + 1][j]) &&
            (current > matrix[i][j - 1]) &&
            (current > matrix[i][j + 1])) {
          ++count;
        }
      }
    }
    return count;
  }
  void transformLeftBotClockwise(int** const matrix, const int rows, const int cols)
  {
    int top = 0;
    int bottom = rows - 1;
    int left = 0;
    int right = cols - 1;
    int r = bottom;
    int c = left;
    int decrement = 1;
    int direction = 0;
    const int totalElements = rows * cols;
    for (int step = 0; step < totalElements; ++step) {
      matrix[r][c] -= decrement;
      ++decrement;
      if (direction == 0) {
        if (r > top) {
          --r;
        } else {
          direction = 1;
          ++left;
          ++c;
        }
      } else if (direction == 1) {
        if (c < right) {
          ++c;
        } else {
          direction = 2;
          ++top;
          ++r;
        }
      } else if (direction == 2) {
        if (r < bottom) {
          ++r;
        } else {
          direction = 3;
          --right;
          --c;
        }
      } else if (direction == 3) {
        if (c > left) {
          --c;
        } else {
          direction = 0;
          --bottom;
          --r;
        }
      }
    }
  }
  void runDemo()
  {
    const int rows = 3;
    const int cols = 3;
    int** const matrix = new int*[rows];
    for (int i = 0; i < rows; ++i) {
      matrix[i] = new int[cols];
    }
    matrix[0][0] = 3;
    matrix[0][1] = 3;
    matrix[0][2] = 2;
    matrix[1][0] = 3;
    matrix[1][1] = 5;
    matrix[1][2] = 2;
    matrix[2][0] = 2;
    matrix[2][1] = 3;
    matrix[2][2] = 2;
    const int localMaxCount = countLocalMax(matrix, rows, cols);
    std::cout << "result: " << localMaxCount << "\n";
    matrix[0][0] = 1;
    matrix[0][1] = 2;
    matrix[0][2] = 3;
    matrix[1][0] = 4;
    matrix[1][1] = 5;
    matrix[1][2] = 6;
    matrix[2][0] = 7;
    matrix[2][1] = 8;
    matrix[2][2] = 9;
    transformLeftBotClockwise(matrix, rows, cols);
    std::cout << "result:\n";
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        std::cout << matrix[i][j] << " ";
      }
      std::cout << '\n';
    }
    for (int i = 0; i < rows; ++i) {
      delete[] matrix[i];
    }
    delete[] matrix;
  }
}
int main()
{
  ignashev::runDemo();
  return 0;
}