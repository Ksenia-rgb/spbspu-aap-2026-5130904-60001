#include <iostream>

namespace sharov {
  constexpr char studentName[] = "sharov.egor";
}

int main()
{
  std::cout << sharov::studentName << '\n';
  if (!std::cout) {
    std::cerr << "Output error.\n";
    return 2;
  }

  return 0;
}
