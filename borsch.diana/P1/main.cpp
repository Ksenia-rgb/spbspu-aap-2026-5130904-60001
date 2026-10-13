#include <iostream>

namespace borsch {
  int analyzeSequence();
}

int main()
{
  return borsch::analyzeSequence();
}

int borsch::analyzeSequence()
{
  const int singleElementLength = 1;
  const int invalidInputCode = 1;

  int max_equal_length = 0;
  int equal_length = 0;
  int max_increasing_length = 0;
  int increasing_length = 0;
  int previous = 0;
  int current = 0;
  bool is_terminated = false;

  while (std::cin >> current) {
    if (current == 0) {
      is_terminated = true;
      break;
    }

    if (equal_length > 0 && current == previous) {
      ++equal_length;
    } else {
      equal_length = singleElementLength;
    }

    if (increasing_length > 0 && current >= previous) {
      ++increasing_length;
    } else {
      increasing_length = singleElementLength;
    }

    if (equal_length > max_equal_length) {
      max_equal_length = equal_length;
    }
    if (increasing_length > max_increasing_length) {
      max_increasing_length = increasing_length;
    }

    previous = current;
  }

  if (!is_terminated) {
    std::cerr << "Error: input is not a valid sequence\n";
    return invalidInputCode;
  }

  std::cout << max_equal_length << "\n";
  std::cout << max_increasing_length << "\n";
  return 0;
}
