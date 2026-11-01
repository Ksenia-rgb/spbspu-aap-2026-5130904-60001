#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>

namespace zahvaev
{
  const std::size_t maxFixedSize = 10000;
  const std::size_t maxSize = std::numeric_limits< std::size_t >::max();
  const int argsCount = 4;
  const int modeArg = 1;
  const int inputArg = 2;
  const int outputArg = 3;
  const int paramsError = 1;
  const int internalError = 2;

  bool readMatrix(std::istream &in, int *data, std::size_t count)
  {
    for (std::size_t i = 0; i < count; ++i)
    {
      if (!(in >> data[i]))
      {
        return false;
      }
    }
    in >> std::ws;
    return in.eof();
  }

  bool changeMatrix(int **matrix, std::size_t rows, std::size_t cols)
  {
    for (std::size_t i = 0; i < rows; ++i)
    {
      for (std::size_t j = 0; j < cols; ++j)
      {
        const std::size_t layer = std::min({i, j, rows - 1 - i, cols - 1 - j});
        const int offset = static_cast< int >(layer) + 1;
        if (matrix[i][j] > std::numeric_limits< int >::max() - offset)
        {
          return false;
        }
        matrix[i][j] += offset;
      }
    }
    return true;
  }

  long long calcMaxDiagonalSum(const int *const *matrix, std::size_t rows, std::size_t cols)
  {
    if (rows == 0 || cols == 0)
    {
      return 0;
    }
    const std::size_t secondary = cols - 1;
    long long max_sum = 0;
    bool is_found = false;
    for (std::size_t diagonal = 0; diagonal < rows + cols - 1; ++diagonal)
    {
      if (diagonal == secondary)
      {
        continue;
      }
      long long sum = 0;
      for (std::size_t i = 0; i < rows; ++i)
      {
        for (std::size_t j = 0; j < cols; ++j)
        {
          if (i + j == diagonal)
          {
            sum += matrix[i][j];
          }
        }
      }
      if (!is_found || sum > max_sum)
      {
        max_sum = sum;
        is_found = true;
      }
    }
    return max_sum;
  }
}

int main(int argc, char *argv[])
{
  if (argc != zahvaev::argsCount)
  {
    std::cerr << "Error: wrong number of arguments\n";
    return zahvaev::paramsError;
  }
  const bool isFixed = (std::strcmp(argv[zahvaev::modeArg], "1") == 0);
  const bool isDynamic = (std::strcmp(argv[zahvaev::modeArg], "2") == 0);
  if (!isFixed && !isDynamic)
  {
    std::cerr << "Error: first parameter must be 1 or 2\n";
    return zahvaev::paramsError;
  }

  std::ifstream in(argv[zahvaev::inputArg]);
  std::ofstream out(argv[zahvaev::outputArg]);
  if (!in || !out)
  {
    std::cerr << "Error: cannot open file\n";
    return zahvaev::internalError;
  }

  long long raw_rows = 0;
  long long raw_cols = 0;
  if (!(in >> raw_rows >> raw_cols) || raw_rows < 0 || raw_cols < 0)
  {
    std::cerr << "Error: invalid matrix size\n";
    return zahvaev::internalError;
  }
  const std::size_t rows = static_cast< std::size_t >(raw_rows);
  const std::size_t cols = static_cast< std::size_t >(raw_cols);
  if ((cols != 0 && rows > zahvaev::maxSize / sizeof(int) / cols) || rows > zahvaev::maxSize / sizeof(int *))
  {
    std::cerr << "Error: matrix is too large\n";
    return zahvaev::internalError;
  }
  const std::size_t count = rows * cols;
  if (isFixed && (count > zahvaev::maxFixedSize || rows > zahvaev::maxFixedSize))
  {
    std::cerr << "Error: matrix does not fit into fixed array\n";
    return zahvaev::internalError;
  }

  int fixed_data[zahvaev::maxFixedSize] = {};
  int *fixed_rows[zahvaev::maxFixedSize] = {};
  int *dynamic_data = nullptr;
  int **dynamic_rows = nullptr;
  int *data = fixed_data;
  int **row_pointers = fixed_rows;
  if (isDynamic)
  {
    dynamic_data = static_cast< int * >(std::malloc(count * sizeof(int)));
    dynamic_rows = static_cast< int ** >(std::malloc(rows * sizeof(int *)));
    if ((dynamic_data == nullptr && count > 0) || (dynamic_rows == nullptr && rows > 0))
    {
      std::free(dynamic_data);
      std::free(dynamic_rows);
      std::cerr << "Error: not enough memory\n";
      return zahvaev::internalError;
    }
    data = dynamic_data;
    row_pointers = dynamic_rows;
  }

  if (!zahvaev::readMatrix(in, data, count))
  {
    std::free(dynamic_data);
    std::free(dynamic_rows);
    std::cerr << "Error: invalid matrix content\n";
    return zahvaev::internalError;
  }
  for (std::size_t i = 0; i < rows; ++i)
  {
    row_pointers[i] = data + i * cols;
  }

  const long long max_sum = zahvaev::calcMaxDiagonalSum(row_pointers, rows, cols);
  if (!zahvaev::changeMatrix(row_pointers, rows, cols))
  {
    std::free(dynamic_data);
    std::free(dynamic_rows);
    std::cerr << "Error: integer overflow\n";
    return zahvaev::internalError;
  }

  out << rows << ' ' << cols;
  for (std::size_t i = 0; i < rows; ++i)
  {
    for (std::size_t j = 0; j < cols; ++j)
    {
      out << ' ' << row_pointers[i][j];
    }
  }
  out << '\n' << max_sum << '\n';
  std::free(dynamic_data);
  std::free(dynamic_rows);
  if (!out)
  {
    std::cerr << "Error: cannot write output file\n";
    return zahvaev::internalError;
  }
  return 0;
}
