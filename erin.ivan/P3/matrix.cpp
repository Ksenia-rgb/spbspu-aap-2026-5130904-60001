#include "matrix.hpp"

#include <iostream>

namespace
{
  bool isLocMin(const int * mtx, size_t cols, size_t r, size_t c)
  {
    int val = mtx[r * cols + c];
    for (size_t i = r - 1; i <= r + 1; ++i)
    {
      for (size_t j = c - 1; j <= c + 1; ++j)
      {
        if ((i != r || j != c) && val >= mtx[i * cols + j])
        {
          return false;
        }
      }
    }
    return true;
  }
}

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

size_t erin::cntLocMin(const int * mtx, size_t rows, size_t cols)
{
  if (rows < 3 || cols < 3)
  {
    return 0;
  }
  size_t cnt = 0;
  for (size_t r = 1; r < rows - 1; ++r)
  {
    for (size_t c = 1; c < cols - 1; ++c)
    {
      if (isLocMin(mtx, cols, r, c))
      {
        ++cnt;
      }
    }
  }
  return cnt;
}
