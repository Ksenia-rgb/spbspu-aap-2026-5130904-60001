#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <iostream>

namespace sumtsov
{

  constexpr size_t initial_capacity = 16;

  char *readLine(std::istream &in, size_t &length)
  {
    size_t capacity = initial_capacity;
    char *buffer = static_cast< char * >(std::malloc(capacity));
    if (buffer == nullptr)
    {
      return nullptr;
    }

    length = 0;
    char symbol = '\0';
    while (in.get(symbol) && (symbol != '\n'))
    {
      if (length + 1 >= capacity)
      {
        capacity *= 2;
        char *grown = static_cast< char * >(std::realloc(buffer, capacity));
        if (grown == nullptr)
        {
          std::free(buffer);
          return nullptr;
        }
        buffer = grown;
      }
      buffer[length] = symbol;
      ++length;
    }
    buffer[length] = '\0';
    return buffer;
  }

  int hasChar(const char *str, char target)
  {
    for (const char *p = str; *p != '\0'; ++p)
    {
      if (*p == target)
      {
        return 1;
      }
    }
    return 0;
  }

  size_t excludeSecond(const char *first, const char *second, char *result)
  {
    size_t pos = 0;
    for (const char *p = first; *p != '\0'; ++p)
    {
      if (hasChar(second, *p) == 0)
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
    const size_t first_length = std::strlen(first);
    std::memcpy(result, first, first_length);

    size_t pos = first_length;
    for (const char *p = second; *p != '\0'; ++p)
    {
      if (std::isdigit(static_cast< unsigned char >(*p)) != 0)
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
  size_t length = 0;
  char *first = sumtsov::readLine(std::cin, length);
  if (first == nullptr)
  {
    std::cerr << "Error: failed to allocate memory\n";
    return 1;
  }

  const char *exc_second = "abc";
  const char *dgt_second = "g1h2k";

  const size_t exc_size = length + 1;
  const size_t dgt_size = length + std::strlen(dgt_second) + 1;

  char *exc_result = static_cast< char * >(std::malloc(exc_size));
  char *dgt_result = static_cast< char * >(std::malloc(dgt_size));
  if ((exc_result == nullptr) || (dgt_result == nullptr))
  {
    std::free(exc_result);
    std::free(dgt_result);
    std::free(first);
    std::cerr << "Error: failed to allocate memory\n";
    return 1;
  }

  sumtsov::excludeSecond(first, exc_second, exc_result);
  sumtsov::addDigitsFromSecond(first, dgt_second, dgt_result);

  std::cout << exc_result << '\n';
  std::cout << dgt_result << '\n';

  std::free(exc_result);
  std::free(dgt_result);
  std::free(first);

  return 0;
}
