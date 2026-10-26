#include <cstddef>
#include <iostream>

int main()
{
  const std::size_t singleElementLength = 1;

  std::size_t max_equal_length = 0;
  std::size_t equal_length = 0;
  std::size_t max_increasing_length = 0;
  std::size_t increasing_length = 0;
  int previous = 0;
  int current = 0;

  while (std::cin >> current && current != 0) {
    if (current == previous) {
      ++equal_length;
    } else {
      if (equal_length > max_equal_length) {
        max_equal_length = equal_length;
      }
      equal_length = singleElementLength;
    }

    if (current >= previous) {
      ++increasing_length;
    } else {
      if (increasing_length > max_increasing_length) {
        max_increasing_length = increasing_length;
      }
      increasing_length = singleElementLength;
    }

    previous = current;
  }

  if (!std::cin) {
    const int invalidInputCode = 1;
    std::cerr << "Error: input is not a valid sequence\n";
    return invalidInputCode;
  }

  if (equal_length > max_equal_length) {
    max_equal_length = equal_length;
  }
  if (increasing_length > max_increasing_length) {
    max_increasing_length = increasing_length;
  }

  std::cout << max_equal_length << "\n";
  std::cout << max_increasing_length << "\n";
  return 0;
}
