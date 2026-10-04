#include <iostream>

int main() {
  int a;
  while (std::cin >> a) {
    if (a == 0) {
      return 0;
    }
    std::cout << a << "\n";
  }
  if (std::cin.eof()) {
      std::cerr << "Error: unexpected EOF.\n";
      return 2;
  }
  if (std::cin.fail()) {
      std:cerr << "Error: invalid input.\n";
      return 1;
  }
  return 0;
}
