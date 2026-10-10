#include <iostream>

int main()
{
  long long a = 0;
  long long count = 0;
  size_t  min_len = 3;
  long long prev2 = 0;
  long long prev1 = 0;
  long long sum_dup = 0;
  long long prev = 0;
  long long inc_seq  = 0;
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
    if (count >= 1 && a>prev1)
    {
      inc_seq++;
    }
    if (count >= 2 && a == prev1 + prev2)
    {
      sum_dup++;
    }
    prev2 = prev1;
    prev1 = a;
    count++;
  }
  std::cout << inc_seq << "\n";
  if (count<min_len)
  {
    std::cerr << "Error: The sequence is too short to calculate the characteristic\n";
    return 2;
  }
  std::cout << sum_dup << "\n";
  return 0;
}
