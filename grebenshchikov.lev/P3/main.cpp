#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstddef>

namespace grebenshchikov
{
  size_t cntColNsm(const int *mtx, size_t rows, size_t cols)
  {
    size_t count = 0;
    for (size_t i = 0; i < cols; ++i)
    {
      int flag = 0;
      for (size_t j = 1; j < rows; ++j)
      {
        const int preel = mtx[(j - 1) * cols + i];
        if (mtx[j * cols + i] == preel)
        {
          flag = 1;
          break;
        }
      }
      if (flag == 0)
      {
        ++count;
      }
    }
    return count;
  }

  bool uppTriMtx(const int *mtx, size_t rows, size_t cols)
  {
    if (rows == 0 || cols == 0)
    {
      return false;
    }
    for (size_t i = 0; i < rows; ++i)
    {
      for (size_t j = 0; j < cols; ++j)
      {
        if (i > j && mtx[i * cols + j] != 0)
        {
          return false;
        }
      }
    }
    return true;
  }
}

int main(int argc, char *argv[])
{
  const int argsCount = 4;
  const size_t inputArg = 2;
  const size_t outputArg = 3;
  const int fileError = 2;

  if (argc < argsCount)
  {
    std::cerr << "Not enough arguments";
    return 1;
  }
  if (argc > argsCount)
  {
    std::cerr << "Too many arguments";
    return 1;
  }
  if (argv[1][1] != '\0' || (argv[1][0] != '1' && argv[1][0] != '2'))
  {
    std::cerr << "First parameter isnt a number or out of range\n";
    return 1;
  }

  std::ifstream in(argv[inputArg]);
  if (!in.is_open())
  {
    std::cerr << "Cannot open input file\n";
    return fileError;
  }
  int rowsIn = 0;
  int colsIn = 0;
  if (!(in >> rowsIn >> colsIn) || rowsIn < 0 || colsIn < 0)
  {
    std::cerr << "Error reading file\n";
    return fileError;
  }
  const size_t rows = rowsIn;
  const size_t cols = colsIn;

  const size_t kmax = 10000;
  int staticMtx[kmax] = {};
  int *dynamicMtx = nullptr;
  int *mtx = nullptr;
  switch (*argv[1])
  {
  case '1':
    if (cols != 0 && rows > kmax / cols)
    {
      std::cerr << "Matrix size exceeds maximum allowed size\n";
      return fileError;
    }
    mtx = staticMtx;
    break;
  case '2':
    dynamicMtx = static_cast< int * >(std::malloc(rows * cols * sizeof(int)));
    if (dynamicMtx == nullptr && rows * cols > 0)
    {
      std::cerr << "Not enough memory\n";
      return fileError;
    }
    mtx = dynamicMtx;
    break;
  }

  for (size_t i = 0; i < rows * cols; ++i)
  {
    if (!(in >> mtx[i]))
    {
      std::cerr << "Error reading file\n";
      std::free(dynamicMtx);
      return fileError;
    }
  }

  std::ofstream out(argv[outputArg]);
  if (!out.is_open())
  {
    std::cerr << "Cannot open output file\n";
    std::free(dynamicMtx);
    return fileError;
  }
  out << std::boolalpha << grebenshchikov::uppTriMtx(mtx, rows, cols) << '\n';
  out << grebenshchikov::cntColNsm(mtx, rows, cols) << '\n';
  std::free(dynamicMtx);
  return 0;
}
