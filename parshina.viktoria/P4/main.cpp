#include <cctype>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <limits>
#include <new>

namespace parshina
{
  char * excludeSecondCharacters(const char * source, const char * second, char * result);
  char * removeVowels(const char * sourse, char * result);
}

char * parshina::excludeSecondCharacters(const char * sourse, const char * second, char * result)
{
  size_t i = 0;
  size_t j = 0;

  while (sourse[i] != '\0')
  {
    if (std::strchr(second, sourse[i]) == nullptr)
    {
      result[j] = sourse[i];
      ++j;
    }
    ++i;
  }

  result[j] = '\0';
  return result;
}

char * parshina::removeVowels(const char * source, char * result)
{
  size_t i = 0;
  size_t j = 0;

  while (source[i] != '\0')
  {
    const unsigned char symbol = source[i];
    const int lower = std::tolower(symbol);

    if (std::strchr("aeiouy", lower) == nullptr)
    {
      result[j] = source[i];
      ++j;
    }
    ++i;
  }

  result[j] = '\0';
  return result;
}

int main()
{
  const size_t initial_capacity = 16;
  size_t capacity = initial_capacity;
  char * input_str = new (std::nothrow) char[capacity];

  if (input_str == nullptr)
  {
    std::cerr << "Not enough memory\n";
    return 1;
  }

  size_t length = 0;
  char symbol = '\0';

  while (std::cin.get(symbol) && symbol != '\n')
  {
    if (length == capacity - 1)
    {
      if (capacity > std::numeric_limits< size_t >::max() / 2)
      {
        delete[] input_str;
        std::cerr << "Not enough memory\n";
        return 1;
      }

      capacity *= 2;
      char * const extended = new (std::nothrow) char[capacity];

      if (extended == nullptr)
      {
        delete[] input_str;
        std::cerr << "Not enough memory\n";
        return 1;
      }

      for (size_t i = 0; i < length; ++i)
      {
        extended[i] = input_str[i];
      }

      delete[] input_str;
      input_str = extended;
    }

    input_str[length] = symbol;
    ++length;
  }

  if (!std::cin)
  {
    delete[] input_str;
    std::cerr << "Input error\n";
    return 1;
  }

  input_str[length] = '\0';
  char * const result = new (std::nothrow) char[length + 1];

  if (result == nullptr)
  {
    delete[] input_str;
    std::cerr << "Not enough memory\n";
    return 1;
  }

  const char * const second = "abc";
  std::cout << parshina::excludeSecondCharacters(input_str, second, result) << '\n';
  std::cout << parshina::removeVowels(input_str, result) << '\n';

  if (!std::cout)
  {
    delete[] result;
    delete[] input_str;
    std::cerr << "Output error\n";
    return 1;
  }

  delete[] result;
  delete[] input_str;
  return 0;
}
