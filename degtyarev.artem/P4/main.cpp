#include <iostream>
#include <algorithm>
#include <cstddef>


char *resize(char *str, size_t &cupacity)
{
  size_t new_cupacity = cupacity * 2;
  char *new_str = new char[new_cupacity];
  for (size_t i = 0; i < cupacity; ++i)
  {
    new_str[i] = str[i];
  }
  delete[] str;
  cupacity = new_cupacity;
  return new_str;
}

char *Read_str(size_t &cupacity, size_t &size)
{
  char *str = new char[cupacity];
  char current = '0';
  while (std::cin.get(current) && current != '\n')
  {
    if (size + 1 >= cupacity)
    { 
      try
      {
        str = resize(str, cupacity);
      }
      catch (const std::bad_alloc &)
      {
        delete[] str;
        throw;
      }
      
    }
    str[size++] = current;
  }
  str[size] = '\0';
  return str;
}

char* UNI_TWO(const char *str, const char *str2, size_t size, size_t size2, char *sumstr)
{ 
  size_t cnt = 0;
  for (size_t i = 0; i < std::min(size, size2); ++i)
  {
    sumstr[cnt++] = str[i];
    sumstr[cnt++] = str2[i];
  }
  if (size > size2)
  {
    for (size_t i = size2; i < size; ++i)
    {
      sumstr[cnt++] = str[i];
    }
  }
  else
  {
    for (size_t i = size; i < size2; ++i)
    {
      sumstr[cnt++] = str2[i];
    }
  }
  sumstr[cnt] = '\0';
  return sumstr;
}

int main()
{ 
  size_t cupacity = 1;
  size_t size = 0;
  const char *str = nullptr;
  try
  {
    str = Read_str(cupacity, size);
  }
  catch (const std::bad_alloc &e)
  {
    std::cerr << "Memory allocation error: " << e.what() << '\n';
    return 1;
  }
  const char *str2 = "def ";
  size_t size2 = 4;
  char *sumstr = nullptr;
  try
  {
    sumstr = new char[size + size2 + 1];
  }
  catch (const std::bad_alloc &e)
  {
    std::cerr << "Memory allocation error: " << e.what() << '\n';
    delete[] str;
    return 1;
  }
  
  std::cout << UNI_TWO(str, str2, size, size2, sumstr) << '\n';
  delete[] str;
  delete[] sumstr;
}
