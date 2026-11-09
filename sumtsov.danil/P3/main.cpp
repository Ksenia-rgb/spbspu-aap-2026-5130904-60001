#include <cerrno>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <new>

namespace sumtsov
{

  bool parseNonNegativeInt(const char *text, long long &value)
  {
    if ((text == nullptr) || (*text == '\0'))
    {
      return false;
    }

    char *end = nullptr;
    errno = 0;
    long long parsed = std::strtoll(text, &end, 10);

    if ((end == text) || (*end != '\0') || (errno == ERANGE) || (parsed < 0))
    {
      return false;
    }

    value = parsed;
    return true;
  }

  std::istream &readMatrixHeader(std::istream &in, size_t &rows, size_t &cols)
  {
    long long rows_value = 0;
    long long cols_value = 0;

    in >> rows_value;
    if (!in || (rows_value < 0))
    {
      in.setstate(std::ios::failbit);
      return in;
    }

    in >> cols_value;
    if (!in || (cols_value < 0))
    {
      in.setstate(std::ios::failbit);
      return in;
    }

    rows = static_cast< size_t >(rows_value);
    cols = static_cast< size_t >(cols_value);
    return in;
  }

  std::istream &readMatrixData(std::istream &in, size_t rows, size_t cols, int *data)
  {
    for (size_t i = 0; i < rows * cols; ++i)
    {
      if (!(in >> data[i]))
      {
        break;
      }
    }
    return in;
  }

  size_t countSaddlePoints(const int *data, size_t rows, size_t cols)
  {
    if ((rows == 0) || (cols == 0))
    {
      return 0;
    }

    int *row_min = nullptr;
    int *col_max = nullptr;

    try
    {
      row_min = new int[rows];
      col_max = new int[cols];
    }
    catch (const std::bad_alloc &)
    {
      delete[] row_min;
      delete[] col_max;
      throw;
    }

    for (size_t i = 0; i < rows; ++i)
    {
      row_min[i] = data[i * cols];
      for (size_t j = 1; j < cols; ++j)
      {
        int value = data[i * cols + j];
        if (value < row_min[i])
        {
          row_min[i] = value;
        }
      }
    }

    for (size_t j = 0; j < cols; ++j)
    {
      col_max[j] = data[j];
      for (size_t i = 1; i < rows; ++i)
      {
        int value = data[i * cols + j];
        if (value > col_max[j])
        {
          col_max[j] = value;
        }
      }
    }

    size_t count = 0;
    for (size_t i = 0; i < rows; ++i)
    {
      for (size_t j = 0; j < cols; ++j)
      {
        int value = data[i * cols + j];
        if ((value == row_min[i]) && (value == col_max[j]))
        {
          ++count;
        }
      }
    }

    delete[] row_min;
    delete[] col_max;

    return count;
  }

  size_t minOf(size_t a, size_t b)
  {
    return (a < b) ? a : b;
  }

  void buildTopLeftSquare(const int *data, size_t cols, size_t n, int *square)
  {
    for (size_t i = 0; i < n; ++i)
    {
      for (size_t j = 0; j < n; ++j)
      {
        square[i * n + j] = data[i * cols + j];
      }
    }
  }

  void transformSpiralTopLeftClockwise(int *square, size_t n)
  {
    if (n == 0)
    {
      return;
    }

    size_t top = 0;
    size_t bottom = n - 1;
    size_t left = 0;
    size_t right = n - 1;
    size_t step = 1;
    size_t side = n;

    while ((top <= bottom) && (left <= right))
    {
      for (size_t col = left; col <= right; ++col)
      {
        square[top * side + col] -= static_cast< int >(step);
        ++step;
      }
      ++top;

      if (top > bottom)
      {
        break;
      }

      for (size_t row = top; row <= bottom; ++row)
      {
        square[row * side + right] -= static_cast< int >(step);
        ++step;
      }

      if (right == left)
      {
        break;
      }
      --right;

      if (left > right)
      {
        break;
      }

      for (size_t col = right + 1; col-- > left;)
      {
        square[bottom * side + col] -= static_cast< int >(step);
        ++step;
      }

      if (bottom == top)
      {
        break;
      }
      --bottom;

      for (size_t row = bottom + 1; row-- > top;)
      {
        square[row * side + left] -= static_cast< int >(step);
        ++step;
      }

      ++left;
    }
  }

  void writeMatrix(std::ostream &out, const int *data, size_t rows, size_t cols)
  {
    out << rows << ' ' << cols;
    for (size_t i = 0; i < rows * cols; ++i)
    {
      out << ' ' << data[i];
    }
  }

}

int main(int argc, char *argv[])
{
  if (argc != 4)
  {
    std::cerr << "Error: expected 3 arguments: num input output\n";
    return 1;
  }

  long long num_value = 0;
  if (!sumtsov::parseNonNegativeInt(argv[1], num_value) || ((num_value != 1) && (num_value != 2)))
  {
    std::cerr << "Error: first argument must be 1 or 2\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  if (!input)
  {
    std::cerr << "Error: cannot open input file\n";
    return 2;
  }

  size_t rows = 0;
  size_t cols = 0;
  if (!sumtsov::readMatrixHeader(input, rows, cols))
  {
    std::cerr << "Error: input file does not contain a valid matrix\n";
    return 2;
  }

  const size_t max_fixed_elements = 10000;
  int fixed_data[max_fixed_elements];
  int *dynamic_data = nullptr;
  int *data = nullptr;

  if (num_value == 1)
  {
    if (rows * cols > max_fixed_elements)
    {
      std::cerr << "Error: matrix is too large for fixed storage\n";
      return 2;
    }
    data = fixed_data;
  }
  else
  {
    try
    {
      dynamic_data = new int[rows * cols];
    }
    catch (const std::bad_alloc &)
    {
      std::cerr << "Error: failed to allocate memory\n";
      return 2;
    }
    data = dynamic_data;
  }

  if (!sumtsov::readMatrixData(input, rows, cols, data))
  {
    std::cerr << "Error: input file does not contain a valid matrix\n";
    delete[] dynamic_data;
    return 2;
  }

  size_t saddle_count = 0;
  size_t square_size = sumtsov::minOf(rows, cols);
  int *square = nullptr;

  try
  {
    saddle_count = sumtsov::countSaddlePoints(data, rows, cols);
    square = new int[square_size * square_size];
  }
  catch (const std::bad_alloc &)
  {
    std::cerr << "Error: failed to allocate memory\n";
    delete[] dynamic_data;
    return 2;
  }

  sumtsov::buildTopLeftSquare(data, cols, square_size, square);
  sumtsov::transformSpiralTopLeftClockwise(square, square_size);

  std::ofstream output(argv[3]);
  if (!output)
  {
    std::cerr << "Error: cannot open output file\n";
    delete[] dynamic_data;
    delete[] square;
    return 2;
  }

  output << saddle_count << '\n';
  sumtsov::writeMatrix(output, square, square_size, square_size);
  output << '\n';

  delete[] dynamic_data;
  delete[] square;

  return 0;
}
