#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>

int main(int argc, char * argv[])
{
  if (argc != 4)
  {
    std::cerr << "Invalid arguments\n";
    return 1;
  }

  if (std::strcmp(argv[1], "1") != 0 && std::strcmp(argv[1], "2") != 0)
  {
    std::cerr << "Invalid mode\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  if (!input)
  {
    std::cerr << "Cannot open input file\n";
    return 2;
  }

  int input_rows = 0;
  int input_cols = 0;
  if(!(input >> input_rows >> input_cols) || input_rows < 0 || input_cols < 0)
  {
    std::cerr << "Invalid matrix\n";
    return 2;
  }

  const size_t rows = input_rows;
  const size_t cols = input_cols;
  if (rows != 0 && cols > std::numeric_limits< size_t >::max() / rows)
  {
    std::cerr << "Invalid matrix dimensions\n";
    return 2;
  }

  const size_t count = rows * cols;
  const size_t max_elements = 10000;
  const bool use_heap = std::strcmp(argv[1], "2") == 0;

  if (!use_heap && count > max_elements)
  {
    std::cerr << "matrix is too large\n";
    return 2;
  }

  if (use_heap && count > std::numeric_limits< size_t >::max() / sizeof(int))
  {
    std::cerr << "Matrix is too large\n";
    return 2;
  }

  int fixed_matrix[max_elements] = {};
  int * heap_matrix = nullptr;
  int * matrix = fixed_matrix;

  if (use_heap && count != 0)
  {
    heap_matrix = static_cast< int * >(std::malloc(count * sizeof(int)));
    if (heap_matrix == nullptr)
    {
      std::cerr << "Not enough memory\n";
      return 2;
    }
    matrix = heap_matrix;
  }

  for (size_t i = 0; i < count; ++i)
  {
    if (!(input >> matrix[i]))
    {
      std::free(heap_matrix);
      std::cerr << "Invalid matrix\n";
      return 2;
    }
  }

  input >> std::ws;
  if (!input.eof() || input.bad())
  {
    std::free(heap_matrix);
    std::cerr << "Invalid matrix\n";
    return 2;
  }

  std::free(heap_matrix);
  return 0;
}
