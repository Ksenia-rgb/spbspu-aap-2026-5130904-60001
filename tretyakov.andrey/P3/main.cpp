#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstddef>
#include <cstdlib>
#include <cstdlib>
#include <limits>

namespace tretyakov
{
  bool solveLwrTriMtx(const int * matrix, size_t rows, size_t cols)
  {
    size_t k = 0;
    k = std::min(rows, cols);
    if (k == 0)
    {
      return false;
    }
    for (size_t i = 0; i < rows; ++i)
    {
      for (size_t j = i + 1; j < k; ++j)
      {
        if (matrix[i * cols + j] != 0)
        {
          return false;
        }
      }
    }
    return true;
  }

  size_t solveCntLocMax(const int * matrix, size_t rows, size_t cols)
  {
    if (rows < 3 || cols < 3)
    {
      return 0;
    }
    size_t count = 0;
    int currentElement = 0;
    for (size_t i = 1; i < rows - 1; ++i)
    {
      for (size_t j = 1; j < cols - 1; ++j)
      {
        currentElement = matrix[i * cols + j];
        bool isElementMax = true;
        for (int deltaI = -1; deltaI <= 1; ++deltaI)
        {
          for (int deltaJ = -1; deltaJ <= 1; ++deltaJ)
          {
            if (deltaI == 0 && deltaJ == 0)
            {
              continue;
            }
            if (matrix[(i + deltaI) * cols + (j + deltaJ)] >= currentElement)
            {
              isElementMax = false;
              break;
            }
          }
          if (!isElementMax)
          {
            break;
          }
        }
        if (isElementMax)
        {
          ++count;
        }
      }
    }
    return count;
  }
}

int main(int argc, char * argv[])
{
  if (argc < 4)
  {
    std::cerr << "Not enough arguments\n";
    return 1;
  }
  if (argc > 4)
  {
    std::cerr << "Too many arguments\n";
    return 1;
  }
  long num = 0;
  char * endPtr = nullptr;
  num = std::strtol(argv[1], & endPtr, 10);
  if (endPtr == argv[1])
  {
    std::cerr << "First parameter is not a number\n";
    return 1;
  }
  if (*endPtr != '\0')
  {
    std::cerr << "First parameter is not a number\n";
    return 1;
  }
  if (num == std::numeric_limits< long >::max() || num == std::numeric_limits< long >::min())
  {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }
  if (num != 1 && num != 2)
  {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }
  std::ifstream inFile(argv[2]);
  if (!inFile)
  {
    std::cerr << "Can't open input file\n";
    return 2;
  }
  std::ofstream outFile(argv[3]);
  if (!outFile)
  {
    std::cerr << "Can't open output file\n";
    return 2;
  }
  size_t rows = 0;
  size_t cols = 0;
  if (!(inFile >> rows >> cols))
  {
    std::cerr << "Can't read matrix cols and rows or matrix doesn't exist\n";
    return 2;
  }
  if ((rows == 0 && cols != 0) || (rows != 0 && cols == 0))
  {
    std::cerr << "Matrix doesn't exist\n";
    return 2;
  }
  if (rows == 0 && cols == 0)
  {
    outFile << "false " << 0 << "\n";
    return 0;
  }
  int * matrix = nullptr;
  if (num == 1)
  {
    const size_t countElements = 10000;
    int staticMatrix[countElements] = {};
    if (rows > countElements / cols)
    {
      std::cerr << "Matrix is too large\n";
      return 2;
    }
    matrix = staticMatrix;
  }
  else if (num == 2)
  {
    matrix = reinterpret_cast< int * >(malloc(rows * cols * sizeof(int)));
    if (matrix == nullptr)
    {
      std::cerr << "Memory allocation failed\n";
      return 2;
    }
  }
  for (size_t i = 0; i < rows * cols; ++i)
  {
    if (!(inFile >> matrix[i]))
    {
      std::cerr << "Invalid elements\n";
      if (num == 2)
      {
        free(matrix);
      }
      return 2;
    }
  }
  bool lowerTriangleMtx = false;
  size_t counterOfLocalMaximum = 0;
  lowerTriangleMtx = tretyakov::solveLwrTriMtx(matrix, rows, cols);
  counterOfLocalMaximum = tretyakov::solveCntLocMax(matrix, rows, cols);
  outFile << std::boolalpha;
  outFile << lowerTriangleMtx << " " << counterOfLocalMaximum << "\n";
  if (num == 2)
  {
    free(matrix);
  }
  return 0;
}
