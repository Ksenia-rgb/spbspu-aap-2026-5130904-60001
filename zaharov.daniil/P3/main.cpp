#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstddef>
#include <memory>

namespace zaharov
{

  const int maxElements = 10000;

  std::istream &readMatrix(std::ifstream &in, int *data, size_t &rows, size_t &cols)
  {
    if (!(in >> rows >> cols))
    {
      return in;
    }

    if (rows > maxElements || cols > maxElements || rows * cols > maxElements)
    {
      return in;
    }

    const size_t total = rows * cols;
    for (size_t i = 0; i < total; ++i)
    {
      if (!(in >> data[i]))
      {
        return in;
      }
    }

    return in;
  }

  size_t findBestColumn(const int *data, size_t rows, size_t cols)
  {
    size_t max_series = 0;
    size_t best_col = 0;

    for (size_t j = 0; j < cols; ++j)
    {
      size_t cur_series = 1;
      size_t col_max_series = 1;

      for (size_t i = 1; i < rows; ++i)
      {
        if (data[i * cols + j] == data[(i - 1) * cols + j])
        {
          ++cur_series;
        }
        else
        {
          cur_series = 1;
        }

        if (cur_series > col_max_series)
        {
          col_max_series = cur_series;
        }
      }

      if (col_max_series > max_series)
      {
        max_series = col_max_series;
        best_col = j + 1;
      }
    }
    return best_col;
  }

  void applySpiralDecrease(int *data, size_t rows, size_t cols)
  {
    if (rows == 0 || cols == 0)
    {
      return;
    }

    size_t top = 0;
    size_t bottom = rows - 1;
    size_t left = 0;
    size_t right = cols - 1;
    int step = 1;

    while (top <= bottom && left <= right)
    {
      for (size_t i = 0; i <= bottom - top; ++i)
      {
        data[(bottom - i) * cols + left] -= step++;
      }
      ++left;

      if (top <= bottom)
      {
        for (size_t j = 0; j <= right - left; ++j)
        {
          data[top * cols + (left + j)] -= step++;
        }
        ++top;
      }

      if (left <= right)
      {
        for (size_t i = 0; i <= bottom - top; ++i)
        {
          data[(top + i) * cols + right] -= step++;
        }
        --right;
      }

      if (top <= bottom)
      {
        for (size_t j = 0; j <= right - left; ++j)
        {
          data[bottom * cols + (right - j)] -= step++;
        }
        --bottom;
      }
    }
  }

  std::ostream &writeMatrix(std::ofstream &out, const int *data, size_t rows, size_t cols)
  {
    out << rows << ' ' << cols << '\n';

    for (size_t i = 0; i < rows; ++i)
    {
      for (size_t j = 0; j < cols; ++j)
      {
        out << data[i * cols + j];
        if (j + 1 < cols)
        {
          out << ' ';
        }
      }
      out << '\n';
    }
    return out;
  }

  bool parseArgs(int argc, char *argv[], size_t &num, const char *&input_file, const char *&output_file)
  {
    if (argc != 4)
    {
      return false;
    }

    char *end = nullptr;
    const long parsed = std::strtol(argv[1], &end, 10);

    if (*end != '\0' || (parsed != 1 && parsed != 2))
    {
      return false;
    }

    num = static_cast< size_t >(parsed);
    input_file = argv[2];
    output_file = argv[3];
    return true;
  }

  bool processMatrix(size_t num, std::ifstream &in, std::ofstream &out)
  {
    size_t rows = 0;
    size_t cols = 0;
    int *data = nullptr;
    int *original = nullptr;
    int stack_data[maxElements];
    int stack_original[maxElements];

    if (num == 1)
    {
      data = stack_data;
      original = stack_original;
      if (!readMatrix(in, data, rows, cols))
      {
        return false;
      }
    }
    else
    {
      if (!(in >> rows >> cols))
      {
        return false;
      }

      if (rows > maxElements || cols > maxElements || rows * cols > maxElements)
      {
        return false;
      }

      data = new int[rows * cols];
      original = new int[rows * cols];

      const size_t total = rows * cols;
      for (size_t i = 0; i < total; ++i)
      {
        if (!(in >> data[i]))
        {
          delete[] data;
          delete[] original;
          return false;
        }
      }
    }

    const size_t total = rows * cols;
    if (total > 0)
    {
      for (size_t = 0; i < total; ++i)
      {
        original[i] = data[i];
      }

      applySpiralDecrease(data, rows, cols);
      writeMatrix(out, data, rows, cols);
      out << findBestColumn(original, rows, cols) << '\n';
    }
    else
    {
      out << rows << ' ' << cols << '\n';
      out << 0 << '\n';
    }

    if (num == 2)
    {
      delete[] data;
      delete[] original;
    }

    return true;
  }

  int run(int argc, char *argv[])
  {
    size_t num = 0;
    const char *input_file = nullptr;
    const char *output_file = nullptr;

    if (!parseArgs(argc, argv, num, input_file, output_file))
    {
      std::cerr << "Error: expected 3 arguments\n";
      return 1;
    }

    std::ifstream in(input_file);
    if (!in)
    {
      std::cerr << "Error: cannot open input file\n";
      return 2;
    }

    std::ofstream out(output_file);
    if (!out)
    {
      std::cerr << "Error: cannot open output file\n";
      return 2;
    }

    if (!processMatrix(num, in, out))
    {
      std::cerr << "Error: cannot read matrix\n";
      return 2;
    }

    return 0;
  }
}

int main(int argc, char *argv[])
{
  return zaharov::run(argc, argv);
}
