#include <cstddef>
#include <iostream>
#include <memory>
#include <new>
#include "strings.hpp"

int main()
{
  const char* const has_sam_second = "abs";
  const char* const dgt_snd_second = "g1h2k";

  size_t length = 0;
  char* const line = readLine(std::addressof(std::cin), std::addressof(length));
  if (line == nullptr) {
    std::cerr << "Error: not enough memory\n";
    return 1;
  }
  if (length == 0) {
    delete[] line;
    std::cerr << "Error: empty input\n";
    return 1;
  }

  const size_t result_size = length + countDgt(dgt_snd_second) + 1;
  char* const result = new (std::nothrow) char[result_size];
  if (result == nullptr) {
    delete[] line;
    std::cerr << "Error: not enough memory\n";
    return 1;
  }

  dgtSnd(result, line, dgt_snd_second);

  std::cout << hasSam(line, has_sam_second) << "\n";
  std::cout << result << "\n";

  delete[] result;
  delete[] line;
  return 0;
}
