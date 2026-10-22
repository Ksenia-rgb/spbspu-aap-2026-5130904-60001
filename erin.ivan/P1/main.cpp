#include <cstddef>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace erin
{
  bool LocMax(int left, int mid, int right)
  {
    return (mid > left) && (mid > right);
  }

  bool SgnChg(int pred, int now)
  {
    return ((pred > 0) && (now < 0)) || ((pred < 0) && (now > 0));
  }

  void processSequence(std::istream & in, std::size_t & count_loc_max, std::size_t & count_sgn_chg)
  {
    const int max_int = std::numeric_limits< int >::max();
    int left = max_int;
    int mid = max_int;
    int right = max_int;

    int pred = 0;
    int now = 0;

    while ((in >> now) && (now != 0))
    {
      left = mid;
      mid = right;
      right = now;

      if (LocMax(left, mid, right))
      {
        count_loc_max++;
      }

      if (SgnChg(pred, now))
      {
        count_sgn_chg++;
      }
      pred = now;
    }

    if (!in)
    {
      throw std::invalid_argument("Invalid input");
    }

    if (pred == 0)
    {
      throw std::length_error("Empty sequence");
    }
  }
}

int main()
{
  const int input_error = 1;
  const int empty_error = 2;

  std::size_t count_loc_max = 0;
  std::size_t count_sgn_chg = 0;
  int return_code = 0;

  try
  {
    erin::processSequence(std::cin, count_loc_max, count_sgn_chg);
  }
  catch (const std::invalid_argument & e)
  {
    std::cerr << e.what() << "\n";
    return input_error;
  }
  catch (const std::length_error & e)
  {
    std::cerr << e.what() << "\n";
    return_code = empty_error;
  }

  if (return_code == 0)
  {
    std::cout << count_loc_max << "\n";
  }
  std::cout << count_sgn_chg << "\n";
  return return_code;
}