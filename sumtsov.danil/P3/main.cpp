#include <fstream>
#include <iostream>
#include <string>

namespace sumtsov
{

  bool parseNonNegativeInt(const std::string &text, long long &value)
  {
    if (text.empty())
    {
      return false;
    }

    for (char c : text)
    {
      if (c < '0' || c > '9')
      {
        return false;
      }
    }

    try
    {
      size_t consumed = 0;
      value = std::stoll(text, &consumed);
      return consumed == text.size();
    }
    catch (const std::exception &)
    {
      return false;
    }
  }

  bool readMatrixHeader(std::istream &in, size_t &rows, size_t &cols)
  {
    long long rowsValue = 0;
    long long colsValue = 0;

    if (!(in >> rowsValue) || rowsValue < 0)
    {
      return false;
    }

    if (!(in >> colsValue) || colsValue < 0)
    {
      return false;
    }

    rows = static_cast< size_t >(rowsValue);
    cols = static_cast< size_t >(colsValue);
    return true;
  }

  bool readMatrixData(std::istream &in, size_t rows, size_t cols, int *data)
  {
    for (size_t i = 0; i < rows * cols; ++i)
    {
      if (!(in >> data[i]))
      {
        return false;
      }
    }

    return true;
  }

  size_t countSaddlePoints(const int *data, size_t rows, size_t cols)
  {
    if (rows == 0 || cols == 0)
    {
      return 0;
    }

    int *rowMin = new int[rows];
    int *colMax = new int[cols];

    for (size_t i = 0; i < rows; ++i)
    {
      rowMin[i] = data[i * cols];
      for (size_t j = 1; j < cols; ++j)
      {
        int value = data[i * cols + j];
        if (value < rowMin[i])
        {
          rowMin[i] = value;
        }
      }
    }

    for (size_t j = 0; j < cols; ++j)
    {
      colMax[j] = data[j];
      for (size_t i = 1; i < rows; ++i)
      {
        int value = data[i * cols + j];
        if (value > colMax[j])
        {
          colMax[j] = value;
        }
      }
    }

    size_t count = 0;
    for (size_t i = 0; i < rows; ++i)
    {
      for (size_t j = 0; j < cols; ++j)
      {
        int value = data[i * cols + j];
        if (value == rowMin[i] && value == colMax[j])
        {
          ++count;
        }
      }
    }

    delete[] rowMin;
    delete[] colMax;

    return count;
  }

  int *buildTopLeftSquare(const int *data, size_t rows, size_t cols, size_t &n)
  {
    n = (rows < cols) ? rows : cols;

    int *square = new int[n * n];
    for (size_t i = 0; i < n; ++i)
    {
      for (size_t j = 0; j < n; ++j)
      {
        square[i * n + j] = data[i * cols + j];
      }
    }

    return square;
  }

  void transformSpiralTopLeftClockwise(int *square, size_t n)
  {
    if (n == 0)
    {
      return;
    }

    int top = 0;
    int bottom = static_cast< int >(n) - 1;
    int left = 0;
    int right = static_cast< int >(n) - 1;
    int step = 1;
    int side = static_cast< int >(n);

    while (top <= bottom && left <= right)
    {
      for (int col = left; col <= right; ++col)
      {
        square[top * side + col] -= step;
        ++step;
      }
      ++top;

      for (int row = top; row <= bottom; ++row)
      {
        square[row * side + right] -= step;
        ++step;
      }
      --right;

      if (top <= bottom)
      {
        for (int col = right; col >= left; --col)
        {
          square[bottom * side + col] -= step;
          ++step;
        }
        --bottom;
      }

      if (left <= right)
      {
        for (int row = bottom; row >= top; --row)
        {
          square[row * side + left] -= step;
          ++step;
        }
        ++left;
      }
    }
  }

  void writeMatrix(std::ostream &out, const int *data, size_t rows, size_t cols)
  {
    out << rows << ' ' << cols;
    for (size_t i = 0; i < rows * cols; ++i)
    {
      out << ' ' << data[i];
    }
    out << '\n';
  }

}

int main(int argc, char *argv[])
{
  if (argc != 4)
  {
    std::cerr << "Error: expected 3 arguments: num input output\n";
    return 1;
  }

  long long numValue = 0;
  if (!sumtsov::parseNonNegativeInt(argv[1], numValue) || (numValue != 1 && numValue != 2))
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

  const size_t maxFixedElements = 10000;
  int fixedData[maxFixedElements];
  int *dynamicData = nullptr;
  int *data = nullptr;

  if (numValue == 1)
  {
    if (rows * cols > maxFixedElements)
    {
      std::cerr << "Error: matrix is too large for fixed storage\n";
      return 2;
    }
    data = fixedData;
  }
  else
  {
    dynamicData = new int[rows * cols];
    data = dynamicData;
  }

  if (!sumtsov::readMatrixData(input, rows, cols, data))
  {
    std::cerr << "Error: input file does not contain a valid matrix\n";
    delete[] dynamicData;
    return 2;
  }

  size_t saddleCount = sumtsov::countSaddlePoints(data, rows, cols);

  size_t squareSize = 0;
  int *square = sumtsov::buildTopLeftSquare(data, rows, cols, squareSize);
  sumtsov::transformSpiralTopLeftClockwise(square, squareSize);

  std::ofstream output(argv[3]);
  if (!output)
  {
    std::cerr << "Error: cannot open output file\n";
    delete[] dynamicData;
    delete[] square;
    return 2;
  }

  output << saddleCount << '\n';
  sumtsov::writeMatrix(output, square, squareSize, squareSize);

  delete[] dynamicData;
  delete[] square;

  return 0;
}
