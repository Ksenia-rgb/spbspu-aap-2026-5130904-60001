#include "variants.hpp"

#include "matrix.hpp"

namespace sharov {
  long long getMinAntiDiagonalSum(const Matrix &matrix)
  {
    const int rows = matrix.getRows();
    const int columns = matrix.getCols();
    const int size = rows < columns ? rows : columns;
    if (size == 0) {
      return 0;
    }
    long long minimum = 0;
    bool hasValue = false;
    const int diagonalCount = 2 * size - 1;
    for (int diagonalIndex = 0; diagonalIndex < diagonalCount; ++diagonalIndex) {
      long long sum = 0;
      for (int row = 0; row < size; ++row) {
        const int column = diagonalIndex - row;
        if (column >= 0 && column < size) {
          sum += matrix.at(row, column);
        }
      }
      if (!hasValue || sum < minimum) {
        minimum = sum;
        hasValue = true;
      }
    }
    return minimum;
  }

  void addWaveLayerIncrements(Matrix &matrix)
  {
    const int rows = matrix.getRows();
    const int columns = matrix.getCols();
    for (int row = 0; row < rows; ++row) {
      const int oppositeRow = rows - 1 - row;
      for (int column = 0; column < columns; ++column) {
        const int oppositeColumn = columns - 1 - column;
        int layer = row < column ? row : column;
        if (oppositeRow < layer) {
          layer = oppositeRow;
        }
        if (oppositeColumn < layer) {
          layer = oppositeColumn;
        }
        matrix.at(row, column) += layer + 1;
      }
    }
  }
}
