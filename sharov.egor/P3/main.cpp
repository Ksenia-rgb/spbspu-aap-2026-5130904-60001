#include <climits>
#include <cstring>
#include <fstream>
#include <iostream>

#include "matrix-io.hpp"
#include "matrix.hpp"
#include "variants.hpp"

namespace sharov {
  namespace {
    const int ARGUMENT_COUNT = 3;
    const int SUCCESS_CODE = 0;
    const int ARGUMENT_ERROR_CODE = 1;
    const int DATA_ERROR_CODE = 2;

    int getElementCount(const MatrixSize &size)
    {
      return size.rows * size.columns;
    }

    int writeResults(Matrix &matrix, const char *const outputPath)
    {
      std::ofstream output(outputPath);
      if (!output.is_open()) {
        std::cerr << "output error: cannot open file '" << outputPath << "'\n";
        return DATA_ERROR_CODE;
      }
      output << getMinAntiDiagonalSum(matrix) << '\n';
      addWaveLayerIncrements(matrix);
      writeMatrix(output, matrix);
      if (!output) {
        std::cerr << "output error: cannot write results to '" << outputPath << "'\n";
        return DATA_ERROR_CODE;
      }
      return SUCCESS_CODE;
    }

    int loadElementsAndWrite(std::istream &input, Matrix &matrix, const char *const outputPath)
    {
      const MatrixReadStatus elementsStatus = readMatrixElements(input, matrix);
      if (elementsStatus != MatrixReadStatus::success) {
        std::cerr << getMatrixReadMessage(elementsStatus) << '\n';
        return DATA_ERROR_CODE;
      }
      return writeResults(matrix, outputPath);
    }

    int processMatrix(const char *const inputPath, const char *const outputPath, StorageKind kind)
    {
      std::ifstream input(inputPath);
      if (!input.is_open()) {
        std::cerr << "input error: cannot open file '" << inputPath << "'\n";
        return DATA_ERROR_CODE;
      }
      const bool isFixedStorage = kind == StorageKind::fixed;
      const int maxElementCount = isFixedStorage ? MAX_STACK_ELEMENT_COUNT : INT_MAX;
      MatrixSize size = {0, 0};
      const MatrixReadStatus sizeStatus = readMatrixSize(input, maxElementCount, size);
      if (sizeStatus != MatrixReadStatus::success) {
        std::cerr << getMatrixReadMessage(sizeStatus) << '\n';
        return DATA_ERROR_CODE;
      }
      if (isFixedStorage) {
        FixedMatrixStorage storage;
        Matrix matrix(storage.getData(), size.rows, size.columns);
        return loadElementsAndWrite(input, matrix, outputPath);
      }
      DynamicMatrixStorage storage(getElementCount(size));
      if (!storage.isAllocated()) {
        std::cerr << "memory error: cannot allocate storage for the matrix\n";
        return DATA_ERROR_CODE;
      }
      Matrix matrix(storage.getData(), size.rows, size.columns);
      return loadElementsAndWrite(input, matrix, outputPath);
    }
  }

  int runLab(int argc, char *argv[])
  {
    if (argc != ARGUMENT_COUNT + 1) {
      std::cerr << "usage: " << argv[0] << " num input output\n";
      return ARGUMENT_ERROR_CODE;
    }
    const bool isFixedRequested = std::strcmp(argv[1], "1") == 0;
    const bool isDynamicRequested = std::strcmp(argv[1], "2") == 0;
    if (!isFixedRequested && !isDynamicRequested) {
      std::cerr << "argument error: first parameter must be 1 or 2\n";
      return ARGUMENT_ERROR_CODE;
    }
    const StorageKind kind = isFixedRequested ? StorageKind::fixed : StorageKind::dynamic;
    return processMatrix(argv[2], argv[3], kind);
  }
}

int main(int argc, char *argv[])
{
  return sharov::runLab(argc, argv);
}
