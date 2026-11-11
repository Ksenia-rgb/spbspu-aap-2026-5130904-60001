#include <iostream>
#include <cstddef>
#include <limits>

int main()
{
  int value1 = 0;
  int value2 = 0;
  int hypotenuse = 0;
  size_t counter_of_pthtrp = 0;
  size_t counter_of_sumdup = 0;
  int two_previous = 0;
  size_t count_of_entered_values = 0;
  constexpr int max_int = std::numeric_limits< int >::max();
  while (std::cin >> value1 && value1 != 0)
  {
    ++count_of_entered_values;
    if (value2 != 0)
    {
      if (two_previous == value1)
      {
        ++counter_of_sumdup;
      }
      if (value1 > 0 && value2 > 0)
      {
        if (value1 == hypotenuse / value1)
        {
          ++counter_of_pthtrp;
        }
        if ((value1 > max_int / value1) || (value2 > max_int / value2))
        {
          std::cerr << "Overflow error\n";
          return 2;
        }
        if (value1 * value1 > max_int - value2 * value2)
        {
          std::cerr << "Overflow error\n";
          return 2;
        }
        hypotenuse = value1 * value1 + value2 * value2;
      }
      two_previous = value1 + value2;
    }
    value2 = value1;
  }
  if (!std::cin)
  {
    std::cerr << "Input error\n";
    return 1;
  }
  if (count_of_entered_values > 2)
  {
    std::cout << "PTH-TRP = " << counter_of_pthtrp << "\n";
    std::cout << "SUM-DUP = " << counter_of_sumdup << "\n";
    return 0;
  }
  else
  {
    std::cerr << "Sequence too short for SUM-DUP\n";
    std::cout << "PTH-TRP = " << counter_of_pthtrp << "\n";
    return 2;
  }
  return 0;
}
