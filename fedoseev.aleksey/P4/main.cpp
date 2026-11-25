#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cctype>

namespace fedoseev {
  char * expand(const char * str, size_t new_size)
  {
    char * result = static_cast< char *>(malloc(sizeof(char) * new_size));
    if (!result)
    {
      std::cerr << "Memory allocation error\n";
      return nullptr;
    }
    
    size_t i = 0;
    for (; str[i] != '\0'; ++i)
    {
      result[i] = str[i];
    }
    result[i] = '\0';
    
    return result;
  }

  char * read_line(size_t * length)
  {
    const size_t default_capacity = 16;
    size_t capacity = default_capacity;
    char * result = static_cast< char *>(malloc(sizeof(char) * capacity));
    if (!result)
    {
      std::cerr << "Memory allocation error\n";
      return nullptr;
    }
    
    char symbol = 0;
    size_t i = 0;
    while (std::cin.get(symbol) && symbol != '\n')
    {
      result[i] = symbol;
      ++i;
      if (i + 1 >= capacity)
      {
        capacity *= 2;
        result[i] = '\0';
        char * temp = result;
        result = expand(temp, capacity);
        if (!result)
        {
          free(temp);
          return nullptr;
        }
        free(temp);
      }
    }
    
    result[i] = '\0';
    * length = i;
    return result;
  }

  void uni_two(const char * str1, size_t len1, const char * str2, size_t len2, char * result)
  {
    size_t index = 0;
    size_t i = 0;
    while (i < len1 || i < len2)
    {
      if (i < len1)
      {
        result[index] = str1[i];
        ++index;
      }
      if (i < len2)
      {
        result[index] = str2[i];
        ++index;
      }
      std::cout << index << "\n";
      ++i;
    }
    result[index] = '\0';
    std::cout << index << "\n";
  }

  void shr_sym(const char * str, char * result)
  {  
    const size_t number_char = 26;
    size_t index = 0;
    for (size_t i = 0; i < number_char; ++i)
    {
      int found = 0;
      for (size_t j = 0; str[j] != '\0'; ++j)
      {
        if (('a' + i == str[j]) || ('A' + i == str[j]))
        {
          found = 1;
          break;
        }
      }
      if (found == 0)
      {
        result[index] = 'a' + i;
        ++index;
      }
    }
    result[index] = '\0';
  }
}

int main()
{
  size_t length1 = 0;
  char * str1 = fedoseev::read_line(&length1);
  if (!str1)
  {
    std::cerr << "Memory allocation error\n";
    return 1;
  }
  const char * str2 = "def_";
  const size_t length2 = std::strlen(str2);

  char * result1 = static_cast< char *>(malloc((length1 + length2 + 1) * sizeof(char)));
  if (!result1)
  {
    std::cerr << "Memory allocation error\n";
    free(str1);
    return 1;
  }
  fedoseev::uni_two(str1, length1, str2, length2, result1);
  std::cout << "UNI-TWO: " << result1 << "\n";
  free(result1);

  char result2[27];
  fedoseev::shr_sym(str1, result2);
  std::cout << "SHR-SYM: " << result2 << "\n";

  free(str1);
  return 0;
}
