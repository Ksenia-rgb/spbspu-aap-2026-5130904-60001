#include <iostream>

int main()
{
  long long a = 0;
  long long count = 0;
  size_t  min_len = 3;
  int prev2 = 0;
  int prev1 = 0;
  int sum_dup = 0;
  int prev = 0;
  int inc_seq  = 0;
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
    if (count == 0)
    {
      prev2 = a;
      prev = a;
      count++;
      continue;
    }
    if (count == 1)
    {
      prev1 = a;
      count++;
      if (a>prev)
      {
        inc_seq++;
        prev = a;
      }
      continue;
    }
    if (a == prev1 + prev2)
    {
      sum_dup++;
    }
    if (a>prev)
    {
      inc_seq++;
    }
    prev2 = prev1;
    prev1 = a;
    prev = a;
    count++;
  }
  if (count<min_len)
  {
    std::cerr << "Error: The sequence is too short to calculate the characteristic\n";
    return 2;
  }
  std::cout << sum_dup << "\n";
  std::cout << inc_seq << "\n";
  return 0;
}
