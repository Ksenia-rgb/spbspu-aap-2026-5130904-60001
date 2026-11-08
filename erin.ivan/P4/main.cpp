#include <cstdlib>
#include <iostream>
#include <memory>
#include "strings.hpp"

int main()
{
  size_t len = 0;
  char * str = erin::readStr(std::cin, std::addressof(len));
  if (str == nullptr)
  {
    std::cerr << "Memory allocation failed\n";
    return 1;
  }
  if (len == 0)
  {
    std::free(str);
    std::cerr << "Empty input\n";
    return 1;
  }

  std::free(str);
  return 0;
}
