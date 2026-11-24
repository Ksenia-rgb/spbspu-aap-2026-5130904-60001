#include <climits>
#include <cstddef>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include "matrix-io.hpp"
#include "matrix.hpp"
#include "variants.hpp"

namespace {
  constexpr unsigned int RANDOM_SEED = 20261123U;
  constexpr int RANDOM_CASE_COUNT = 200;
  constexpr int ROUND_TRIP_CASE_COUNT = 100;
  constexpr int MIN_DIMENSION = 1;
  constexpr int MAX_DIMENSION = 6;
  constexpr int MIN_ELEMENT = -1000;
  constexpr int MAX_ELEMENT = 1000;

  int checksCount = 0;
  int failuresCount = 0;

  void checkLongLong(long long expected, long long actual, const std::string &label)
  {
    ++checksCount;
    if (expected != actual) {
      ++failuresCount;
      std::cout << "FAIL " << label << ": expected " << expected << ", actual " << actual << '\n';
    }
  }

  void checkString(const std::string &expected, const std::string &actual, const std::string &label)
  {
    ++checksCount;
    if (expected != actual) {
      ++failuresCount;
      std::cout << "FAIL " << label << ": expected \"" << expected << "\", actual \"" << actual << "\"\n";
    }
  }

  void checkStatus(sharov::MatrixReadStatus expected, sharov::MatrixReadStatus actual, const std::string &label)
  {
    ++checksCount;
    if (expected != actual) {
      ++failuresCount;
      std::cout << "FAIL " << label << ": expected status " << static_cast< int >(expected) << ", actual "
                << static_cast< int >(actual) << '\n';
    }
  }

  sharov::MatrixReadStatus readMatrixText(
      const std::string &text, int maxElementCount, std::vector< long long > &values, sharov::MatrixSize &size)
  {
    std::istringstream input(text);
    const sharov::MatrixReadStatus sizeStatus = sharov::readMatrixSize(input, maxElementCount, size);
    if (sizeStatus != sharov::MatrixReadStatus::success) {
      return sizeStatus;
    }
    const int elementCount = size.rows * size.columns;
    values.assign(static_cast< std::size_t >(elementCount == 0 ? 1 : elementCount), 0);
    sharov::Matrix matrix(values.data(), size.rows, size.columns);
    return sharov::readMatrixElements(input, matrix);
  }

  long long bruteMinAntiDiagonalSum(const std::vector< long long > &values, int rows, int columns)
  {
    const int size = rows < columns ? rows : columns;
    if (size == 0) {
      return 0;
    }
    const int diagonalCount = 2 * size - 1;
    std::vector< long long > sums(static_cast< std::size_t >(diagonalCount), 0);
    for (int row = 0; row < size; ++row) {
      for (int column = 0; column < size; ++column) {
        const std::size_t index = static_cast< std::size_t >(row * columns + column);
        sums[static_cast< std::size_t >(row + column)] += values[index];
      }
    }
    long long minimum = sums[0];
    for (std::size_t index = 1; index < sums.size(); ++index) {
      if (sums[index] < minimum) {
        minimum = sums[index];
      }
    }
    return minimum;
  }

  void testMatrixAccess()
  {
    std::vector< long long > data = {1, 2, 3, 4, 5, 6};
    sharov::Matrix matrix(data.data(), 2, 3);
    checkLongLong(2, matrix.getRows(), "access: rows");
    checkLongLong(3, matrix.getCols(), "access: columns");
    checkLongLong(6, matrix.getElementCount(), "access: element count");
    checkLongLong(3, matrix.at(0, 2), "access: element (0, 2)");
    checkLongLong(4, matrix.at(1, 0), "access: element (1, 0)");
    matrix.at(1, 2) = 42;
    checkLongLong(42, data[5], "access: write through at()");
    const sharov::Matrix &readOnlyMatrix = matrix;
    checkLongLong(42, readOnlyMatrix.at(1, 2), "access: const element (1, 2)");
    checkLongLong(42, readOnlyMatrix.getData()[5], "access: const data");
  }

