#include <iostream>
int main()
{
  int number = 0;
  while (true){
    if (!(std::cin >> number)) {
      std::cerr << "Ошибка ввода\n";
      return 1;
    }
    if (number == 0){
      break;
    }
    std::cout << number << "\n";
  }
  return 0;
}
