#include <iostream>
#include <cstddef>
#include <cstring>

namespace zaharov
{
  void removeLatinLetters(const char *src, char *dest)
  {
    size_t j = 0;
    for (size_t i = 0; src[i] != '\0'; ++i)
    {
      char c = src[i];
      bool isLatin = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');

      if (!isLatin)
      {
        dest[j] = c;
        ++j;
      }
    }
    dest[j] = '\0';
  }

  int hasRepeatingChars(const char *str)
  {
    int counts[256] = {0};
    for (size_t i = 0; str[i] != '\0'; ++i)
    {
      unsigned char c = static_cast< unsigned char >(str[i]);
      counts[c]++;
      if (counts[c] > 1)
      {
        return 1;
      }
    }
    return 0;
  }
}

int main()
{
  const size_t maxSize = 10000;
  char *buffer = new char[maxSize];

  if (!std::cin.getline(buffer, maxSize))
  {
    std::cerr << "Error: cannot read string\n";
    delete[] buffer;
    return 1;
  }

  char *res = new char[maxSize];

  zaharov::removeLatinLetters(buffer, res);
  std::cout << res << '\n';

  int hasRep = zaharov::hasRepeatingChars(buffer);
  std::cout << hasRep << '\n';

  delete[] buffer;
  delete[] res;

  return 0;
}
