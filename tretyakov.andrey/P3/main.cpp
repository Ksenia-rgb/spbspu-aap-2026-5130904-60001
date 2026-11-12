#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstddef>
#include <cstdlib>
#include <limits>

namespace tretyakov
{
  bool solveLwrTriMtx(const int * matrix, size_t rows, size_t cols)
  {
    const size_t k = std::min(rows, cols);
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
    int current_element = 0;
    for (size_t i = 1; i < rows - 1; ++i)
    {
      for (size_t j = 1; j < cols - 1; ++j)
      {
        current_element = matrix[i * cols + j];
        bool is_element_max = true;
        for (int delta_i = -1; delta_i <= 1; ++delta_i)
        {
          for (int delta_j = -1; delta_j <= 1; ++delta_j)
          {
            if (delta_i == 0 && delta_j == 0)
            {
              continue;
            }
            if (matrix[(i + delta_i) * cols + (j + delta_j)] >= current_element)
            {
              is_element_max = false;
              break;
            }
          }
          if (!is_element_max)
          {
            break;
          }
        }
        if (is_element_max)
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
  char * end_ptr = nullptr;
  const long num = std::strtol(argv[1], &end_ptr, 10);
  if (end_ptr == argv[1])
  {
    std::cerr << "First parameter is not a number\n";
    return 1;
  }
  if (*end_ptr != '\0')
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
  std::ifstream in_file(argv[2]);
  if (!in_file)
  {
    std::cerr << "Can't open input file\n";
    return 2;
  }
  std::ofstream out_file(argv[3]);
  if (!out_file)
  {
    std::cerr << "Can't open output file\n";
    return 2;
  }
  size_t rows = 0;
  size_t cols = 0;
  if (!(in_file >> rows >> cols))
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
    out_file << "false " << 0 << "\n";
    return 0;
  }
  int * matrix = nullptr;
  int * dynamic_matrix = nullptr;
  const size_t count_elements = 10000;
  int fix_matrix[count_elements] = {};
  if (num == 1)
  {
    if (rows > count_elements / cols)
    {
      std::cerr << "Matrix is too large\n";
      return 2;
    }
    matrix = fix_matrix;
  }
  else if (num == 2)
  {
    dynamic_matrix = reinterpret_cast< int * >(malloc(rows * cols * sizeof(int)));
    if (dynamic_matrix == nullptr)
    {
      std::cerr << "Memory allocation failed\n";
      return 2;
    }
    matrix = dynamic_matrix;
  }
  for (size_t i = 0; i < rows * cols; ++i)
  {
    if (!(in_file >> matrix[i]))
    {
      std::cerr << "Invalid elements\n";
      free(dynamic_matrix);
      return 2;
    }
  }
  const bool lower_triangle_mtx = tretyakov::solveLwrTriMtx(matrix, rows, cols);
  const size_t counter_of_local_maximum = tretyakov::solveCntLocMax(matrix, rows, cols);
  out_file << std::boolalpha;
  out_file << lower_triangle_mtx << " " << counter_of_local_maximum << "\n";
  free(dynamic_matrix);
  return 0;
}
