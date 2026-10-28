#include <algorithm>
#include <limits>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>

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

size_t countDifCols(const int *const *arr, size_t rows, size_t cols)
{
  size_t cnt_cols = 0;
  for (size_t j = 0; j < cols; ++j)
  {
    int flag = 0;
    for (size_t i = 1; i < rows; ++i)
    {
      if (arr[i][j] == arr[i - 1][j])
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

  int mx_sumd = std::numeric_limits <int>::min();
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

int maxSumDiag(const int *const *arr, size_t rows, size_t cols)
{
  const size_t n = std::min(rows, cols);
  if (n < 2)
  {
    return 0;
  }

  int mx_sumd = std::numeric_limits <int>::min();
  const size_t kdiag = n - 1;
  for (size_t i = 0; i < kdiag; ++i)
  {
    int cnt = arr[n - 1][n - i - 2];
    int cnt1 = arr[n - i - 2][n - 1];
    for (size_t j = 0; j < n - i - 2; ++j)
    {
      cnt += arr[n - 2 - j][n - i - 3 - j];
      cnt1 += arr[n - i - 3 - j][n - 2 - j];
    }
    mx_sumd = std::max(mx_sumd, std::max(cnt, cnt1));
  }
  return mx_sumd;
}

void freeMatrix(int **arr, size_t rows)
{
  for (size_t i = 0; i < rows; ++i)
  {
    free(arr[i]);
  }
  free(arr);
}

int main(int argc, char *argv[])
{
  if (argc < 4)
  {
    std::cerr << "Not enough arguments";
    return 1;
  }
  if (argc > 4)
  {
    std::cerr << "Too many arguments";
    return 1;
  }
  if (argv[1][1] != '\0')
  {
    std::cerr << "First parameter isnt a number or out of range\n";
    return 1;
  }

  switch (*argv[1])
  {
  case '1':
  {
    int arr[maxStaticSize];

    std::ifstream in(argv[2]);
    size_t rows = 0, cols = 0;
    if (!(in >> rows >> cols) || (rows <= 0 && cols != 0) || (cols <= 0 && rows != 0))
    {
      std::cerr << "Error reading file\n";
      return 2;
    }

    for (size_t i = 0; i < rows * cols; ++i)
    {
      if (!(in >> arr[i]))
      {
        std::cerr << "Error reading file\n";
        return 2;
      }
    }

    std::ofstream out(argv[3]);
    out << countDifCols(arr, rows, cols) << " " << maxSumDiag(arr, rows, cols) << '\n';
    return 0;
  }

  case '2':
  {
    std::ifstream in(argv[2]);
    size_t rows = 0, cols = 0;
    if (!(in >> rows >> cols) || (rows <= 0 && cols != 0) || (cols <= 0 && rows != 0))
    {
      std::cerr << "Error reading file\n";
      return 2;
    }

    int **const arr = static_cast< int ** >(malloc(rows * sizeof(int *)));
    for (size_t i = 0; i < rows; ++i)
    {
      arr[i] = static_cast< int * >(malloc(cols * sizeof(int)));
    }

    for (size_t i = 0; i < rows; ++i)
    {
      for (size_t j = 0; j < cols; ++j)
      {
        if (!(in >> arr[i][j]))
        {
          std::cerr << "Error reading file\n";
          freeMatrix(arr, rows);
          return 2;
        }
      }
    }

    std::ofstream out(argv[3]);
    out << countDifCols(arr, rows, cols) << " " << maxSumDiag(arr, rows, cols) << '\n';

    freeMatrix(arr, rows);
    return 0;
  }

  default:
  {
    std::cerr << "First parameter isnt a number or out of range\n";
    return 1;
  }
  }
}
