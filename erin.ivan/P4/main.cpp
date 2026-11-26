#include <cstdlib>
#include <iostream>
#include <memory>
#include "strings.hpp"

int main()
{
  size_t len = 0;
  char * const str = erin::readStr(std::cin, std::addressof(len));
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

  constexpr char sec_str[] = "def ";
  constexpr size_t sec_len = sizeof(sec_str) - 1;

  char * const uni_buf = static_cast< char * >(std::malloc((len + sec_len + 1) * sizeof(char)));
  if (uni_buf == nullptr)
  {
    std::free(str);
    std::cerr << "Memory allocation failed\n";
    return 1;
  }

  char * const rep_buf = static_cast< char * >(std::malloc((len + 1) * sizeof(char)));
  if (rep_buf == nullptr)
  {
    std::free(uni_buf);
    std::free(str);
    std::cerr << "Memory allocation failed\n";
    return 1;
  }

  std::cout << erin::uniteStr(uni_buf, str, sec_str) << "\n";
  std::cout << erin::findRep(rep_buf, str) << "\n";

  std::free(rep_buf);
  std::free(uni_buf);
  std::free(str);
  return 0;
}
