#include <cstddef>
#include <iostream>

namespace borsch {
  constexpr size_t singleElementLength = 1;
  constexpr size_t lengthLimit = ~static_cast< size_t >(0);
  constexpr int invalidInputCode = 1;
  constexpr int tooLongCode = 2;

  void updateMax(size_t length, size_t &maxValue)
  {
    if (length > maxValue) {
      maxValue = length;
    }
  }

  void processEqual(int previous, int current, size_t &length, size_t &maxLength)
  {
    if (current == previous) {
      if (length < lengthLimit) {
        ++length;
      }
    } else {
      updateMax(length, maxLength);
      length = singleElementLength;
    }
  }

  void processIncreasing(int previous, int current, size_t &length, size_t &maxLength)
  {
    if (current >= previous) {
      if (length < lengthLimit) {
        ++length;
      }
    } else {
      updateMax(length, maxLength);
      length = singleElementLength;
    }
  }

  int printLength(size_t length, const char *description)
  {
    if (length == lengthLimit) {
      std::cerr << "Error: " << description << " is too long to be calculated\n";
      return tooLongCode;
    }
    std::cout << length << "\n";
    return 0;
  }
}

int main()
{
  size_t maxEqualLength = 0;
  size_t equalLength = 0;
  size_t maxIncreasingLength = 0;
  size_t increasingLength = 0;
  int previous = 0;
  int current = 0;

  while (std::cin >> current && current != 0) {
    borsch::processEqual(previous, current, equalLength, maxEqualLength);
    borsch::processIncreasing(previous, current, increasingLength, maxIncreasingLength);
    previous = current;
  }

  if (!std::cin) {
    std::cerr << "Error: input is not a valid sequence\n";
    return borsch::invalidInputCode;
  }

  borsch::updateMax(equalLength, maxEqualLength);
  borsch::updateMax(increasingLength, maxIncreasingLength);

  const int equalCode = borsch::printLength(maxEqualLength, "equal fragment");
  const int increasingCode = borsch::printLength(maxIncreasingLength, "increasing fragment");

  if (equalCode != 0) {
    return equalCode;
  }
  return increasingCode;
}
