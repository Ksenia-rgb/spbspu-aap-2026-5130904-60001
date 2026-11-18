#include <cstddef>
#include <iostream>

namespace parshina
{
  void calculateCountMax(int num, size_t length, int & max, size_t & count);
  void calculateAfterMax(int num, size_t length, int & max, size_t & count);
}

void parshina::calculateCountMax(int num, size_t length, int & max, size_t & count)
{
  if (length == 0 || num > max)
  {
    max = num;
    count = 1;
  }
  else if (num == max)
  {
    ++count;
  }
}

void parshina::calculateAfterMax(int num, size_t length, int & max, size_t & count)
{
  if (length == 0 || num > max)
  {
    max = num;
    count = 0;
  }
  else
  {
    ++count;
  }
}

int main()
{
  int num = 0;
  int max_count = 0;
  int max_after = 0;
  size_t length = 0;
  size_t count_max = 0;
  size_t after_max = 0;

  while (std::cin >> num && num != 0)
  {
    parshina::calculateCountMax(num, length, max_count, count_max);
    parshina::calculateAfterMax(num, length, max_after, after_max);
    ++length;
  }

  if (!std::cin)
  {
    std::cerr << "Invalid input\n";
    return 1;
  }

  if (length == 0)
  {
    std::cerr << "Empty sequence\n";
    return 2;
  }

  std::cout << count_max << "\n";
  std::cout << after_max << "\n";

  return 0;
}
