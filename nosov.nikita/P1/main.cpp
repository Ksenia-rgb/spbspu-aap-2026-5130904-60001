#include <cstddef>
#include <iostream>

int main()
{
  constexpr int invalid_input_code = 1;
  constexpr int internal_error_code = 2;

  int current = 0;
  int previous = 0;
  int before_previous = 0;

  std::size_t length = 0;
  std::size_t triples_count = 0;
  std::size_t divisible_count = 0;

  while ((std::cin >> current) && (current != 0))
  {
    if (length >= 1)
    {
      if ((current % previous) == 0)
      {
        ++divisible_count;
      }
    }

    if ((before_previous > 0) && (previous > 0) && (current > 0))
    {
      const long long a = before_previous;
      const long long b = previous;
      const long long c = current;
      if (((a * a) + (b * b)) == (c * c))
      {
        ++triples_count;
      }
    }

    before_previous = previous;
    previous = current;
    ++length;
  }

  if (std::cin.fail())
  {
    std::cerr << "Error: input is not a valid number\n";
    return invalid_input_code;
  }

  std::cout << "pth-trp = " << triples_count << '\n';

  if (length < 2)
  {
    std::cerr << "Sequence too short to compute div-rem\n";
    return internal_error_code;
  }

  std::cout << "div-rem = " << divisible_count << '\n';
  return 0;
}
