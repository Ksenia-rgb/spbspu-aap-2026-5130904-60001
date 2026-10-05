#include <iostream>

int main() {
  int a;
  while (std::cin >> a) {
    if (a == 0) {
      return 0;
    }
    std::cout << a << "\n";
  }

