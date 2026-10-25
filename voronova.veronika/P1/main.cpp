#include <iostream>
#include <limits>
#include <cstddef>

int main()
{
  int a = 0;

  int min = std::numeric_limits< int >::max();
  int max = std::numeric_limits< int >::min();
  std::size_t cnt1 = 0;
  std::size_t cnt2 = 0;

  while ((std::cin >> a) && (a != 0)) {
    if (a < min) {
      min = a;
      cnt1 = 1;
    } else if (a == min) {
      if (cnt1 == std::numeric_limits< std::size_t >::max()) {
        std::cerr << "Error\n";
        return 1;
      }
      cnt1++;
    }

    if (a > max) {
      max = a;
      cnt2 = 0;
    } else {
      if (cnt2 == std::numeric_limits< std::size_t >::max()) {
        std::cerr << "Error\n";
        return 1;
      }
      cnt2++;
    }
  }

  if (std::cin.fail()) {
    std::cerr << "Error\n";
    return 1;
  }
  std::cout << "CNT-MIN nums: " << cnt1 << "\n";
  std::cout << "AFT-MAX nums: " << cnt2 << "\n";
  return 0;
}
