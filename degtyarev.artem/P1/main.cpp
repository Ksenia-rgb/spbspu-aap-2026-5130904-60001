#include <iostream>
const int two = 2;

int main()
{
  bool morethan0val = false;
  int val2 = 0;
  std::cin >> val2;

  if (std::cin.fail())
  {
    std::cout << "Error: input is not a valid number\n";
    return 1;
  }

  int max = val2;
  int sub_max = 0;

  int max2 = val2;
  int cnt = 0;

  while (val2 != 0)
  {
    morethan0val = true;
    std::cin >> val2;
    if (std::cin.fail())
    {
      std::cout << "Error: input is not a valid number\n";
      return 1;
    }

    if (val2 != 0)
    {
      if (max < val2)
      {
        sub_max = max;
        max = val2;
      }
      else if ((sub_max < val2 && max != val2) || (sub_max == 0 && max != val2))
      {
        sub_max = val2;
      }
    }

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

  if (morethan0val == false)
  {
    std::cerr << "Sequence too short to compute sub-max\n";
    std::cerr << "Sequence too short to compute aft-max\n";
    return two;
  }
  else if (sub_max == 0)
  {
    std::cerr << "Sequence too short to compute sub-max\n";
    std::cout << "aft-max = " << cnt << '\n';
    return two;
  }
  else
  {
    std::cout << "sub_max = " << sub_max << '\n';
    std::cout << "aft-max = " << cnt << '\n';
    return 0;
  }
}
