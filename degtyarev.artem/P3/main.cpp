#include <iostream>
#include <fstream>

size_t count_difcols(int *arr, size_t rows, size_t cols)
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

size_t count_difcols(int **arr, size_t rows, size_t cols)
{
  size_t cnt_cols = 0;
  for (size_t j = 0; j < cols; ++j)
  {
    int flag = 0;
    for (size_t i = 1; i < rows; ++i)
    {
      if (arr[i][j] == arr[i-1][j])
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

int max_sumdiag(int *arr, size_t rows, size_t cols)
{
  size_t n = std::min(rows, cols);
  rows = cols = n;

  int mx_sumd = 0;
  for (size_t i = 1; i < cols; ++i)
  {
    int cnt = arr[i];
    int cnt1 = arr[i + (cols - 1) * i];
    for (size_t j = 1; j <= cols - 1 - i; ++j)
    {
      cnt += arr[i + (cols + 1) * j];
      cnt1 += arr[i + (cols + 1) * j + (cols - 1) * i];
    }
    mx_sumd = std::max(mx_sumd, std::max(cnt, cnt1));
  }
  return mx_sumd;
}

int max_sumdiag(int **arr, size_t rows, size_t cols)
{
  size_t n = std::min(rows, cols);
  rows = cols = n;

  int mx_sumd = 0;
  if (cols == 0)
  {
    return 0;
  }

  size_t kdiag = cols - 1;
  for (size_t i = 0; i < kdiag; ++i)
  {
    int cnt = arr[rows-1][cols-i-2];
    int cnt1 = arr[cols-i-2][rows-1];
    for (size_t j = 0; j < cols-i-2; ++j)
    {
      cnt += arr[rows-2-j][cols-i-3-j];
      cnt1 += arr[cols-i-3-j][rows-2-j];
    }
    mx_sumd = std::max(mx_sumd, std::max(cnt, cnt1));
  }
  return mx_sumd;
}

int main(int argc,char *argv[])
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

  switch (*argv[1])
  {
  case '1':
  {
    int arr[10000];

    std::ifstream in(argv[2]);
    size_t rows, cols;
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

    size_t cnt_diffcols = count_difcols(arr, rows, cols);
    int maxdiag = max_sumdiag(arr, rows, cols);

    std::ofstream out(argv[3]);
    out << cnt_diffcols << " " << maxdiag << '\n';
    return 0;
  }

  case '2':
  {
    std::ifstream in(argv[2]);
    int rows, cols;
    if (!(in >> rows >> cols) || (rows <= 0 && cols != 0) || (cols <= 0 && rows != 0))
    {
      std::cerr << "Error reading file\n";
      return 2;
    }

    int  **arr = (int **)malloc(rows * sizeof(int*));
    for (size_t i = 0; i < rows; ++i)
    {
      arr[i] = (int *)malloc(cols * sizeof(int));
    }

    for (size_t i = 0; i < rows; ++i)
    {
      for (size_t j = 0; j < cols; ++j)
      {
        if (!(in >> arr[i][j]))
        {
          std::cerr << "Error reading file\n";
          return 2;
        }
      }
    }

    size_t cnt_diffcols = count_difcols(arr, rows, cols);
    int maxdiag = max_sumdiag(arr, rows, cols);

    std::ofstream out(argv[3]);
    out << cnt_diffcols << " " << maxdiag << '\n';
    return 0;
  }

  default:
  {
    std::cout << "First parameter isnt a number or out of range\n";
    return 1;
  }
  }
}
