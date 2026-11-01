#include <iostream>
#include <limits>
#include <cstddef>

int main()
{
  int number = 0;
  size_t count = 0;
  int max_first = std::numeric_limits< int >::min();
  int max_second = std::numeric_limits< int >::min();
  size_t div_count = 0;
  int last_number = 0;

  while ((std::cin >> number) && number != 0) {
    if (count < 2) {
      count++;
    }
    if (number > max_first) {
      max_second = max_first;
      max_first = number;
    } else if (number > max_second) {
      max_second = number;
    }

    if (count >= 2) {
      const long long current_number = number;
      if (current_number % last_number == 0) {
        if (div_count == std::numeric_limits< size_t >::max()) {
          std::cerr << "Sequence is too long\n";
          return 2;
        }
        div_count++;
      }
    }

    last_number = number;
  }

  if (!std::cin) {
    std::cerr << "Invalid input\n";
    return 1;
  }

  if (count < 2) {
    std::cerr << "Not enough elements\n";
    std::cout << div_count << "\n";
    return 2;
  }

  std::cout << max_second << "\n";

  std::cout << div_count << "\n";
  return 0;
}
