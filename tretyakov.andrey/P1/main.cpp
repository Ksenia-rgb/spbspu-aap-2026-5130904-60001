#include <iostream>
#include <cstddef>
#include <limits>

int main()
{
  int value1 = 1;
  int value2 = 0;
  int hypotenuse = 0;
  size_t counter_of_pthtrp = 0;
  size_t counter_of_sumdup = 0;
  int two_previous = 0;
  size_t count_of_entered_values = 1;
  const int max_int = std::numeric_limits< int >::max();
  std::cin >> value1;
  if (!std::cin)
  {
    std::cerr << "Input error\n";
    return 1;
  }
  value2 = value1;
  if (value1 != 0)
  {
    try
    {
      while (std::cin >> value1 && value1 != 0)
      {
        ++count_of_entered_values;
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
            throw std::overflow_error("Overflow value1 * value1");
          }
          if (value1 * value1 > max_int - value2 * value2)
          {
            throw std::overflow_error("Overflow hypotenuse");
          }
          hypotenuse = value1 * value1 + value2 * value2;
        }
        two_previous = value1 + value2;
        value2 = value1;
      }
      if (!std::cin)
      {
        std::cerr << "Input error\n";
        return 1;
      }
    }
    catch (const std::overflow_error &)
    {
      std::cerr << "Overflow error\n";
      return 2;
    }
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
