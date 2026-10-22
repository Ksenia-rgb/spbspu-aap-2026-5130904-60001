#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstddef>
#include <iosfwd>

namespace erin
{
  std::istream & readMatrix(std::istream & in, int * matrix, size_t rows, size_t cols);
  size_t countLocalMinima(const int * matrix, size_t rows, size_t cols);
  void transformLeftTopClockwise(int * matrix, size_t rows, size_t cols);
  void writeMatrix(std::ostream & out, const int * matrix, size_t rows, size_t cols);
}

#endif
