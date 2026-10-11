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

  return 0;
}

int main()
{
  return parshina::calculateCharacteristics();
}