  void testMinAntiDiagonal()
  {
    std::vector< long long > data2x2 = {1, 2, 3, 4};
    const sharov::Matrix matrix2x2(data2x2.data(), 2, 2);
    checkLongLong(1, sharov::getMinAntiDiagonalSum(matrix2x2), "MIN-SUM: 2x2 1 2 3 4");

    std::vector< long long > data3x3 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    const sharov::Matrix matrix3x3(data3x3.data(), 3, 3);
    checkLongLong(1, sharov::getMinAntiDiagonalSum(matrix3x3), "MIN-SUM: 3x3 1..9");

    std::vector< long long > data2x3 = {1, 2, 3, 4, 5, 6};
    const sharov::Matrix matrix2x3(data2x3.data(), 2, 3);
    checkLongLong(1, sharov::getMinAntiDiagonalSum(matrix2x3), "MIN-SUM: 2x3 top-left square");

    std::vector< long long > data3x2 = {9, 8, 1, 2, 3, 4};
    const sharov::Matrix matrix3x2(data3x2.data(), 3, 2);
    checkLongLong(2, sharov::getMinAntiDiagonalSum(matrix3x2), "MIN-SUM: 3x2 top-left square");

    std::vector< long long > dataNegative = {-1, -2, -3, -4, -5, -6, -7, -8, -9};
    const sharov::Matrix matrixNegative(dataNegative.data(), 3, 3);
    checkLongLong(-15, sharov::getMinAntiDiagonalSum(matrixNegative), "MIN-SUM: 3x3 negative");

    std::vector< long long > dataSingle = {-7};
    const sharov::Matrix matrixSingle(dataSingle.data(), 1, 1);
    checkLongLong(-7, sharov::getMinAntiDiagonalSum(matrixSingle), "MIN-SUM: 1x1");

    std::vector< long long > dataRow = {5, 4, 3, 2, 1};
    const sharov::Matrix matrixRow(dataRow.data(), 1, 5);
    checkLongLong(5, sharov::getMinAntiDiagonalSum(matrixRow), "MIN-SUM: 1x5");

    std::vector< long long > dataColumn = {5, 4, 3, 2, 1};
    const sharov::Matrix matrixColumn(dataColumn.data(), 5, 1);
    checkLongLong(5, sharov::getMinAntiDiagonalSum(matrixColumn), "MIN-SUM: 5x1");

    std::vector< long long > data4x4 = {-1, 2, -3, 4, 5, -6, 7, -8, -9, 10, -11, 12, 13, -14, 15, -16};
    const sharov::Matrix matrix4x4(data4x4.data(), 4, 4);
    checkLongLong(-33, sharov::getMinAntiDiagonalSum(matrix4x4), "MIN-SUM: 4x4 mixed");

    std::vector< long long > emptyData;
    const sharov::Matrix emptyMatrix(emptyData.data(), 0, 0);
    checkLongLong(0, sharov::getMinAntiDiagonalSum(emptyMatrix), "MIN-SUM: 0x0");
  }

  std::string waveResult(const std::vector< long long > &values, int rows, int columns)
  {
    std::vector< long long > storage = values;
    sharov::Matrix matrix(storage.data(), rows, columns);
    sharov::addWaveLayerIncrements(matrix);
    std::ostringstream output;
    sharov::writeMatrix(output, matrix);
    return output.str();
  }

