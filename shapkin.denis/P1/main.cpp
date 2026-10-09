#include <iostream>

int main()
{
  long long a = 0;
  while (true)
  {
    std::cin >> a;
    if (std::cin.fail())
    {
      std::cerr << "Error: input is not a valid sequence\n";
      return 1;
    }
    if (a==0)
    {
      break;
    }
  }
  std::cout << a << "\n";
  return 0;
}
