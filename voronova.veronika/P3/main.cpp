#include <iostream>
#include <cstddef>
#include <fstream>
#include <algorithm>

namespace voronova {
  bool readMtx(std::istream &in, int *data, std::size_t count)
  {
    for (std::size_t k = 0; k < count; ++k) {
      if (!(in >> data[k])) {
        return false;
      }
    }
    return true;
  }

  void trmLftBotClk(int *data, std::size_t rows, std::size_t cols)
  {
    std::size_t top = 0;
    std::size_t left = 0;
    std::size_t bottom = rows;
    std::size_t right = cols;
    int step = 1;
    while ((top < bottom) && (left < right)) {
      for (std::size_t i = bottom; i > top; --i) {
        data[(i - 1) * cols + left] -= step;
        ++step;
      }
      ++left;
      if (left < right) {
        for (std::size_t j = left; j < right; ++j) {
          data[top * cols + j] -= step;
          ++step;
        }
        ++top;
        if (top < bottom) {
          for (std::size_t i = top; i < bottom; ++i) {
            data[i * cols + right - 1] -= step;
            ++step;
                }
          --right;
          if (left < right) {
            for (std::size_t j = right; j > left; --j) {
              data[(bottom - 1) * cols + j - 1] -= step;
              ++step;
            }
            --bottom;
          }
        }
      }
    }
  }

  void writeMtx(std::ostream &out, const int *data, std::size_t rows, std::size_t cols)
  {
    out << rows << ' ' << cols;
    for (std::size_t k = 0; k < rows * cols; ++k) {
      out << ' ' << data[k];
    }
    out << '\n';
  }

  bool isLowerTriangular(const int *data, std::size_t rows, std::size_t cols)
  {
    std::size_t size = std::min(rows, cols);
    if (size == 0) {
      return false;
    }
    for (std::size_t i = 0; i < size; ++i) {
      for (std::size_t j = i + 1; j < size; ++j) {
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

  const std::string task = argv[1];
  if ((task != "1") && (task != "2")) {
    std::cerr << "Error: wrong task number\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  if (!input) {
    std::cerr << "Error: cannot open input file\n";
    return 2;
  }

  int rows = 0;
  int cols = 0;
  if (!(input >> rows >> cols)) {
    std::cerr << "Error: wrong matrix size\n";
    return 2;
  }
  if ((rows < 0) || (cols < 0)) {
    std::cerr << "Error: wrong matrix size\n";
    return 2;
  }

  std::ofstream output(argv[3]);
  if (!output) {
    std::cerr << "Error: cannot open output file\n";
    return 2;
  }

  if (task == "1") {
    const int capacity = 10000;
    if ((rows != 0) && (cols > capacity / rows)) {
      std::cerr << "Error: matrix is too large\n";
      return 2;
    }

    int data[capacity] = {};

    if (!voronova::readMtx(input, data, rows * cols)) {
      std::cerr << "Error: wrong matrix elements\n";
      return 2;
    }

    bool lower = voronova::isLowerTriangular(data, rows, cols);
    voronova::trmLftBotClk(data, rows, cols);
    voronova::writeMtx(output, data, rows, cols);
    output << std::boolalpha << lower << '\n';
  } else {
    const std::size_t count = std::size_t(rows) * cols;
    int *data = nullptr;

    try {
      data = new int[count];
    } catch (const std::bad_alloc &) {
      std::cerr << "Error: cannot allocate memory\n";
      return 2;
    }

    if (!voronova::readMtx(input, data, count)) {
      std::cerr << "Error: wrong matrix elements\n";
      delete[] data;
      return 2;
    }

    bool lower = voronova::isLowerTriangular(data, rows, cols);
    voronova::trmLftBotClk(data, rows, cols);
    voronova::writeMtx(output, data, rows, cols);
    output << std::boolalpha << lower << '\n';
    delete[] data;
  }

  char extra = '\0';
  if (input >> extra) {
    std::cerr << "Error: extra data in input file\n";
    return 2;
  }
  return 0;
}
