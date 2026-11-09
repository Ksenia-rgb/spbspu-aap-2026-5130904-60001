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
{}