  void testWaveIncrements()
  {
    const std::vector< long long > data3x3 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    checkString("3 3 2 3 4 5 7 7 8 9 10\n", waveResult(data3x3, 3, 3), "FLL: 3x3 1..9");

    const std::vector< long long > data2x2 = {1, 2, 3, 4};
    checkString("2 2 2 3 4 5\n", waveResult(data2x2, 2, 2), "FLL: 2x2 1 2 3 4");

    const std::vector< long long > data2x3 = {1, 2, 3, 4, 5, 6};
    checkString("2 3 2 3 4 5 6 7\n", waveResult(data2x3, 2, 3), "FLL: 2x3");

    const std::vector< long long > dataNegative = {-1, -2, -3, -4};
    checkString("2 2 0 -1 -2 -3\n", waveResult(dataNegative, 2, 2), "FLL: 2x2 negative");

    const std::vector< long long > dataSingle = {10};
    checkString("1 1 11\n", waveResult(dataSingle, 1, 1), "FLL: 1x1");

    const std::vector< long long > zeros4x4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    checkString("4 4 1 1 1 1 1 2 2 1 1 2 2 1 1 1 1 1\n", waveResult(zeros4x4, 4, 4), "FLL: 4x4 zeros");

    const std::vector< long long > zeros5x5
        = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    checkString(
        "5 5 1 1 1 1 1 1 2 2 2 1 1 2 3 2 1 1 2 2 2 1 1 1 1 1 1\n", waveResult(zeros5x5, 5, 5), "FLL: 5x5 zeros");

    const std::vector< long long > zeros3x5 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    checkString("3 5 1 1 1 1 1 1 2 2 2 1 1 1 1 1 1\n", waveResult(zeros3x5, 3, 5), "FLL: 3x5 zeros");

    const std::vector< long long > zeros1x4 = {0, 0, 0, 0};
    checkString("1 4 1 1 1 1\n", waveResult(zeros1x4, 1, 4), "FLL: 1x4 zeros");

    const std::vector< long long > emptyData;
    checkString("0 0\n", waveResult(emptyData, 0, 0), "FLL: 0x0");
  }

  void testStorage()
  {
    sharov::FixedMatrixStorage fixedStorage;
    checkLongLong(sharov::MAX_STACK_ELEMENT_COUNT, fixedStorage.getCapacity(), "storage: fixed capacity");
    fixedStorage.getData()[0] = 7;
    checkLongLong(7, fixedStorage.getData()[0], "storage: fixed data write");
    const sharov::FixedMatrixStorage &readOnlyFixedStorage = fixedStorage;
    checkLongLong(7, readOnlyFixedStorage.getData()[0], "storage: fixed const data");

    sharov::DynamicMatrixStorage dynamicStorage(5);
    checkLongLong(5, dynamicStorage.getCapacity(), "storage: dynamic capacity");
    checkLongLong(1, dynamicStorage.isAllocated() ? 1 : 0, "storage: dynamic is allocated");
    long long *const dynamicData = dynamicStorage.getData();
    for (int index = 0; index < 5; ++index) {
      dynamicData[index] = index * 2;
    }
    const sharov::DynamicMatrixStorage &readOnlyDynamicStorage = dynamicStorage;
    checkLongLong(8, readOnlyDynamicStorage.getData()[4], "storage: dynamic data write");

    const sharov::DynamicMatrixStorage emptyStorage(0);
    checkLongLong(0, emptyStorage.getCapacity(), "storage: empty dynamic capacity");
    checkLongLong(1, emptyStorage.isAllocated() ? 1 : 0, "storage: empty dynamic is allocated");
  }

  void testReading()
  {
    std::vector< long long > values;
    sharov::MatrixSize size = {0, 0};
    checkStatus(sharov::MatrixReadStatus::success,
        readMatrixText("3 3 1 2 3 4 5 6 7 8 9", sharov::MAX_STACK_ELEMENT_COUNT, values, size), "read: valid matrix");
    checkLongLong(3, size.rows, "read: rows");
    checkLongLong(3, size.columns, "read: columns");
    checkLongLong(9, static_cast< long long >(values.size()), "read: stored element count");
    checkLongLong(7, values[6], "read: stored element value");

    checkStatus(sharov::MatrixReadStatus::success,
        readMatrixText("2 3\n1 2 3\n4 5 6\n", sharov::MAX_STACK_ELEMENT_COUNT, values, size),
        "read: matrix with line breaks");
    checkLongLong(6, static_cast< long long >(values.size()), "read: line break element count");

    checkStatus(sharov::MatrixReadStatus::success,
        readMatrixText("2 2 1 2 3 4   \n\n", sharov::MAX_STACK_ELEMENT_COUNT, values, size),
        "read: trailing whitespace");

    checkStatus(sharov::MatrixReadStatus::success,
        readMatrixText("+2 +2 +1 -2 3 4", sharov::MAX_STACK_ELEMENT_COUNT, values, size), "read: explicit signs");
    checkLongLong(-2, values[1], "read: signed value");

    checkStatus(sharov::MatrixReadStatus::success,
        readMatrixText("2 2 1 2 3 -2147483648", sharov::MAX_STACK_ELEMENT_COUNT, values, size),
        "read: INT_MIN element");
    checkLongLong(-2147483648LL, values[3], "read: INT_MIN value");

    checkStatus(sharov::MatrixReadStatus::success,
        readMatrixText("2 2 1 2 3 2147483647", sharov::MAX_STACK_ELEMENT_COUNT, values, size), "read: INT_MAX element");
    checkLongLong(2147483647LL, values[3], "read: INT_MAX value");

    checkStatus(sharov::MatrixReadStatus::success, readMatrixText("0 0", sharov::MAX_STACK_ELEMENT_COUNT, values, size),
        "read: empty matrix");
    checkLongLong(0, size.rows, "read: empty rows");
    checkLongLong(0, size.columns, "read: empty columns");

    checkStatus(sharov::MatrixReadStatus::success, readMatrixText("0 5", sharov::MAX_STACK_ELEMENT_COUNT, values, size),
        "read: zero row matrix");
    checkLongLong(0, size.rows, "read: zero row count");
    checkLongLong(5, size.columns, "read: zero row columns");

    checkStatus(sharov::MatrixReadStatus::notEnoughElements,
        readMatrixText("10000 1", sharov::MAX_STACK_ELEMENT_COUNT, values, size),
        "read: maximum size matrix without elements");
  }

