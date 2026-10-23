#include <iostream>

int main()
{
  int num = 0;
  if (!(std::cin >> num) || (num == 0))
  {
    return 2;
  }
  int max1 = num;
  int max2 = 0;
  int current_element = num;
  int current_streak = 1;
  int max_streak = 1;
  while ((std::cin >> num) && (num != 0))
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
    else if ((max1 == max2) && (num < max1))
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
  if (current_streak > max_streak)
  {
    max_streak = current_streak;
  }
  if (max2 == 0)
  {
    return 2;
  }
  std::cout << max2 << "\n" << max_streak << "\n";
  return 0;
}
