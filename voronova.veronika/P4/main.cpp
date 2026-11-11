#include <cctype>
#include <cstdlib>
#include <iostream>

namespace voronova {
  size_t difLat(const char *str)
  {
    size_t count = 0;
    const size_t alphabet_size = 256;
    int used[alphabet_size] = {};
    for (size_t i = 0; str[i] != '\0'; ++i) {
      const unsigned char c = str[i];
      if (used[c] == 0 && std::isalpha(c)) {
        used[c] = 1;
        ++count;
      }
    }
    return count;
  }

  char *uppLow(const char *src, char *new_src)
  {
    size_t i = 0;
    for (; src[i] != '\0'; ++i) {
      if (std::isupper(src[i])) {
        new_src[i] = std::tolower(src[i]);
      } else {
        new_src[i] = src[i];
      }
    }
    new_src[i] = '\0';
    return new_src;
  }
}

int main()
{
  size_t capacity = 10;
  size_t size = 0;
  char *str = static_cast< char * >(std::malloc(capacity));

  if (str == nullptr) {
    std::cerr << "Error: not enough memory\n";
    return 1;
  }

  char c = 0;
  while (std::cin.get(c) && c != '\n') {
    if (size + 1 == capacity) {
      capacity = capacity * 2;
      char *const temp = static_cast< char * >(std::realloc(str, capacity));
      if (temp == nullptr) {
        std::free(str);
        std::cerr << "Error: not enough memory\n";
        return 1;
      }
      str = temp;
    }
    str[size] = c;
    ++size;
  }
  str[size] = '\0';

  if (size == 0) {
    std::free(str);
    std::cerr << "Error: empty input\n";
    return 1;
  }

  char *const res = static_cast< char * >(std::malloc(size + 1));
  if (res == nullptr) {
    std::free(str);
    std::cerr << "Error: not enough memory\n";
    return 1;
  }

  std::cout << voronova::difLat(str) << "\n";
  std::cout << voronova::uppLow(str, res) << "\n";

  std::free(res);
  std::free(str);
  return 0;
}
