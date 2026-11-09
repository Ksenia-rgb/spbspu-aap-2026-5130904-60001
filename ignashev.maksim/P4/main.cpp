#include <cctype>
#include <cstddef>

namespace ignashev {
  int repDgt(const char *str)
  {
    if (str == nullptr) {
      return 0;
    }
    int digitCounts[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (std::size_t i = 0; str[i] != '\0'; ++i) {
      if (std::isdigit(static_cast< unsigned char >(str[i]))) {
        std::size_t digitIndex = static_cast< std::size_t >(str[i] - '0');
        digitCounts[digitIndex] += 1;
        if (digitCounts[digitIndex] > 1) {
          return 1;
        }
      }
    }
    return 0;
  }
  char *rmvVow(char *dest, const char *src)
  {
    if (dest == nullptr || src == nullptr) {
      return dest;
    }
    std::size_t j = 0;
    for (std::size_t i = 0; src[i] != '\0'; ++i) {
      char ch = src[i];
      char lowerCh = static_cast< char >(std::tolower(static_cast< unsigned char >(ch)));
      if (lowerCh == 'a' || lowerCh == 'e' || lowerCh == 'i' || lowerCh == 'o' || lowerCh == 'u' || lowerCh == 'y') {
        continue;
      }
      dest[j] = ch;
      j += 1;
    }
    dest[j] = '\0';
    return dest;
  }
}