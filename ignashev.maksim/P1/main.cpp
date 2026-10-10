#include <iostream>
int main()
{
  int max1, max2, num;
  if (!(std::cin >> max1) || max1 == 0 || !(std::cin >> max2) || max2 == 0)
  {
    return 2;
  }
  if (max2 > max1) std::swap(max1, max2)
  while (std::cin >> num && num != 0)
  {
    if (num > max1)
    {
      max2 = max1;
      max1 = num;
    }
    else if (num > max2 && num < max1
    {
      max2 = num;
    }
    else if (max1 == max2 && num < max1)
    {
      max2 = num;
    }
  }
  std::cout << max2 << std::endl;
  return 0;
}
