#include <cstddef>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace erin
{
  bool is_loc_max(int left, int mid, int right)
  {
    return (mid > left) && (mid > right);
  }

  bool is_sgn_chg(int pred, int now)
  {
    return ((pred > 0) && (now < 0)) || ((pred < 0) && (now > 0));
  }

  size_t update_loc_max(size_t count, int left, int mid, int right)
  {
    if (is_loc_max(left, mid, right))
    {
      if (count == std::numeric_limits< size_t >::max())
      {
        throw std::overflow_error("Too many local maximums");
      }
      ++count;
    }
    return count;
  }

  size_t update_sgn_chg(size_t count, int pred, int now)
  {
    if (is_sgn_chg(pred, now))
    {
      if (count == std::numeric_limits< size_t >::max())
      {
        throw std::overflow_error("Too many sign changes");
      }
      ++count;
    }
    return count;
  }
}

int main()
{
  const int max_int = std::numeric_limits< int >::max();
  int left = max_int;
  int mid = max_int;
  int right = max_int;
  int pred = 0;
  int now = 0;

  size_t count_loc_max = 0;
  size_t count_sgn_chg = 0;

  try
  {
    while ((std::cin >> now) && (now != 0))
    {
      left = mid;
      mid = right;
      right = now;

      count_loc_max = erin::update_loc_max(count_loc_max, left, mid, right);
      count_sgn_chg = erin::update_sgn_chg(count_sgn_chg, pred, now);

      pred = now;
    }
  }
  catch (const std::overflow_error & e)
  {
    std::cerr << e.what() << "\n";
    return 2;
  }

  if (!std::cin)
  {
    std::cerr << "Invalid input\n";
    return 1;
  }

  int return_code = 0;
  if (pred == 0)
  {
    std::cerr << "Not enough elements\n";
    return_code = 2;
  }
  else
  {
    std::cout << count_loc_max << "\n";
  }

  std::cout << count_sgn_chg << "\n";
  return return_code;
}
