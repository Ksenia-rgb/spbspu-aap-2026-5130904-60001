#include <cstdlib>
#include <iostream>

namespace kotyurgina
{
  char* readLine();
  int hasSame(const char* str1, const char* str2);
}

char* kotyurgina::readLine()
{
  const size_t initialCapacity = 16;
  const size_t maxCapacity = static_cast< size_t >(-1);
  size_t capacity = initialCapacity;

  char* str = static_cast< char* >(std::malloc(capacity));
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
      char* newStr = static_cast< char* >(std::malloc(newCapacity));

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

int kotyurgina::hasSame(const char* str1, const char* str2)
{
  for (size_t i = 0; str1[i] != '\0'; ++i)
  {
    for (size_t j = 0; str2[j] != '\0'; ++j)
    {
      if (str1[i] == str2[j])
      {
        return 1;
      }
    }
  }
  return 0;
}

int main()
{
  char* str = kotyurgina::readLine();

  if (str == nullptr)
  {
    std::cerr << "Memory allocation error\n";
    return 1;
  }

  std::cout << kotyurgina::hasSame(str, "abs") << '\n';
  std::free(str);
  return 0;
}