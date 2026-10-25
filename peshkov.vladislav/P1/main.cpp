#include <cstddef>
#include <iostream>

int main()
{
  long long prev = 0;
  long long curr = 0;
  long long next = 0;
  size_t count_grt_lss = 0;

  long long max_val = 0;
  size_t count_aft_max = 0;

  size_t total_count = 0;

  while (std::cin >> next && next != 0) {
    ++total_count;

    if (total_count >= 3) {
      if (curr < prev && curr > next) {
        ++count_grt_lss;
      }
    }
    prev = curr;
    curr = next;

    if (total_count == 1 || next > max_val) {
      max_val = next;
      count_aft_max = 0;
    } else {
      ++count_aft_max;
    }
  }

  if (next != 0 || std::cin.fail()) {
    std::cerr << "Error: invalid input\n";
    return 1;
  }

  if (total_count == 0) {
    std::cerr << "Error: sequence is too short\n";
    return 2;
  }

  std::cout << count_grt_lss << "\n";
  std::cout << count_aft_max << "\n";

  return 0;
}
