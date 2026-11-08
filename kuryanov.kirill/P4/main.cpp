#include <iostream>
#include <cstddef>
#include <cctype>
#include <cstring>

namespace kuryanov {
  char * resize(char * arr, size_t & capacity, size_t & size)
  {
    size_t new_capacity = capacity * 2;
    char * result = new char[new_capacity];
    for (size_t i = 0; i < size; i++) {
      result[i] = arr[i];
    }
    delete[] arr;
    capacity = new_capacity;
    return result;
  }
  char * readline(size_t & size)
  {
    size = 0;
    size_t capacity = 8;
    char * str = new char[capacity];
    char cur = '\n';
    try {
      while (std::cin.get(cur) && cur != '\n') {
        if (size + 1 >= capacity) {
          str = resize(str, capacity, size);
        }

        str[size++] = cur;
      }
      str[size] = '\0';
      return str;
    }
    catch (const std::bad_alloc &) {
      delete[] str;
      throw;
    }
  }

  char * latTwo(const char * str1, size_t size1,
                const char * str2, size_t size2,
                char * out) noexcept
  {
    size_t result_size = 0;
    for (char letter = 'a'; letter <= 'z'; ++letter) {
      bool is_found = false;

      for (size_t i = 0; i < size1; ++i) {
        if (std::tolower(static_cast<unsigned char>(str1[i])) == letter) {
          is_found = true;
          break;
        }
      }
      if (!is_found) {
        for (size_t j = 0; j < size2; ++j) {
          if (std::tolower(static_cast<unsigned char>(str2[j])) == letter) {
            is_found = true;
            break;
          }
        }
      }

      if (is_found) {
        out[result_size++] = letter;
      }
    }
    out[result_size] = '\0';
    return out;
  }
  char * uniTwo(const char * str1, size_t size1,
                const char * str2, size_t size2,
                char * out) noexcept
  {
    size_t i = 0;
    size_t i1 = 0;
    size_t i2 = 0;

    while (i1 < size1 || i2 < size2) {
      if (i1 < size1) {
        out[i++] = str1[i1++];
      }
      if (i2 < size2) {
        out[i++] = str2[i2++];
      }
    }

    out[i] = '\0';
    return out;
  }

}
int main()
{
  const size_t num_let = 26;
  const char * nd_string = "def ghk";
  size_t st_size = 0;
  char * st_string = nullptr;
  char * sumstr = nullptr;
  try {
    st_string = kuryanov::readline(st_size);
    size_t nd_size = std::strlen(nd_string);
    sumstr = new char [st_size + nd_size + 1];
    char letstr[num_let + 1] = {};

    std::cout << kuryanov::latTwo(st_string, st_size, nd_string, nd_size, letstr) << "\n";

    std::cout << kuryanov::uniTwo(st_string, st_size, nd_string, nd_size, sumstr) << "\n";
  }
  catch (const std::bad_alloc &) {
    std::cerr << "Memory allocation failed\n";
    delete[] st_string;
    delete[] sumstr;
    return 1;
  }

  delete[] st_string;
  delete[] sumstr;

  return 0;
}
