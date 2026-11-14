#include <algorithm>
#include <limits>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>

namespace degtyarev
{
  constexpr size_t maxStaticSize = 10000;

  size_t countDifCols(const int *arr, size_t rows, size_t cols)
  {
    size_t cnt_cols = 0;
    for (size_t i = 0; i < cols; ++i)
    {
      int flag = 0;
      for (size_t j = i + cols; j < rows * cols; j = j + cols)
      {
        if (arr[j] == arr[j - cols])
        {
          flag = 1;
          break;
        }
      }
      if (flag == 0)
      {
        ++cnt_cols;
      }
    }
    return cnt_cols;
  }

  int maxSumDiag(const int *arr, size_t rows, size_t cols)
  {
    const size_t n = std::min(rows, cols);
    if (n < 2)
    {
      return 0;
    }

    int mx_sumd = std::numeric_limits< int >::min();
    for (size_t i = 1; i < n; ++i)
    {
      int cnt = arr[i];
      int cnt1 = arr[i * cols];
      for (size_t j = 1; j <= n - 1 - i; ++j)
      {
        cnt += arr[i + (cols + 1) * j];
        cnt1 += arr[i * cols + (cols + 1) * j];
      }
      mx_sumd = std::max(mx_sumd, std::max(cnt, cnt1));
    }
    return mx_sumd;
  }
}

int main(int argc, char *argv[])
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
  if (argv[1][1] != '\0' || (*argv[1] != '1' && *argv[1] != '2'))
  {
    std::cerr << "First parameter isnt a number or out of range\n";
    return 1;
  }

  std::ifstream in(argv[2]);
  size_t rows = 0, cols = 0;
  if (!in || !(in >> rows >> cols) || (rows == 0 && cols != 0) || (cols == 0 && rows != 0))
  {
    std::cerr << "Error reading file\n";
    return 2;
  }
  if (cols != 0 && rows > std::numeric_limits< size_t >::max() / sizeof(int) / cols)
  {
    std::cerr << "Matrix is too big\n";
    return 2;
  }
  const size_t size = rows * cols;

  int static_arr[degtyarev::maxStaticSize] = {};
  int *dynamic_arr = nullptr;
  int *arr = nullptr;
  switch (*argv[1])
  {
  case '1':
  {
    if (size > degtyarev::maxStaticSize)
    {
      std::cerr << "Matrix is too big\n";
      return 2;
    }
    arr = static_arr;
    break;
  }

  case '2':
  {
    dynamic_arr = static_cast< int * >(malloc(size * sizeof(int)));
    if (dynamic_arr == nullptr && size != 0)
    {
      std::cerr << "Memory allocation error\n";
      return 2;
    }
    arr = dynamic_arr;
    break;
  }
  }

  for (size_t i = 0; i < size; ++i)
  {
    if (!(in >> arr[i]))
    {
      std::cerr << "Error reading file\n";
      free(dynamic_arr);
      return 2;
    }
  }

  std::ofstream out(argv[3]);
  if (!out)
  {
    std::cerr << "Cannot open output file\n";
    free(dynamic_arr);
    return 2;
  }
  out << degtyarev::countDifCols(arr, rows, cols) << " " << degtyarev::maxSumDiag(arr, rows, cols) << '\n';

  free(dynamic_arr);
  return 0;
}
