#include <iostream>
#include <cstddef>

int main()
{
  int num = 0;
  int max1 = 0;
  int max2 = 0;
  int current_element = 0;
  size_t current_streak = 0;
  size_t max_streak = 0;
  size_t count = 0;
  while ((std::cin >> num) && (num != 0))
  {
    count++;
    if (count == 1)
    {
      max1 = num;
      current_element = num;
      current_streak = 1;
      max_streak = 1;
    }
    else
    {
      if (num > max1)
      {
        max2 = max1;
        max1 = num;
      }
      else if ((num > max2) && (num < max1))
      {
        max2 = num;
      }
      if (num == current_element)
      {
        current_streak++;
      }
      else
      {
        if (current_streak > max_streak)
        {
          max_streak = current_streak;
        }
        current_element = num;
        current_streak = 1;
      }
    }
  }
  if (current_streak > max_streak)
  {
    max_streak = current_streak;
  }
  if ((!std::cin && !std::cin.eof()) || (max2 == 0))
  {
    return 2;
  }
  std::cout << max2 << "\n" << max_streak << "\n";
  return 0;
}
