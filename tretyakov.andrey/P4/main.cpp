#include <iostream>
#include <cstring>

namespace tretyakov
{
  char *resize(char *string1, size_t &capacity)
  {
    const size_t new_capacity = capacity * 2;
    char *const new_string = new char[new_capacity];
    std::memcpy(new_string, string1, capacity);
    delete[] string1;
    capacity = new_capacity;
    return new_string;
  }
  char *readStr(size_t &capacity, size_t &size1)
  {
    char *string1 = new char[capacity];
    char current = '\0';
    while (std::cin.get(current) && current != '\n')
    {
      if (size1 + 1 >= capacity)
      {
        string1 = resize(string1, capacity);
      }
      string1[size1++] = current;
    }
    string1[size1] = '\0';
    return string1;
  }
  char *uniTwo(const char *string1, const char *string2, size_t size1, size_t size2, char *sum_string)
  {
    size_t i = 0;
    size_t j = 0;
    while (i < size1 && j < size2)
    {
      sum_string[i + j] = string1[i];
      ++i;
      sum_string[i + j] = string2[j];
      ++j;
    }
    while (i < size1)
    {
      sum_string[i + j] = string1[i];
      ++i;
    }
    while (j < size2)
    {
      sum_string[i + j] = string2[j];
      ++j;
    }
    sum_string[i + j] = '\0';
    return sum_string;
  }
  char *hasSam(const char *string1, const char *string2, size_t size1, char *res)
  {
    int found = 0;
    for (size_t i = 0; i < size1; ++i)
    {
      for (size_t j = 0; string2[j] != '\0'; ++j)
      {
        if (string1[i] == string2[j])
        {
          found = 1;
          break;
        }
      }
      if (found)
      {
        break;
      }
    }
    if (found)
    {
      res[0] = '1';
    }
    else
    {
      res[0] = '0';
    }
    res[1] = '\0';
    return res;
  }
}

int main()
{
  const size_t initial_capacity = 16;
  const char *const string2 = "def ";
  const size_t size2 = std::strlen(string2);
  const char *const string3 = "abs";
  size_t capacity = initial_capacity;
  size_t size1 = 0;
  char *string1 = nullptr;
  char *sum_string = nullptr;
  try
  {
    string1 = tretyakov::readStr(capacity, size1);
    sum_string = new char[size1 + size2 + 1];
  }
  catch (const std::bad_alloc &)
  {
    std::cerr << "Error: failed memory allocation\n";
    delete[] string1;
    return 1;
  }
  if (size1 == 0)
  {
    std::cerr << "Empty input\n";
    delete[] string1;
    delete[] sum_string;
    return 1;
  }
  char res[2] = {};
  std::cout << tretyakov::uniTwo(string1, string2, size1, size2, sum_string) << "\n";
  std::cout << tretyakov::hasSam(string1, string3, size1, res) << "\n";
  delete[] string1;
  delete[] sum_string;
  return 0;
}
