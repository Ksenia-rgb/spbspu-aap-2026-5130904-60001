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
  int maxE = 0;
  int countMax = 0;
  int countDel = 0;
  int afterFirst = first;
  while (first)
  {
    std::cin >> first;
    
    afterFirst = first;
  }
  if (!std::cin)
  {
    std::cerr << "Ваша последовательность не подходит под условия";
    return 1;
  }
}
