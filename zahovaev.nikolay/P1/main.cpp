#include <iostream>
#include <cstddef>
#include <climits>
#include <stdexcept>

namespace zahovaev
{
  size_t max_size_t =ULONG_MAX;
  void div_rem(const int first, const int before_first, size_t & count_del)
  {
    if (first % before_first == 0)
    {
      if (count_del == max_size_t)
      {
        throw std::logic_error("Overflow");
      }
      count_del++;
    }
  }

  void cnt_max(const int first, int & max_e, size_t & count_max)
  {
    if (first > max_e)
    {
      max_e = first;
      count_max = 1;
    }
    else if (first == max_e)
    {
      if (count_max == max_size_t)
      {
        throw std::logic_error("Overflow");
      }
      count_max++;
    }
  }
};
int main()
{
  int first = 0;
  int max_e = INT_MIN;
  size_t count_max = 0;
  size_t count_del = 0;
  std::cin >> first;
  int before_first = first;
  try
  {
    while (std::cin >> first && first != 0)
    {
      zahovaev::div_rem(first, before_first, count_del);
      zahovaev::cnt_max(first, before_first, count_max);
      
      before_first = first;
    }
  }
  catch(const std::logic_error & e)
  {
    std::cerr << "Your sequence too big\n";
    return 1;
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
