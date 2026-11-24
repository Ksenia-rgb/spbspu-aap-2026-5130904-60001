#ifndef MATRIX_IO_HPP
#define MATRIX_IO_HPP

#include <istream>
#include <ostream>

#include "matrix.hpp"

namespace sharov {
  enum class MatrixReadStatus {
    success,
    emptyInput,
    notEnoughElements,
    invalidToken,
    valueOverflow,
    negativeDimension,
    elementLimitExceeded,
    extraElements
  };

  struct MatrixSize {
    int rows;
    int columns;
  };

  MatrixReadStatus readMatrixSize(std::istream &input, int maxElementCount, MatrixSize &size);
  MatrixReadStatus readMatrixElements(std::istream &input, Matrix &matrix);
  const char *getMatrixReadMessage(MatrixReadStatus status);
  void writeMatrix(std::ostream &output, const Matrix &matrix);
}

#endif
