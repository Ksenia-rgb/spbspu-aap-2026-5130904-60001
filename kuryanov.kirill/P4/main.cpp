#include <iostream>
#include <cstddef>

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
  char * readline (size_t & size)
  {
    size_t capacity = 8;
    char * str = new char[capacity];
    char cur;
    while (std::cin.get(cur) && cur != '\n') {
      if (size + 1 >= capacity) {
        str = resize(str, capacity, size);
      }

      str[size++] = cur;
    }
    str[size] = '\0';
    return str;
  }
// a -- z [97 -- 122]
// A -- Z [65 -- 90]
// [0 -- 25]
  char * latTwo(const char * str1, size_t size1,
                const char * str2, size_t size2,
                char * out) noexcept
  {
    size_t result_size = 0;
    for (char letter = 'a'; letter <= 'z'; ++letter) {
      bool is_found = false;

      for (size_t i = 0; i < size1; ++i) {
        if (str1[i] == letter || str1[i] == letter - 'a' + 'A') {
          is_found = true;
          break;
        }
      }
      if (!is_found) {
        for (size_t j = 0; j < size2; ++j) {
          if (str2[j] == letter || str2[j] == letter - 'a' + 'A') {
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
  size_t st_size = 0;
  size_t nd_size = 0;
  const size_t num_let = 26;

  char * st_string = kuryanov::readline(st_size);
  char * nd_string = kuryanov::readline(nd_size);
  std::cout << "\n";
  char *sumstr = new char [st_size + nd_size + 1];
  char *letstr = new char [num_let + 1]{};
  std::cout << kuryanov::latTwo(st_string, st_size, nd_string, nd_size, letstr) << "\n";
  std::cout << "\n";
  std::cout << kuryanov::uniTwo(st_string, st_size, nd_string, nd_size, sumstr) << "\n";
  std::cout << "\n";
  for (size_t i= 0; i < st_size; ++i) {
    std::cout << st_string[i];
  }
  std::cout << "\n";
  for (size_t i= 0; i < nd_size; ++i) {
    std::cout << nd_string[i];
  }
  std::cout << "\n";
  delete[] st_string;
  delete[] nd_string;
  delete[] sumstr;
  delete[] letstr;

  return 0;


}