  void testReadingErrors()
  {
    std::vector< long long > values;
    sharov::MatrixSize size = {0, 0};
    checkStatus(sharov::MatrixReadStatus::emptyInput, readMatrixText("", sharov::MAX_STACK_ELEMENT_COUNT, values, size),
        "read error: empty file");
    checkStatus(sharov::MatrixReadStatus::emptyInput,
        readMatrixText("   \n\t ", sharov::MAX_STACK_ELEMENT_COUNT, values, size), "read error: whitespace only file");
    checkStatus(sharov::MatrixReadStatus::notEnoughElements,
        readMatrixText("2", sharov::MAX_STACK_ELEMENT_COUNT, values, size), "read error: single number");
    checkStatus(sharov::MatrixReadStatus::notEnoughElements,
        readMatrixText("2 2", sharov::MAX_STACK_ELEMENT_COUNT, values, size), "read error: dimensions only");
    checkStatus(sharov::MatrixReadStatus::notEnoughElements,
        readMatrixText("2 2 1 2 3", sharov::MAX_STACK_ELEMENT_COUNT, values, size), "read error: not enough elements");
    checkStatus(sharov::MatrixReadStatus::notEnoughElements,
        readMatrixText("2 3 1 2 3 4 5", sharov::MAX_STACK_ELEMENT_COUNT, values, size),
        "read error: PDF not enough elements");
    checkStatus(sharov::MatrixReadStatus::extraElements,
        readMatrixText("2 2 1 2 3 4 5", sharov::MAX_STACK_ELEMENT_COUNT, values, size), "read error: extra elements");
    checkStatus(sharov::MatrixReadStatus::invalidToken,
        readMatrixText("My matrix: 2 2 1 2 3 4", sharov::MAX_STACK_ELEMENT_COUNT, values, size),
        "read error: PDF text prefix");
    checkStatus(sharov::MatrixReadStatus::invalidToken,
        readMatrixText("2 a 3 1 2 3 4 5 6", sharov::MAX_STACK_ELEMENT_COUNT, values, size),
        "read error: PDF letter token");
    checkStatus(sharov::MatrixReadStatus::invalidToken,
        readMatrixText("2 2 1 2 3 4abc", sharov::MAX_STACK_ELEMENT_COUNT, values, size), "read error: glued token");
    checkStatus(sharov::MatrixReadStatus::invalidToken,
        readMatrixText("2 2 1 2 3 -", sharov::MAX_STACK_ELEMENT_COUNT, values, size), "read error: bare sign");
    checkStatus(sharov::MatrixReadStatus::valueOverflow,
        readMatrixText("2 3 100000000000000000000000000000000000 2 3 4", sharov::MAX_STACK_ELEMENT_COUNT, values, size),
        "read error: PDF overflow");
    checkStatus(sharov::MatrixReadStatus::valueOverflow,
        readMatrixText("2 2 1 2 3 2147483648", sharov::MAX_STACK_ELEMENT_COUNT, values, size),
        "read error: int overflow");
    checkStatus(sharov::MatrixReadStatus::valueOverflow,
        readMatrixText("2 2 1 2 3 -2147483649", sharov::MAX_STACK_ELEMENT_COUNT, values, size),
        "read error: int underflow");
    checkStatus(sharov::MatrixReadStatus::negativeDimension,
        readMatrixText("-1 2 1 2", sharov::MAX_STACK_ELEMENT_COUNT, values, size), "read error: negative rows");
    checkStatus(sharov::MatrixReadStatus::negativeDimension,
        readMatrixText("2 -3 1 2 3 4", sharov::MAX_STACK_ELEMENT_COUNT, values, size), "read error: negative columns");
    checkStatus(sharov::MatrixReadStatus::elementLimitExceeded,
        readMatrixText("10001 1", sharov::MAX_STACK_ELEMENT_COUNT, values, size), "read error: stack storage limit");
    checkStatus(sharov::MatrixReadStatus::elementLimitExceeded,
        readMatrixText("101 100", sharov::MAX_STACK_ELEMENT_COUNT, values, size),
        "read error: stack storage limit rectangle");
    checkStatus(sharov::MatrixReadStatus::elementLimitExceeded, readMatrixText("2147483647 2", INT_MAX, values, size),
        "read error: dimension product overflow");
    checkStatus(sharov::MatrixReadStatus::elementLimitExceeded, readMatrixText("46341 46341", INT_MAX, values, size),
        "read error: dimension product overflow rectangle");
  }

