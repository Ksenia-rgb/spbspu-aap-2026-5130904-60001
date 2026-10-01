#include <iostream>

int main()
{
  int val1 = 0, val2 = 1;
  std::cin >> val2;

  if (std::cin.fail())
  {
    std::cout << "Ошибка ввода!!! вы ввели не число, либо число не того формата\n";
    return 1;
  }

  while (val2!=0)
  { 
    val1 = val2;
    std::cin >> val2;
    if (std::cin.fail())
    {
      std::cout << "Ошибка ввода!!! вы ввели не число, либо число не того формата\n";
      return 1;
    }
  }

  std::cout << val1 << '\n';
}
