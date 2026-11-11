#include <iostream>
#include <fstream>
#include <cstdlib>
#include "matrix.hpp"

int main(int argc, char** argv)
{
  if (argc != 4)
  {
    std::cerr << "Invalid arguments count\n";
    return 1;
  }

  char* end = nullptr;
  long num = std::strtol(argv[1], &end, 10);
  if (*argv[1] == '\0' || *end != '\0' || (num != 1 && num != 2))
  {
    std::cerr << "Invalid first parameter\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  if (!input.is_open())
  {
    std::cerr << "Cannot open input file\n";
    return 2;
  }

  long long r_in = 0;
  long long c_in = 0;
  if (!(input >> r_in >> c_in) || r_in < 0 || c_in < 0)
  {
    std::cerr << "Invalid matrix dimensions\n";
    return 2;
  }

  size_t rows = static_cast< size_t >(r_in);
  size_t cols = static_cast< size_t >(c_in);

  if (num == 1 && rows * cols > 10000)
  {
    std::cerr << "Matrix size exceeds fixed limit\n";
    return 2;
  }

  int fixed_buf[10000];
  int* dyn_buf = nullptr;
  int* matrix = fixed_buf;

  if (num == 2)
  {
    try
    {
      dyn_buf = new int[rows * cols];
      matrix = dyn_buf;
    }
    catch (const std::bad_alloc&)
    {
      std::cerr << "Memory allocation failed\n";
      return 2;
    }
  }

  if (!readMatrix(input, matrix, rows, cols))
  {
    delete[] dyn_buf;
    std::cerr << "Invalid matrix elements\n";
    return 2;
  }

  std::ofstream output(argv[3]);
  if (!output.is_open())
  {
    delete[] dyn_buf;
    std::cerr << "Cannot open output file\n";
    return 2;
  }

  output << countNzrDig(matrix, rows, cols) << "\n";
  lftBotCnt(matrix, rows, cols);
  printMatrix(output, matrix, rows, cols);
  output << "\n";

  delete[] dyn_buf;
  return 0;
}