  std::string formatMatrixText(const std::string &text, int maxElementCount)
  {
    std::vector< long long > values;
    sharov::MatrixSize size = {0, 0};
    const sharov::MatrixReadStatus status = readMatrixText(text, maxElementCount, values, size);
    if (status != sharov::MatrixReadStatus::success) {
      return "read error";
    }
    const sharov::Matrix matrix(values.data(), size.rows, size.columns);
    std::ostringstream output;
    sharov::writeMatrix(output, matrix);
    return output.str();
  }

  void testWriting()
  {
    checkString(
        "2 3 1 2 3 4 5 6\n", formatMatrixText("2 3 1 2 3 4 5 6", sharov::MAX_STACK_ELEMENT_COUNT), "write: 2x3");
    checkString("0 0\n", formatMatrixText("0 0", sharov::MAX_STACK_ELEMENT_COUNT), "write: empty matrix");
    checkString("1 1 -5\n", formatMatrixText("1 1 -5", sharov::MAX_STACK_ELEMENT_COUNT), "write: single element");
  }

  void testAssignmentExamples()
  {
    std::vector< long long > values;
    sharov::MatrixSize size = {0, 0};
    checkStatus(sharov::MatrixReadStatus::success,
        readMatrixText("3 3 1 2 3 4 5 6 7 8 9", sharov::MAX_STACK_ELEMENT_COUNT, values, size), "example 3x3: read");
    sharov::Matrix matrix3x3(values.data(), size.rows, size.columns);
    checkLongLong(1, sharov::getMinAntiDiagonalSum(matrix3x3), "example 3x3: MIN-SUM-MDG");
    sharov::addWaveLayerIncrements(matrix3x3);
    std::ostringstream output3x3;
    sharov::writeMatrix(output3x3, matrix3x3);
    checkString("3 3 2 3 4 5 7 7 8 9 10\n", output3x3.str(), "example 3x3: FLL-INC-WAV");

    checkStatus(sharov::MatrixReadStatus::success,
        readMatrixText("2 2 1 2 3 4", sharov::MAX_STACK_ELEMENT_COUNT, values, size), "example 2x2: read");
    sharov::Matrix matrix2x2(values.data(), size.rows, size.columns);
    checkLongLong(1, sharov::getMinAntiDiagonalSum(matrix2x2), "example 2x2: MIN-SUM-MDG");
    sharov::addWaveLayerIncrements(matrix2x2);
    std::ostringstream output2x2;
    sharov::writeMatrix(output2x2, matrix2x2);
    checkString("2 2 2 3 4 5\n", output2x2.str(), "example 2x2: FLL-INC-WAV");

    checkStatus(sharov::MatrixReadStatus::success, readMatrixText("0 0", sharov::MAX_STACK_ELEMENT_COUNT, values, size),
        "example 0x0: read");
    sharov::Matrix emptyMatrix(values.data(), size.rows, size.columns);
    checkLongLong(0, sharov::getMinAntiDiagonalSum(emptyMatrix), "example 0x0: MIN-SUM-MDG");
    sharov::addWaveLayerIncrements(emptyMatrix);
    std::ostringstream outputEmpty;
    sharov::writeMatrix(outputEmpty, emptyMatrix);
    checkString("0 0\n", outputEmpty.str(), "example 0x0: FLL-INC-WAV");
  }

