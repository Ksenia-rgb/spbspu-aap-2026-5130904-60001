#include <cstddef>
#include <iostream>

namespace borsch {
  constexpr size_t singleElementLength = 1;
  constexpr size_t lengthLimit = ~static_cast< size_t >(0);
  constexpr int invalidInputCode = 1;
  constexpr int tooLongCode = 2;

  void updateMax(size_t length, size_t &max_value)
  {
    if (length > max_value) {
      max_value = length;
    }
  }

  void processEqual(int previous, int current, size_t &length, size_t &max_length)
  {
    if (current == previous) {
      if (length < lengthLimit) {
        ++length;
      }
    } else {
      updateMax(length, max_length);
      length = singleElementLength;
    }
  }

  void processIncreasing(int previous, int current, size_t &length, size_t &max_length)
  {
    if (current >= previous) {
      if (length < lengthLimit) {
        ++length;
      }
    } else {
      updateMax(length, max_length);
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
  size_t max_equal_length = 0;
  size_t equal_length = 0;
  size_t max_increasing_length = 0;
  size_t increasing_length = 0;
  int previous = 0;
  int current = 0;

  while (std::cin >> current && current != 0) {
    borsch::processEqual(previous, current, equal_length, max_equal_length);
    borsch::processIncreasing(previous, current, increasing_length, max_increasing_length);
    previous = current;
  }

  if (!std::cin) {
    std::cerr << "Error: input is not a valid sequence\n";
    return borsch::invalidInputCode;
  }

  borsch::updateMax(equal_length, max_equal_length);
  borsch::updateMax(increasing_length, max_increasing_length);

  const int equalCode = borsch::printLength(max_equal_length, "equal fragment");
  const int increasingCode = borsch::printLength(max_increasing_length, "increasing fragment");

  if (equalCode != 0) {
    return equalCode;
  }
  return increasingCode;
}
