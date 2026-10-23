#include <iostream>
#include <limits>
int main()
{
  int number = 0;
  size_t count = 0;
  int max_first = 0;
  int max_second = 0;
  size_t div_count = 0;
  int last_number = 0;

  while (true) {
    if (!(std::cin >> number)) {
      std::cerr << "Invalid input\n";
      return 1;
    }
    if (number == 0) {
      break;
    }
    if (count < 4) {
      count++;
    }
    if (count == 1) {
      max_first = number;
      last_number = number;
    }
    const long long current_number = number;
    if (count == 2) {
      if (number < max_first) {
        max_second = number;
      } else {
        max_second = max_first;
        max_first = number;
      }
      if (current_number % last_number == 0) {
        if (div_count == std::numeric_limits< size_t >::max()) {
          std::cerr << "Sequence is too long\n";
          return 2;
        }
        div_count++;
      }
    }
    if (count >= 3) {
      if (number > max_first) {
        max_second = max_first;
        max_first = number;
      } else if (number > max_second) {
        max_second = number;
      }
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

  if (count < 2) {
    std::cerr << "Not enough elements\n";
    std::cout << div_count << "\n";
    return 2;
  }
  std::cout << max_second << "\n";
  std::cout << div_count << "\n";
  return 0;
}
