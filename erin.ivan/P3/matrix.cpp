#include "matrix.hpp"

#include <iostream>

std::istream & erin::readMtx(std::istream & in, int * mtx, size_t size)
{
  for (size_t i = 0; i < size; ++i)
  {
    if (!(in >> mtx[i]))
    {
      return in;
    }
  }
  return in;
}

void erin::printMtx(std::ostream & out, const int * mtx, size_t rows, size_t cols)
{
  out << rows << " " << cols;
  size_t size = rows * cols;
  for (size_t i = 0; i < size; ++i)
  {
    out << " " << mtx[i];
  }
}
