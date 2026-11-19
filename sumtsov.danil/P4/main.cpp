#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>

namespace sumtsov
{

  bool containsChar(const char *str, char target)
  {
    for (const char *p = str; *p != '\0'; ++p)
    {
      if (*p == target)
      {
        return true;
      }
    }
    return false;
  }

  size_t excludeSecond(const char *first, const char *second, char *result)
  {
    size_t pos = 0;
    for (const char *p = first; *p != '\0'; ++p)
    {
      if (!containsChar(second, *p))
      {
        result[pos] = *p;
        ++pos;
      }
    }
    result[pos] = '\0';
    return pos;
  }

  size_t addDigitsFromSecond(const char *first, const char *second, char *result)
  {
    size_t firstLen = std::strlen(first);
    std::memcpy(result, first, firstLen);

    size_t pos = firstLen;
    for (const char *p = second; *p != '\0'; ++p)
    {
      if (std::isdigit(static_cast< unsigned char >(*p)))
      {
        result[pos] = *p;
        ++pos;
      }
    }
    result[pos] = '\0';
    return pos;
  }

}

int main()
{
  std::string line;
  if (!std::getline(std::cin, line))
  {
    std::cerr << "Error: failed to read input string\n";
    return 1;
  }

  const char *first = line.c_str();
  size_t firstLen = line.size();

  const char *excSndSecond = "abc";
  const char *dgtSndSecond = "g1h2k";

  size_t dgtSndSecondLen = std::strlen(dgtSndSecond);

  size_t excSndBufferSize = firstLen + 1;
  size_t dgtSndBufferSize = firstLen + dgtSndSecondLen + 1;

  char *excSndResult = static_cast< char * >(std::malloc(excSndBufferSize));
  if (excSndResult == nullptr)
  {
    std::cerr << "Error: failed to allocate memory\n";
    return 1;
  }

  char *dgtSndResult = static_cast< char * >(std::malloc(dgtSndBufferSize));
  if (dgtSndResult == nullptr)
  {
    std::free(excSndResult);
    std::cerr << "Error: failed to allocate memory\n";
    return 1;
  }

  sumtsov::excludeSecond(first, excSndSecond, excSndResult);
  sumtsov::addDigitsFromSecond(first, dgtSndSecond, dgtSndResult);

  std::cout << excSndResult << '\n';
  std::cout << dgtSndResult << '\n';

  std::free(excSndResult);
  std::free(dgtSndResult);

  return 0;
}
