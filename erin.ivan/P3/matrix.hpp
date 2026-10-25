#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstddef>
#include <iosfwd>

namespace erin
{
  std::istream & readMtx(std::istream & in, int * mtx, size_t size);
  void printMtx(std::ostream & out, const int * mtx, size_t rows, size_t cols);
  size_t cntLocMin(const int * mtx, size_t rows, size_t cols);
  void lftTopClk(int * mtx, size_t rows, size_t cols);
}

#endif
