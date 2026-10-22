#include <iostream>
#include <limits>
int main()
{ 
  int max = std::numeric_limits<int>::min() + 1;
  int sub_max = std::numeric_limits<int>::min();

  int max2 = std::numeric_limits<int>::min();
  int cnt = 0;

  int val2 = 0;
  std::cin >> val2;

  if (std::cin.fail())
  {
    std::cout << "Error: input is not a valid number\n";
    return 1;
  }

  if (val2 == 0)
  {
    std::cerr << "Sequence too short to compute sub-max\n";
    std::cerr << "Sequence too short to compute aft-max\n";
    return 2;
  }

  max = val2;
  max2 = val2;

  while (std::cin >> val2 && val2!=0)
  {
    if (max < val2)
    {
      sub_max = max;
      max = val2;
    }
    else if (sub_max < val2 && max != val2)
    {
      sub_max = val2;
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
  }

  if (std::cin.fail())
    {
      std::cout << "Error: input is not a valid number\n";
      return 1;
    }
  
  if (sub_max == std::numeric_limits<int>::min())
  {
    std::cerr << "Sequence too short to compute sub-max\n";
    std::cout << "aft-max = " << cnt << '\n';
    return 2;
  }
  else
  {
    std::cout << "sub_max = " << sub_max << '\n';
    std::cout << "aft-max = " << cnt << '\n';
    return 0;
  }
}
