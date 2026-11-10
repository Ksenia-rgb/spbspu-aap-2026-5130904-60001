#include <iostream>
#include <cstring>

namespace tretyakov
{
  char * resize(char * string1, size_t &capacity)
  {
    size_t new_capacity = capacity * 2;
    char * new_string = new char[new_capacity];
    std::memcpy(new_string, string1, capacity);
    delete [] string1;
    capacity = new_capacity;
    return new_string;
  }
  char * readStr(size_t &capacity, size_t &size1)
  {
    char * string1 = new char[capacity];
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
}

int main()
{
  const char * const string2 = "def ";
  size_t size2 = std::strlen(string2);
  const char * const string3 = "abs";
  size_t capacity = 16;
  size_t size1 = 0;
  char * string1 = nullptr;
  char * sum_string = nullptr;
  try
  {
    string1 = tretyakov::readStr(capacity, size1);
    sum_string = new char[size1 + size2 + 1];
  }
  catch (const std::bad_alloc &)
  {
    std::cerr << "Error: failed memory allocation\n";
    delete [] string1;
    return 1;
  }
  if (size1 == 0)
  {
    std::cerr << "Empty input\n";
    delete [] string1;
    delete [] sum_string;
    return 1;
  }
  return 0;
}