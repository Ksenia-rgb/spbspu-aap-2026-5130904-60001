#include <cstdlib>
#include <iostream>

namespace kotyurgina
{
  char * readLine();
}

char * kotyurgina::readLine()
{
  const size_t initialCapacity = 16;
  const size_t maxCapacity = static_cast< size_t >(-1);
  size_t capacity = initialCapacity;

  char * str = static_cast< char * >(std::malloc(capacity));
  if (str == nullptr)
  {
    return nullptr;
  }

  size_t size = 0;
  char ch = '\0';

  while (std::cin.get(ch) && ch != '\n')
  {
    if (size + 1 >= capacity)
    {
      if (capacity > maxCapacity / 2)
      {
        std::free(str);
        return nullptr;
      }

      const size_t newCapacity = capacity * 2;
      char * newStr = static_cast< char * >(std::malloc(newCapacity));

      if (newStr == nullptr)
      {
        std::free(str);
        return nullptr;
      }

      for (size_t i = 0; i < size; ++i)
      {
        newStr[i] = str[i];
      }

      std::free(str);
      str = newStr;
      capacity = newCapacity;
    }

    str[size] = ch;
    ++size;
  }

  str[size] = '\0';
  return str;
}

int main()
{
  char * str = kotyurgina::readLine();

  if (str == nullptr)
  {
    std::cerr << "Memory allocation error\n";
    return 1;
  }

  std::cout << str << '\n';
  std::free(str);
  return 0;
}