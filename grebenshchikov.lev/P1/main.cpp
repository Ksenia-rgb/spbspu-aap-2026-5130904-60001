#include <iostream>

int main()
{
  constexpr long long INITIAL_MAX = -1000000000000;
  constexpr long long INITIAL_MIN = 1000000000000;

  long long max = INITIAL_MAX;
  long long sub_max = INITIAL_MAX;
  long long a = -1;
  long long ctn_min = 0;
  long long min = INITIAL_MIN;
  long long count = 0;

  while (a != 0)
  {
      std::cin >> a;

      if (std::cin.fail())
      {
          std::cerr << "Error: input is not valid sequence of integers\n";
          return 1;
      }

      if (a > max && a != 0)
      {
          sub_max = max;
          max = a;
      } else if (a >= sub_max && a < max && a != 0)
      {
          sub_max = a;
      }

      if (a < min && a != 0)
      {
          min = a;
          ctn_min = 1;
      } else if (a == min)
      {
          ++ctn_min;
      }

      if (a != 0)
      {
          ++count;
      }
  }

  int exit_code = 0;

  if (count < 2)
  {
      std::cerr << "Erorr: sequence too short for SUB-MAX\n";
      exit_code = 2;
  } else
  {
      std::cout << sub_max << '\n';
  }

  std::cout << ctn_min << '\n';
  return exit_code;
}
