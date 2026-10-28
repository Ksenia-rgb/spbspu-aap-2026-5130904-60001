#include <iostream>
#include <limits>
int main()
{
  int max = std::numeric_limits< int >::min() + 1;
  int sub_max = std::numeric_limits< int >::min();
  int cnt = 0;

  int val = 0;
  while (std::cin >> val && val != 0) {
    if (max < val) {
      sub_max = max;
      max = val;
      cnt = 0;
    } else {
      ++cnt;
      if (sub_max < val && max != val) {
        sub_max = val;
      }
    }
  }

  if (std::cin.fail()) {
    std::cout << "Error: input is not a valid number\n";
    return 1;
  }

  if (sub_max == std::numeric_limits< int >::min()) {
    std::cerr << "Sequence too short to compute sub-max\n";
    std::cout << "aft-max = " << cnt << '\n';
    return 2;
  } else {
    std::cout << "sub_max = " << sub_max << '\n';
    std::cout << "aft-max = " << cnt << '\n';
    return 0;
  }
}