  void testRandomMinAntiDiagonal()
  {
    std::mt19937 generator(RANDOM_SEED);
    std::uniform_int_distribution< int > dimensions(MIN_DIMENSION, MAX_DIMENSION);
    std::uniform_int_distribution< int > values(MIN_ELEMENT, MAX_ELEMENT);
    for (int caseIndex = 0; caseIndex < RANDOM_CASE_COUNT; ++caseIndex) {
      const int rows = dimensions(generator);
      const int columns = dimensions(generator);
      std::vector< long long > storage(static_cast< std::size_t >(rows * columns), 0);
      for (int index = 0; index < rows * columns; ++index) {
        storage[static_cast< std::size_t >(index)] = values(generator);
      }
      const sharov::Matrix matrix(storage.data(), rows, columns);
      const long long expected = bruteMinAntiDiagonalSum(storage, rows, columns);
      checkLongLong(expected, sharov::getMinAntiDiagonalSum(matrix), "random MIN-SUM case");
    }
  }

  void testRandomRoundTrip()
  {
    std::mt19937 generator(RANDOM_SEED);
    std::uniform_int_distribution< int > dimensions(MIN_DIMENSION, MAX_DIMENSION);
    std::uniform_int_distribution< int > values(MIN_ELEMENT, MAX_ELEMENT);
    for (int caseIndex = 0; caseIndex < ROUND_TRIP_CASE_COUNT; ++caseIndex) {
      const int rows = dimensions(generator);
      const int columns = dimensions(generator);
      const int elementCount = rows * columns;
      std::vector< long long > original(static_cast< std::size_t >(elementCount), 0);
      for (int index = 0; index < elementCount; ++index) {
        original[static_cast< std::size_t >(index)] = values(generator);
      }
      const sharov::Matrix matrix(original.data(), rows, columns);
      std::ostringstream output;
      sharov::writeMatrix(output, matrix);
      std::vector< long long > restored;
      sharov::MatrixSize restoredSize = {0, 0};
      const sharov::MatrixReadStatus status
          = readMatrixText(output.str(), sharov::MAX_STACK_ELEMENT_COUNT, restored, restoredSize);
      ++checksCount;
      if (status != sharov::MatrixReadStatus::success || restoredSize.rows != rows || restoredSize.columns != columns) {
        ++failuresCount;
        std::cout << "FAIL random round trip " << caseIndex << ": size or status differs\n";
        continue;
      }
      for (int index = 0; index < elementCount; ++index) {
        ++checksCount;
        if (restored[static_cast< std::size_t >(index)] != original[static_cast< std::size_t >(index)]) {
          ++failuresCount;
          std::cout << "FAIL random round trip " << caseIndex << ": element " << index << " differs\n";
        }
      }
    }
  }
}

int main()
{
  testMatrixAccess();
  testMinAntiDiagonal();
  testWaveIncrements();
  testStorage();
  testReading();
  testReadingErrors();
  testWriting();
  testAssignmentExamples();
  testRandomMinAntiDiagonal();
  testRandomRoundTrip();
  if (failuresCount == 0) {
    std::cout << "ALL TESTS PASSED: " << checksCount << " checks\n";
    return 0;
  }
  std::cout << "TESTS FAILED: " << failuresCount << " of " << checksCount << " checks failed\n";
  return 1;
}
