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
  while (first != 0)
  {
    std::cin >> first;
    if (first % afterFirst == 0 && first != 0)
    {
      countDel++;
    }
    if (first > maxE || maxE == 0)
    {
      maxE = first;
      countMax = 1;
    } else if (first == maxE)
    {
      countMax++;
    }
    afterFirst = first;
  }
  if (!std::cin)
  {
    std::cerr << "Ваша последовательность не подходит под условия";
    return 1;
  }
  std::cout << countMax;
  if (countDel == 0)
  {
    std::cerr << "\nВаша последовательность не считается";
    return 2;
  } else
  {
    std::cout << "\n" << countDel;
  }
}
