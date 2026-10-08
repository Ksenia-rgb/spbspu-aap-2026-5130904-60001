#include <iostream>

namespace erin
{
  int task()
  {
    int a = 0;
    int b = 0;
    int c = 0;
    int count_loc_max = 0;

    int pred = 0;
    int count_sgn_chg = 0;

    int len = 0;
    int now = 0;

    const int min_w = 3;
    const int error = 2;

    while (std::cin >> now && now != 0)
    {
      a = b;
      b = c;
      c = now;
      len++;

      if (len >= min_w)
      {
        if (b > a && b > c)
        {
          count_loc_max++;
        }
      }

      if ((pred > 0 && now < 0) || (pred < 0 && now > 0))
      {
        count_sgn_chg++;
      }
      pred = now;
    }

    if (!std::cin)
    {
      std::cerr << "Invalid input\n";
      return 1;
    }

    if (len == 0)
    {
      std::cerr << "Empty sequence\n";
      return error;
    }

    std::cout << count_loc_max << "\n";
    std::cout << count_sgn_chg << "\n";
    return 0;
  }
}

int main()
{
  return erin::task();
}
