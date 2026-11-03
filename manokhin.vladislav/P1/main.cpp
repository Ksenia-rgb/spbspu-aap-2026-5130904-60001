#include <iostream>

int main()
{
  int prev = 0, a = 0, far = 0;
  int loc_min = 0;
  int grt_lss = 0;

  while (std::cin >> far && far != 0) {
    if (prev == 0) {
      prev = far;
      continue;
    } else if (a == 0) {
      a = far;
      continue;
    }

    if (a < prev && a < far) {
      loc_min++;
    }
    if (a < prev && a > far) {
      grt_lss++;
    }

    prev = a;
    a = far;
  }

  if (std::cin.fail()) {
    std::cerr << "Unexpected input";
    return 1;
  }

  if (prev == 0) {
    std::cerr << "Too short sequence";
    return 2;
  }

  std::cout << loc_min << '\n';
  std::cout << grt_lss << '\n';

  return 0;
}
