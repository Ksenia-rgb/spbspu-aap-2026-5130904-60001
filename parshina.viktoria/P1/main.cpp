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

  int countMax = 1;
  int afterMax = 0;
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
      countMax = 1;
      afterMax = 0;
    }

    else
    {
      afterMax++;
      if (num == max)
      {
        countMax++;
      }
    }
  }
  std::cout << countMax << "\n";
  std::cout << afterMax << "\n";
  return 0;
}

int main()
{
  return parshina::calculateCharacteristics();
}
