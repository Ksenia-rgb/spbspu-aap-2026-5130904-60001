#include <iostream>

int main()
{
  long long a, b, c, max_value = 0;
  int count1 = 0, count2 = 0, value = 0;
  while (true) {
    std::cin >> a;
    if (std::cin.fail()) {
      std::cerr << "Input error\n";
      return 1;
    }
    if (a == 0) {
      break;
    }
    value++;
    if (value == 1 || a > max_value) {
      max_value = a;
      count2 = 0;
    } else {
      count2++;
    }
    std::cin >> b;
    if (std::cin.fail()) {
      std::cerr << "Input error\n";
      return 1;
    }
    if (b == 0) {
      break;
    }
    value++;
    if (b > max_value) {
      max_value = b;
      count2 = 0;
    } else {
      count2++;
    }
    std::cin >> c;
    if (std::cin.fail()) {
      std::cerr << "Input error\n";
      return 1;
    }
    if (c == 0) {
      break;
    }
    value++;
    if (c > max_value) {
      max_value = c;
      count2 = 0;
    } else {
      count2++;
    }
    if (a > 0 && b > 0 && c > 0 && ((a * a + b * b == c * c) || (a * a + c * c == b * b) || (b * b + c * c == a * a))) {
      count1++;
    }
  }
  std::cout << count1 << "\n";
  if (value == 0) {
    std::cerr << "Sequence is too short\n";
    return 2;
  }
  std::cout << count2 << "\n";
  return 0;
}
