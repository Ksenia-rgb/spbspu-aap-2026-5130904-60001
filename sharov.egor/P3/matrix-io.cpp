#include "matrix-io.hpp"

#include <cctype>
#include <climits>

#include "matrix.hpp"

namespace sharov {
  namespace {
    enum class TokenStatus { number, endOfInput, invalidToken, valueOverflow };

    TokenStatus readInteger(std::istream &input, int &value)
    {
      int character = input.get();
      while (character != EOF && std::isspace(character) != 0) {
        character = input.get();
      }
      if (character == EOF) {
        return TokenStatus::endOfInput;
      }
      const bool isNegative = character == '-';
      if (character == '-' || character == '+') {
        character = input.get();
      }
      const long long limit = isNegative ? -static_cast< long long >(INT_MIN) : static_cast< long long >(INT_MAX);
      long long magnitude = 0;
      int digitCount = 0;
      while (character != EOF && std::isdigit(character) != 0) {
        const int digit = character - '0';
        if (magnitude > (limit - digit) / 10) {
          return TokenStatus::valueOverflow;
        }
        magnitude = magnitude * 10 + digit;
        ++digitCount;
        character = input.get();
      }
      if (digitCount == 0) {
        return TokenStatus::invalidToken;
      }
      if (character != EOF && std::isspace(character) == 0) {
        return TokenStatus::invalidToken;
      }
      value = isNegative ? static_cast< int >(-magnitude) : static_cast< int >(magnitude);
      return TokenStatus::number;
    }

    MatrixReadStatus mapTokenStatus(TokenStatus status)
    {
      if (status == TokenStatus::invalidToken) {
        return MatrixReadStatus::invalidToken;
      }
      if (status == TokenStatus::valueOverflow) {
        return MatrixReadStatus::valueOverflow;
      }
      return MatrixReadStatus::notEnoughElements;
    }

    MatrixReadStatus readDimension(std::istream &input, bool isFirstDimension, int &value)
    {
      int number = 0;
      const TokenStatus status = readInteger(input, number);
      if (status == TokenStatus::endOfInput) {
        return isFirstDimension ? MatrixReadStatus::emptyInput : MatrixReadStatus::notEnoughElements;
      }
      if (status != TokenStatus::number) {
        return mapTokenStatus(status);
      }
      if (number < 0) {
        return MatrixReadStatus::negativeDimension;
      }
      value = number;
      return MatrixReadStatus::success;
    }
  }

  MatrixReadStatus readMatrixSize(std::istream &input, int maxElementCount, MatrixSize &size)
  {
    int rows = 0;
    MatrixReadStatus status = readDimension(input, true, rows);
    if (status != MatrixReadStatus::success) {
      return status;
    }
    int columns = 0;
    status = readDimension(input, false, columns);
    if (status != MatrixReadStatus::success) {
      return status;
    }
    const long long elementCount = static_cast< long long >(rows) * columns;
    if (elementCount > maxElementCount) {
      return MatrixReadStatus::elementLimitExceeded;
    }
    size.rows = rows;
    size.columns = columns;
    return MatrixReadStatus::success;
  }

  MatrixReadStatus readMatrixElements(std::istream &input, Matrix &matrix)
  {
    const int elementCount = matrix.getElementCount();
    long long *const data = matrix.getData();
    for (int index = 0; index < elementCount; ++index) {
      int number = 0;
      const TokenStatus status = readInteger(input, number);
      if (status != TokenStatus::number) {
        return mapTokenStatus(status);
      }
      data[index] = number;
    }
    int extraNumber = 0;
    const TokenStatus status = readInteger(input, extraNumber);
    if (status == TokenStatus::number) {
      return MatrixReadStatus::extraElements;
    }
    if (status == TokenStatus::endOfInput) {
      return MatrixReadStatus::success;
    }
    return mapTokenStatus(status);
  }

  const char *getMatrixReadMessage(MatrixReadStatus status)
  {
    switch (status) {
    case MatrixReadStatus::emptyInput:
      return "input error: file is empty";
    case MatrixReadStatus::notEnoughElements:
      return "input error: not enough numbers to fill the declared matrix";
    case MatrixReadStatus::invalidToken:
      return "input error: token is not an integer";
    case MatrixReadStatus::valueOverflow:
      return "input error: value does not fit into int";
    case MatrixReadStatus::negativeDimension:
      return "input error: matrix dimension is negative";
    case MatrixReadStatus::elementLimitExceeded:
      return "input error: matrix element count exceeds the allowed limit";
    case MatrixReadStatus::extraElements:
      return "input error: file contains extra numbers";
    default:
      return "input error";
    }
  }

  void writeMatrix(std::ostream &output, const Matrix &matrix)
  {
    output << matrix.getRows() << ' ' << matrix.getCols();
    const long long *const data = matrix.getData();
    const int elementCount = matrix.getElementCount();
    for (int index = 0; index < elementCount; ++index) {
      output << ' ' << data[index];
    }
    output << '\n';
  }
}
