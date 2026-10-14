#include <iostream>

int main() {
  int prev = 0;
  if (!(std::cin >> prev)) {
    if (std::cin.eof()) {
      std::cerr << "Error: cannot compute characteristic\n";
      return 2;
    }

    std::cerr << "Error: input is not a sequence\n";
    return 1;
  }

  if (prev == 0) {
    std::cout << 0 << "\n";
    std::cerr << "Error: cannot compute PTH-TRP characteristic\n";
    return 2;
  }

  int maxEqual = 1;
  int curEqual = 1;
  int first = prev;
  int second = 0;
  int third = 0;
  int have = 1;
  int pythCount = 0;
  int cur = 0;











}
