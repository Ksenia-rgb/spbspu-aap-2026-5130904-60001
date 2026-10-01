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
  while (first)
  {
    std::cin >> first;
  }
  if (!std::cin)
  {
    std::cerr << "Ваша последовательность не подходит под условия";
    return 1;
  }
}
