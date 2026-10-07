#include <iostream>

int main()
{
  int val2 = 0;
  std::cin >> val2;

  if (std::cin.fail())
  {
    std::cout << "Ошибка ввода!!! вы ввели не число, либо число не того формата\n";
    return 1;
  }

  // sub-max
  int max = val2;
  int sub_max = 0;

  // aft-max
  int max2 = val2;
  int cnt = 0;

  while (val2!=0)
  { 
    std::cin >> val2;
    if (std::cin.fail())
    {
      std::cout << "Ошибка ввода!!! вы ввели не число, либо число не того формата\n";
      return 1;
    }

    // sub-max
    if (val2 != 0)
    {
      if (max < val2)
      {
        sub_max = max;
        max = val2;
      }
      else if ((sub_max < val2 && max!=val2) | (sub_max == 0 && max!=val2))
      {
        sub_max = val2;
      }
    }

    // aft-max
    if (val2 != 0)
    {
      if (max2 >= val2)
      {
        ++cnt;
      }
      else
      {
        max2 = val2;
        cnt = 0;
      }
    }
  }

  if (cnt == 0)
  {
    std::cerr << "Слишком короткая последовательность, невозможно рассчитать sub-max" << '\n';
    std::cerr << "Слишком короткая последовательность, невозможно рассчитать aft-max" << '\n';
    return 2;
  }
  else if (sub_max == 0)
  {
    std::cerr << "Слишком короткая последовательность, невозможно рассчитать sub-max" << '\n';
    std::cout << "aft-max = " << cnt-1 << '\n';
    return 2;
  }
  else
  {
    std::cout << "sub_max = " << sub_max << '\n';
    std::cout << "aft-max = " << cnt << '\n';
    return 0;
  }
}