#include <cctype>
#include <climits>
#include <cstdio>
#include <iostream>

#include "characteristics.hpp"

namespace sharov {
  enum class ReadStatus { number, terminator, endOfInput, invalidToken, overflow };

  ReadStatus readNumber(std::istream &input, int &value)
  {
    int character = input.get();
    while (character != EOF && std::isspace(character) != 0) {
      character = input.get();
    }
    if (character == EOF) {
      return ReadStatus::endOfInput;
    }
    const bool negative = character == '-';
    if (character == '-' || character == '+') {
      character = input.get();
    }
    const long long limit = negative ? -static_cast< long long >(INT_MIN) : static_cast< long long >(INT_MAX);
    long long magnitude = 0;
    int digitCount = 0;
    while (character != EOF && std::isdigit(character) != 0) {
      const int digit = character - '0';
      if (magnitude > (limit - digit) / 10) {
        return ReadStatus::overflow;
      }
      magnitude = magnitude * 10 + digit;
      ++digitCount;
      character = input.get();
    }
    if (digitCount == 0) {
      return ReadStatus::invalidToken;
    }
    if (character != EOF && std::isspace(character) == 0) {
      return ReadStatus::invalidToken;
    }
    value = negative ? static_cast< int >(-magnitude) : static_cast< int >(magnitude);
    if (value == 0) {
      return ReadStatus::terminator;
    }
    return ReadStatus::number;
  }

  const char *getReadErrorMessage(ReadStatus status)
  {
    switch (status) {
    case ReadStatus::endOfInput:
      return "input error: sequence is not terminated by zero";
    case ReadStatus::invalidToken:
      return "input error: token is not an integer";
    case ReadStatus::overflow:
      return "input error: value does not fit into int";
    default:
      return "input error";
    }
  }
}

int main()
{
  sharov::SequenceCharacteristics characteristics;
  int value = 0;
  while (true) {
    const sharov::ReadStatus status = sharov::readNumber(std::cin, value);
    if (status == sharov::ReadStatus::number) {
      characteristics.add(value);
      continue;
    }
    if (status == sharov::ReadStatus::terminator) {
      break;
    }
    std::cerr << sharov::getReadErrorMessage(status) << "\n";
    return 1;
  }
  std::cout << characteristics.getMonDec() << "\n";
  if (!characteristics.isLocMaxDefined()) {
    std::cerr << "LOC-MAX is undefined for an empty sequence\n";
    return 2;
  }
  std::cout << characteristics.getLocMax() << "\n";
  return 0;
}
