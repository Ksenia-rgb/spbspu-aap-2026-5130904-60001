#include <iostream>
#include <istream>
#include <cstddef>
#include <new>
#include <cctype>

namespace grebenshchikov
{
  char * extend(const char * str, size_t size, size_t newCapacity)
  {
    char * newStr = new char[newCapacity];
    for (size_t i = 0; i < size; ++i)
    {
      newStr[i] = str[i];
    }
    return newStr;
  }

  char * readStr(std::istream & in, size_t & size)
  {
    size_t capacity = 16;
    char * str = new char[capacity];
    size = 0;
    const bool isSkipws = in.flags() & std::ios_base::skipws;
    in >> std::noskipws;
    char ch = 0;
    while (in >> ch && ch != '\n')
    {
      if (size + 1 == capacity)
      {
        char * newStr = nullptr;
        try
        {
          newStr = extend(str, size, capacity * 2);
        }
        catch (const std::bad_alloc &)
        {
          delete[] str;
          if (isSkipws)
          {
            in >> std::skipws;
          }
          throw;
        }
        delete[] str;
        str = newStr;
        capacity *= 2;
      }
      str[size++] = ch;
    }
    str[size] = '\0';
    if (isSkipws)
    {
      in >> std::skipws;
    }
    return str;
  }

    char * latRmv(const char * src, char * result)
  {
    size_t j = 0;
    for (size_t i = 0; src[i] != '\0'; ++i)
    {
      const unsigned char ch = src[i];
      if (!std::isalpha(ch))
      {
        result[j++] = src[i];
      }

    }
    result[j] = '\0';
    return result;
  }

  char * shrSym(const char * str, char * result)
  {
    size_t j = 0;
    for (char letter = 'a'; letter <= 'z'; ++letter)
    {
      size_t i = 0;
      while (str[i] != '\0' && std::tolower(static_cast< unsigned char >(str[i])) != letter)
      {
        ++i;
      }

      if (str[i] == '\0')
      {
        result[j++] = letter;
      }

    }
    result[j] = '\0';
    return result;
  }
}

int main()
{
  size_t size = 0;
  char * str = nullptr;
  try
  {
    str = grebenshchikov::readStr(std::cin, size);
  }
  catch (const std::bad_alloc &)
  {
    std::cerr << "Not enough memory\n";
    return 1;
  }

  const size_t alphabetSize = 26;
  char * latRes = nullptr;
  char * shrRes = nullptr;
  try
  {
    latRes = new char[size + 1];
    shrRes = new char[alphabetSize + 1];
  }
  catch (const std::bad_alloc &)
  {
    std::cerr << "Not enough memory\n";
    delete[] latRes;
    delete[] str;
    return 1;
  }

  std::cout << grebenshchikov::latRmv(str, latRes) << '\n';
  std::cout << grebenshchikov::shrSym(str, shrRes) << '\n';

  delete[] shrRes;
  delete[] latRes;
  delete[] str;
  return 0;
}
