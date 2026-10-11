#include <iostream>

int main()
{
  int a = 0;
  std::cin >> a;
  if (std::cin.fail()) {
    std::cerr << "Error\n";
    return 1;
  }
  if (a == 0) {
    std::cout << "Количество элементов, равных минимальному значению: 0\n";
    std::cout << "Количество элементов после максимума: 0\n";
    return 0;
  }
  int min = a;
  int max = a;
  int cnt1 = 1;
  int cnt2 = 0;
  while (std::cin >> a && a != 0) {
    if (a < min) {
      min = a;
      cnt1 = 1;
    } else if (a == min) {
      cnt1++;
    }
    if (a > max) {
      max = a;
      cnt2 = 0;
    } else {
      cnt2++;
    }
  }
  if (std::cin.fail()) {
    std::cerr << "Error\n";
    return 1;
  }
  std::cout << "Количество элементов, равных минимальному значению: " << cnt1 << "\n";
  std::cout << "Количество элементов после максимума: " << cnt2 << "\n";
  return 0;
}
