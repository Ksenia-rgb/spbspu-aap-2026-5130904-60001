#include <iostream>

int main()
{
  long long a = 0;
  long long count = 0;
  size_t  min_len = 3;
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
    count++;
  }
  if (count<min_len)
  {
    std::cerr << "Error: The sequence is too short to calculate the characteristic\n";
    return 2;
  }
  std::cout << a << "\n";
  return 0;
}
