#include <iostream>
#include <cstdlib>
#include <cctype>

namespace voronova {
  size_t difLat(const char *str) {
    size_t count = 0;
    int used[256] = {};
    for (size_t i = 0; str[i] != '\0'; ++i) {
      unsigned char c = str[i];
      if (used[c] == 0 && std::isalpha(c)) {
        used[c] = 1;
        ++count;
      }
    }
  return count;
  }

  char * uppLow(const char *src, char *newSrc) {
    size_t i = 0;
    for (; src[i] != '\0'; ++i) {
      if (std::isupper(src[i])) {
        newSrc[i] = std::tolower(src[i]);
      } else {
        newSrc[i] = src[i];
      }
    }
    newSrc[i] = '\0';
    return newSrc;
  }
}

int main()
{
  size_t capacity = 10;
  size_t size = 0;
  char * str = static_cast< char * >(std::malloc(capacity));

  if (str == nullptr) {
    std::cerr << "Error: not enough memory\n";
    return 1;
  }

  char c = 0;
  while (std::cin.get(c) && c != '\n') {
    if (size + 1 == capacity) {
      capacity = capacity * 2;
      char * temp = static_cast< char * >(std::realloc(str, capacity));
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

  char * res = static_cast< char * >(std::malloc(size + 1));
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
