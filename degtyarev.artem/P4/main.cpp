#include <iostream>
#include <algorithm>
#include <cstddef>
#include <cctype>
#include <cstring>

namespace degtyarev
{
  char *resize(const char *str, size_t &capacity)
  {
    const size_t new_capacity = capacity * 2;
    char *const new_str = new char[new_capacity];
    for (size_t i = 0; i < capacity; ++i)
    {
      new_str[i] = str[i];
    }
    delete[] str;
    capacity = new_capacity;
    return new_str;
  }

  char *readStr(size_t &capacity, size_t &size)
  {
    char *str = new char[capacity];
    char current = '\0';
    while (std::cin.get(current) && current != '\n')
    {
      if (size + 1 >= capacity)
      {
        try
        {
          str = resize(str, capacity);
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

  char *uniTwo(const char *str, const char *str2, size_t size, size_t size2, char *sumstr)
  {
    size_t cnt = 0;
    const size_t min_size = std::min(size, size2);
    for (size_t i = 0; i < min_size; ++i)
    {
      sumstr[cnt++] = str[i];
      sumstr[cnt++] = str2[i];
    }
    for (size_t i = min_size; i < size; ++i)
    {
      sumstr[cnt++] = str[i];
    }
    for (size_t i = min_size; i < size2; ++i)
    {
      sumstr[cnt++] = str2[i];
    }
    sumstr[cnt] = '\0';
    return sumstr;
  }

  char *shrSym(const char *str, size_t size, char *res)
  {
    size_t cnt = 0;
    for (char c = 'a'; c <= 'z'; ++c)
    {
      int flag = 0;
      for (size_t i = 0; i < size; ++i)
      {
        if (std::tolower(static_cast< unsigned char >(str[i])) == c)
        {
          ++flag;
          break;
        }
      }
      if (flag == 0)
      {
        res[cnt++] = c;
      }
    }
    res[cnt] = '\0';
    return res;
  }
}

int main()
{
  const char *const str2 = "def ";
  const size_t size2 = std::strlen(str2);

  size_t capacity = 1;
  size_t size = 0;
  char *str = nullptr;
  char *sumstr = nullptr;
  try
  {
    str = degtyarev::readStr(capacity, size);
    sumstr = new char[size + size2 + 1];
  }
  catch (const std::bad_alloc &e)
  {
    std::cerr << "Memory allocation error: " << e.what() << '\n';
    delete[] str;
    return 1;
  }
  if (size == 0)
  {
    std::cerr << "Empty input\n";
    delete[] str;
    delete[] sumstr;
    return 1;
  }

  const size_t alphabet_size = 26;
  char res[alphabet_size + 1] = {};
  std::cout << degtyarev::uniTwo(str, str2, size, size2, sumstr) << '\n';
  std::cout << degtyarev::shrSym(str, size, res) << '\n';
  delete[] str;
  delete[] sumstr;
  return 0;
}
