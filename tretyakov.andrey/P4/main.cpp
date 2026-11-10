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
  return 0;
}