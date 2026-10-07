#include <iostream>

int main()
{
  int val1 = 0, val2 = 0;
  std::cin >> val2;

  if (std::cin.fail())
  {
    std::cout << "Ошибка ввода!!! вы ввели не число, либо число не того формата\n";
    return 1;
  }

  int max = val2;
  int sub_max = 0;

  int max2 = val2;
  int cnt = 0;

  while (val2!=0)
  { 
    val1 = val2;
    std::cin >> val2;
    if (std::cin.fail())
    {
      std::cout << "Ошибка ввода!!! вы ввели не число, либо число не того формата\n";
      return 1;
    }

    if (max2 >= val2)
    {
      ++cnt;
    }
    else
    {
      max2 = val2;
      cnt = 0;
    }

    if (max < val2)
    {
      sub_max = max;
      max = val2;
    }
    else if (sub_max < val2 && max!=val2)
    {
      sub_max = val2;
    }
  
  }
  std::cout << "////////////////////" << '\n';

  std::cout << sub_max <<  '\n';
  std::cout << cnt-1 <<  '\n';
}
