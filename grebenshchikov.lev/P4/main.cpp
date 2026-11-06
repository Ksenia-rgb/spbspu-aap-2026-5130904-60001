#include <iostream>
#include <istream>
#include <cstddef>
#include <new>

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
        char *newStr = nullptr;
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
}

int main()
{
  size_t size = 0;
  char *str = nullptr;
  try
  {
    str = grebenshchikov::readStr(std::cin, size);
  }
  catch (const std::bad_alloc &)
  {
    std::cerr << "Not enough memory\n";
    return 1;
  }

  delete[] str;
  return 0;
}
