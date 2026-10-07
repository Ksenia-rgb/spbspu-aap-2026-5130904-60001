#include <iostream>

int main()
{
  int a = 0, prev = 0, fath = 0, mn = 0, grt = 0;

  std::cin >> prev;

  if (!std::cin) {
    std::cerr << "Unexpected input" << '\n';
    return 1;
  }

  if (prev == 0) {
    std::cerr << "No sequence" << '\n';
    return 2;
  }
  std::cin >> a;

  if (!std::cin) {
    std::cerr << "Unexpected input" << '\n';
    return 1;
  }

  if (a == 0) {
    std::cout << 0 << '\n' << 0 << '\n';
    return 0;
  }
  std::cin >> fath;

  if (!std::cin) {
    std::cerr << "Unexpected input" << '\n';
    return 1;
  }

  while (fath != 0) {
    if (a < prev && a < fath) {
      mn++;
    }
    if (a < prev && a > fath) {
      grt++;
    }
    prev = a;
    fath = a;
    std::cin >> fath;

    if (!std::cin) {
      std::cerr << "Unexpected input" << '\n';
      return 1;
    }
  }
  std::cout << mn << '\n';
  std::cout << grt << '\n';
  return 0;
}