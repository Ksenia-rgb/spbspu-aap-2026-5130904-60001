#include "matrix.hpp"

#include <iostream>

namespace
{
  bool isStrictLocalMinimum(const int * matrix, size_t cols, size_t r, size_t c)
  {
    const int current = matrix[r * cols + c];
    for (int dr = -1; dr <= 1; ++dr)
    {
      for (int dc = -1; dc <= 1; ++dc)
      {
        if (dr == 0 && dc == 0)
        {
          continue;
        }
        const size_t nr = static_cast< size_t >(static_cast< ptrdiff_t >(r) + dr);
        const size_t nc = static_cast< size_t >(static_cast< ptrdiff_t >(c) + dc);
        if (current >= matrix[nr * cols + nc])
        {
          return false;
        }
      }
    }
    return true;
  }
}

std::istream & erin::readMatrix(std::istream & in, int * matrix, size_t rows, size_t cols)
{
  const size_t total = rows * cols;
  for (size_t i = 0; i < total; ++i)
  {
    if (!(in >> matrix[i]))
    {
      return in;
    }
  }
  return in;
}

size_t erin::countLocalMinima(const int * matrix, size_t rows, size_t cols)
{
  if (rows < 3 || cols < 3)
  {
    return 0;
  }
  size_t count = 0;
  for (size_t r = 1; r < rows - 1; ++r)
  {
    for (size_t c = 1; c < cols - 1; ++c)
    {
      if (isStrictLocalMinimum(matrix, cols, r, c))
      {
        ++count;
      }
    }
  }
  return count;
}

void erin::transformLeftTopClockwise(int * matrix, size_t rows, size_t cols)
{
  if (rows == 0 || cols == 0)
  {
    return;
  }
  size_t top = 0;
  size_t bottom = rows - 1;
  size_t left = 0;
  size_t right = cols - 1;
  const size_t total = rows * cols;
  size_t visited = 0;
  int decrement = 1;

  while (visited < total)
  {
    for (size_t c = left; c <= right && visited < total; ++c)
    {
      matrix[top * cols + c] -= decrement;
      ++decrement;
      ++visited;
    }
    ++top;

    for (size_t r = top; r <= bottom && visited < total; ++r)
    {
      matrix[r * cols + right] -= decrement;
      ++decrement;
      ++visited;
    }
    if (right > 0)
    {
      --right;
    }

    for (size_t offset = 0; visited < total && offset <= right - left; ++offset)
    {
      const size_t c = right - offset;
      matrix[bottom * cols + c] -= decrement;
      ++decrement;
      ++visited;
    }
    if (bottom > 0)
    {
      --bottom;
    }

    for (size_t offset = 0; visited < total && offset <= bottom - top; ++offset)
    {
      const size_t r = bottom - offset;
      matrix[r * cols + left] -= decrement;
      ++decrement;
      ++visited;
    }
    ++left;
  }
}

void erin::writeMatrix(std::ostream & out, const int * matrix, size_t rows, size_t cols)
{
  out << rows << " " << cols;
  const size_t total = rows * cols;
  for (size_t i = 0; i < total; ++i)
  {
    out << " " << matrix[i];
  }
}
