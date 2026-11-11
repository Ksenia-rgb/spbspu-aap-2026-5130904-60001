#include <iostream>
#include <cstddef>
#include <fstream>
#include <algorithm>

namespace voronova {
  std::istream &readMtx(std::istream &in, int *data, size_t count)
  {
    for (size_t k = 0; k < count; ++k) {
      if (!(in >> data[k])) {
        return in;
      }
    }
    return in;
  }

  void trmLftBotClk(int *data, size_t rows, size_t cols)
  {
    size_t top = 0;
    size_t left = 0;
    size_t bottom = rows;
    size_t right = cols;
    int step = 1;
    while ((top < bottom) && (left < right)) {
      for (size_t i = bottom; i > top; --i) {
        data[(i - 1) * cols + left] -= step;
        ++step;
      }
      ++left;
      if (left < right) {
        for (size_t j = left; j < right; ++j) {
          data[top * cols + j] -= step;
          ++step;
        }
        ++top;
        if (top < bottom) {
          for (size_t i = top; i < bottom; ++i) {
            data[i * cols + right - 1] -= step;
            ++step;
                }
          --right;
          if (left < right) {
            for (size_t j = right; j > left; --j) {
              data[(bottom - 1) * cols + j - 1] -= step;
              ++step;
            }
            --bottom;
          }
        }
      }
    }
  }

  std::ostream &writeMtx(std::ostream &out, const int *data, size_t rows, size_t cols)
  {
    out << rows << ' ' << cols;
    for (size_t k = 0; k < rows * cols; ++k) {
      out << ' ' << data[k];
    }
    return out;
  }

  bool isLowerTriangular(const int *data, size_t rows, size_t cols)
  {
    size_t size = std::min(rows, cols);
    if (size == 0) {
      return false;
    }
    for (size_t i = 0; i < size; ++i) {
      for (size_t j = i + 1; j < size; ++j) {
        if (data[i * cols + j] != 0) {
          return false;
        }
      }
    }
    return true;
  }
}

int main(int argc, char *argv[])
{
  if (argc != 4) {
    std::cerr << "Error: invalid number of arguments\n";
    return 1;
  }

  const char *task = argv[1];
  if (((task[0] != '1') && (task[0] != '2')) || (task[1] != '\0')) {
    std::cerr << "Error: wrong task number\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  if (!input) {
    std::cerr << "Error: cannot open input file\n";
    return 2;
  }

  size_t rows = 0;
  size_t cols = 0;
  if (!(input >> rows >> cols)) {
    std::cerr << "Error: wrong matrix size\n";
    return 2;
  }

  std::ofstream output(argv[3]);
  if (!output) {
    std::cerr << "Error: cannot open output file\n";
    return 2;
  }

  const size_t capacity = 10000;
  if ((task[0] == '1') && (rows != 0) && (cols > capacity / rows)) {
    std::cerr << "Error: matrix is too large\n";
    return 2;
  }

  int fixedData[capacity] = {};
  int *data = fixedData;

  if (task[0] == '2') {
    try {
      data = new int[rows * cols];
    } catch (const std::bad_alloc &) {
      std::cerr << "Error: cannot allocate memory\n";
      return 2;
    }
  }

  if (!voronova::readMtx(input, data, rows * cols)) {
    std::cerr << "Error: wrong matrix elements\n";
    if (task[0] == '2') {
      delete[] data;
    }
    return 2;
  }

  bool lower = voronova::isLowerTriangular(data, rows, cols);
  voronova::trmLftBotClk(data, rows, cols);
  voronova::writeMtx(output, data, rows, cols) << '\n';
  output << std::boolalpha << lower << '\n';

  if (task[0] == '2') {
    delete [] data;
  }
  return 0;
}
