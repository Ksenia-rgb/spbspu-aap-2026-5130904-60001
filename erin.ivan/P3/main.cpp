#include <cstdlib>
#include <fstream>
#include <iostream>
#include "matrix.hpp"

int main(int argc, char ** argv)
{
  if (argc != 4)
  {
    std::cerr << "Invalid number of arguments\n";
    return 1;
  }

  char * endptr = nullptr;
  const long mode = std::strtol(argv[1], &endptr, 10);
  if (argv[1][0] == '\0' || *endptr != '\0' || (mode != 1 && mode != 2))
  {
    std::cerr << "First parameter is invalid\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  if (!input.is_open())
  {
    std::cerr << "Cannot open input file\n";
    return 2;
  }

  long long raw_rows = 0;
  long long raw_cols = 0;
  if (!(input >> raw_rows >> raw_cols) || raw_rows < 0 || raw_cols < 0)
  {
    std::cerr << "Invalid matrix dimensions\n";
    return 2;
  }
  if ((raw_rows == 0 && raw_cols != 0) || (raw_rows != 0 && raw_cols == 0))
  {
    std::cerr << "Invalid zero dimensions\n";
    return 2;
  }

  const size_t rows = static_cast< size_t >(raw_rows);
  const size_t cols = static_cast< size_t >(raw_cols);
  const size_t total = rows * cols;
  const size_t max_fixed_size = 10000;

  if (mode == 1 && total > max_fixed_size)
  {
    std::cerr << "Matrix size exceeds fixed buffer\n";
    return 2;
  }

  int fixed_buffer[max_fixed_size] = {};
  int * dynamic_buffer = nullptr;
  int * matrix = fixed_buffer;

  if (mode == 2 && total > 0)
  {
    try
    {
      dynamic_buffer = new int[total];
    }
    catch (const std::bad_alloc &)
    {
      std::cerr << "Memory allocation failed\n";
      return 2;
    }
    matrix = dynamic_buffer;
  }

  if (!erin::readMatrix(input, matrix, rows, cols))
  {
    delete[] dynamic_buffer;
    std::cerr << "Failed to read matrix elements\n";
    return 2;
  }

  std::ofstream output(argv[3]);
  if (!output.is_open())
  {
    delete[] dynamic_buffer;
    std::cerr << "Cannot open output file\n";
    return 2;
  }

  const size_t loc_min_cnt = erin::countLocalMinima(matrix, rows, cols);
  erin::transformLeftTopClockwise(matrix, rows, cols);

  output << loc_min_cnt << "\n";
  erin::writeMatrix(output, matrix, rows, cols);
  output << "\n";

  delete[] dynamic_buffer;
  return 0;
}
