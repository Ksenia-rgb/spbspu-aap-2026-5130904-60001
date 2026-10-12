#include <iostream>

int main() {
  int prev = 0;
  int curr = 0;
  int v1_c = 0;
  int max = 0;
  int v2_c = 0;

  if (!(std::cin >> prev)) {
    std::cerr << "error: the input data cannot be identified as a sequence\n";
    return 1;
  }

  if (prev == 0) {
    std::cout << 0 << '\n';
    std::cerr << "error: the sequence is empty\n";
    return 2;
  }

  max = prev;
  v2_c = 1;

  while (std::cin >> curr) {
    if (curr == 0) {
      break;
    }

    if (curr > prev) {
      v1_c++;
    }

    if (curr > max) {
      max = curr;
      v2_c = 1;
    } else if (curr == max) {
      v2_c++;
    }
    prev = curr;
  }

  if (!std::cin || curr != 0) {
    std::cerr << "error: the input data cannot be identified as a sequence\n";
    return 1;
  }

  std::cout << v1_c << '\n';
  std::cout << v2_c << '\n';
  return 0;
}
