#include <iostream>
#include <cstddef>

int main()
{
  int first = 0;
  std::cin >> first;
  if (!std::cin)
  {
    std::cerr << "Your sequence is incorrect\n";
    return 1;
  }
  int max_e = first;
  size_t count_max = 0;
  const size_t max_size_t = -1;
  size_t count_del = 0;
  int after_first = first;
  while (std::cin >> first && first != 0)
  {
    if (first % after_first == 0)
    {
      count_del++;
    }
    if (first > max_e)
    {
      max_e = first;
      count_max = 1;
    }
    else if (first == max_e)
    {
      if (count_max == max_size_t)
      {
        std::cerr << "Your sequence too big";
        return 1;
      }
      count_max++;
    }
    after_first = first;
  }
  if (!std::cin)
  {
    std::cerr << "Your sequence is incorrect\n";
    return 1;
  }
  std::cout << count_max;
  if (count_del == 0)
  {
    std::cerr << "\nYour sequence is not calculated\n";
    return 2;
  }
  else
  {
    std::cout << "\n" << count_del << "\n";
  }
}
