#include <iostream>

namespace parshina
{
  int calculateCharacteristics();
}

int parshina::calculateCharacteristics()
{
  int num = 0;
  std::cin >> num;

  if (!std::cin)
  {
    std::cerr << "Invalid input\n";
    return 1;
  }

  if (num == 0)
  {
    std::cerr << "Empty sequence\n";
    return 2;
  }

  int count_max = 1;
  int after_max = 0;
  int max = num;

  while (num != 0)
  {
    std::cin >> num;
    if (!std::cin)
    {
      std::cerr << "Invalid input\n";
      return 1;
    }

    if (num == 0)
    {
      break;
    }

    if (num > max)
    {
      max = num;
      count_max = 1;
      after_max = 0;
    }

    else
    {
      after_max++;
      if (num == max)
      {
        count_max++;
      }
    }
  }
  std::cout << count_max << "\n";
  std::cout << after_max << "\n";
  return 0;
}

int main()
{
  return parshina::calculateCharacteristics();
}
