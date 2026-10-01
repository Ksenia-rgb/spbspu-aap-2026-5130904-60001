#include <iostream>

int main()
{
  int minusfirst = 0;
  int first = 0;
  std::cin >> first;
  if (!std::cin)
  {
    std::cerr << "Ваша последовательность не подходит под условия";
    return 1;
  }
  minusfirst = first;
  while (first)
  {
    std::cin >> first;
    
    minusfirst = first;
  }
  if (!std::cin)
  {
    std::cerr << "Ваша последовательность не подходит под условия";
    return 1;
  }
}
