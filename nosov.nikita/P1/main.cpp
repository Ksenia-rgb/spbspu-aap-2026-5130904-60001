#include <iostream>

int main()
{
  int current = 0;
  std::cin >> current;

  if (std::cin.fail())
  {
    std::cerr << "Error: input is not a valid number\n";
    return 1;
  }

  return 0;
}
