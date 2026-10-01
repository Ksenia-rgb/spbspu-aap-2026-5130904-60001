#include <iostream>

int main()
{
  int val1 = 0, val2 = 1;
  std::cin >> val2;
  while (val2!=0)
  { 
    val1 = val2;
    std::cin >> val2;
  }
  std::cout << val1 << '\n';
}
