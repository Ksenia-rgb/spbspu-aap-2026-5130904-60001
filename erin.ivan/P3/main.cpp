#include <cstdlib>
#include <fstream>
#include <iostream>
#include "matrix.hpp"

int main(int argc, char ** argv)
{
  if (argc != 4)
  {
    std::cerr << "Wrong args count\n";
    return 1;
  }

  char * end = nullptr;
  long num = std::strtol(argv[1], &end, 10);
  if (argv[1][0] == '\0' || *end != '\0' || (num != 1 && num != 2))
  {
    std::cerr << "Wrong first arg\n";
    return 1;
  }

  std::ifstream in(argv[2]);
  if (!in.is_open())
  {
    std::cerr << "Cannot open input\n";
    return 2;
  }

  size_t rows = 0;
  size_t cols = 0;
  if (!(in >> rows >> cols))
  {
    std::cerr << "Cannot read size\n";
    return 2;
  }
  if ((rows == 0 && cols != 0) || (rows != 0 && cols == 0))
  {
    std::cerr << "Wrong matrix size\n";
    return 2;
  }

  size_t size = rows * cols;
  if (num == 1 && size > 10000)
  {
    std::cerr << "Size too big\n";
    return 2;
  }

  int fixed_arr[10000] = {};
  int * dyn_arr = nullptr;
  int * mtx = fixed_arr;

  if (num == 2 && size > 0)
  {
    try
    {
      dyn_arr = new int[size];
    }
    catch (const std::bad_alloc &)
    {
      std::cerr << "Bad alloc\n";
      return 2;
    }
    mtx = dyn_arr;
  }

  if (!erin::readMtx(in, mtx, size))
  {
    delete[] dyn_arr;
    std::cerr << "Read fail\n";
    return 2;
  }

  std::ofstream out(argv[3]);
  if (!out.is_open())
  {
    delete[] dyn_arr;
    std::cerr << "Cannot open output\n";
    return 2;
  }

  erin::printMtx(out, mtx, rows, cols);
  out << "\n";

  delete[] dyn_arr;
  return 0;
}
