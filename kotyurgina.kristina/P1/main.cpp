#include <iostream>
int main()
{
  int number = 0;
  int count = 0;
  int max_first = 0;
  int max_second = 0;

  while (true) {
    if (!(std::cin >> number)) {
      std::cerr << "Ошибка ввода\n";
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
    }
    if (count == 2) {
      if (number < max_first) {
        max_second = number;
      } else {
        max_second = max_first;
        max_first = number;
      }
    }
    if (count >= 3) {
      if (number > max_first) {
        max_second = max_first;
        max_first = number;
      } else if (number > max_second) {
          max_second = number;
      }
    }
    }

  if (count < 2) {
    std::cerr << "Недостаточно элементов последовательности\n";
    return 2;
  }
  std::cout << max_second << "\n";
  return 0;
}
