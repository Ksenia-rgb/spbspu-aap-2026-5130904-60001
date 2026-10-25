#include <cstddef>
#include <iostream>

namespace parshina
{
  void calculateCharacteristics(int num, int & max, std::size_t & count_max, std::size_t & after_max);
}

void parshina::calculateCharacteristics(int num, int & max, std::size_t & count_max, std::size_t & after_max)
{
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

int main()
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

  int max = num;
  std::size_t count_max = 1;
  std::size_t after_max = 0;

  while (std::cin >> num && num != 0)
  {
    parshina::calculateCharacteristics(num, max, count_max, after_max);
  }

  if (!std::cin)
  {
    std::cerr << "Invalid input\n";
    return 1;
  }

  std::cout << count_max << "\n";
  std::cout << after_max << "\n";

  return 0;
}
