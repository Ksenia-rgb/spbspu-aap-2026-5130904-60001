#include <iostream>
#include <cstddef>

int main()
{
  long long num = 0;
  size_t count = 0;
  long long prev2 = 0;
  long long prev1 = 0;
  size_t sum_dup = 0;
  size_t inc_seq = 0;
  while (std::cin >> num && num != 0)
  {
    if (count >= 1 && num > prev1)
    {
      inc_seq++;
    }
    if (count >= 2 && (num - prev1 == prev2))
    {
      sum_dup++;
    }
    prev2 = prev1;
    prev1 = num;
    count++;
  }
  if (std::cin.fail())
  {
    std::cerr << "Error: input is not a valid sequence\n";
    return 1;
  }
  std::cout << inc_seq << "\n";
  if (count < 3)
  {
    std::cerr << "Error: The sequence is too short to calculate the characteristic\n";
    return 2;
  }
  std::cout << sum_dup << "\n";
  return 0;
}
