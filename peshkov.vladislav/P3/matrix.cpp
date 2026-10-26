#include "matrix.hpp"
#include <iostream>

std::istream& readMatrix(std::istream& in, int* m, size_t r, size_t c)
{
  for (size_t i = 0; i < r * c; ++i)
  {
    in >> m[i];
  }
  return in;
}

void printMatrix(std::ostream& out, const int* m, size_t r, size_t c)
{
  out << r << " " << c;
  for (size_t i = 0; i < r * c; ++i)
  {
    out << " " << m[i];
  }
}

size_t countNzrDig(const int* m, size_t r, size_t c)
{
  size_t n = (r < c) ? r : c;
  if (n <= 1)
  {
    return 0;
  }
  size_t count = 0;
  for (size_t d = 1; d < n; ++d)
  {
    bool upper_nz = true;
    bool lower_nz = true;
    for (size_t i = 0; i < n - d; ++i)
    {
      if (m[i * c + (i + d)] == 0)
      {
        upper_nz = false;
      }
      if (m[(i + d) * c + i] == 0)
      {
        lower_nz = false;
      }
    }
    if (upper_nz)
    {
      ++count;
    }
    if (lower_nz)
    {
      ++count;
    }
  }
  return count;
}

void lftBotCnt(int* m, size_t r, size_t c)
{
  if (r == 0 || c == 0)
  {
    return;
  }
  size_t top = 0;
  size_t bot = r - 1;
  size_t left = 0;
  size_t right = c - 1;
  int inc = 1;

  while (top <= bot && left <= right)
  {
    for (size_t j = left; j <= right; ++j)
    {
      m[bot * c + j] += inc++;
    }
    if (top == bot)
    {
      break;
    }
    --bot;

    for (size_t i = bot + 1; i-- > top;)
    {
      m[i * c + right] += inc++;
    }
    if (left == right)
    {
      break;
    }
    --right;

    for (size_t j = right + 1; j-- > left;)
    {
      m[top * c + j] += inc++;
    }
    if (top == bot)
    {
      break;
    }
    ++top;

    for (size_t i = top; i <= bot; ++i)
    {
      m[i * c + left] += inc++;
    }
    if (left == right)
    {
      break;
    }
    ++left;
  }
}