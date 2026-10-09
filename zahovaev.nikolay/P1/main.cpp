#include <iostream>

int main()
{
  int first = 0;
  std::cin >> first;
  if (!std::cin)
  {
    std::cerr << "Ваша последовательность не подходит под условия";
    return 1;
  }
  int max_e = 0;
  int count_max = 0;
  int count_del = 0;
  int after_first = first;
  while (first != 0)
  {
    std::cin >> first;
    if (first % after_first == 0 && first != 0)
    {
      count_del++;
    }
    if (first > max_e || max_e == 0)
    {
      max_e = first;
      count_max = 1;
    } else if (first == max_e)
    {
      count_max++;
    }
    after_first = first;
  }
  if (!std::cin)
  {
    std::cerr << "Ваша последовательность не подходит под условия";
    return 1;
  }
  std::cout << count_max;
  if (count_del == 0)
  {
    std::cerr << "\nВаша последовательность не считается";
    return 2;
  } else
  {
    std::cout << "\n" << count_del;
  }
}
