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
  const size_t maxСapacity = static_cast< size_t >(-1);
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
      if (capacity > maxСapacity / 2)
      {
        std::free(str);
        return nullptr;
      }

      const size_t new_capacity = capacity * 2;
      char* const new_str = static_cast< char* >(std::malloc(new_capacity));

      if (new_str == nullptr)
      {
        std::free(str);
        return nullptr;
      }

      for (size_t i = 0; i < size; ++i)
      {
        new_str[i] = str[i];
      }

      std::free(str);
      str = new_str;
      capacity = new_capacity;
    }

    str[size] = ch;
    ++size;
  }
  if (!std::cin)
  {
    std::free(str);
    return nullptr;
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
  char* const str = kotyurgina::readLine();

  if (str == nullptr)
  {
    std::cerr << "Input or memory allocation error\n";
    return 1;
  }

  std::cout << kotyurgina::hasSame(str, "abs") << '\n';
  std::free(str);
  return 0;
}
