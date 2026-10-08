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

  int previous = 0;
  int before_previous = 0;
  int length = 0;

  while (current != 0)
  {
    before_previous = previous;
    previous = current;
    ++length;

    std::cin >> current;
    if (std::cin.fail())
    {
      std::cerr << "Error: input is not a valid number\n";
      return 1;
    }
  }

  return 0;
}
