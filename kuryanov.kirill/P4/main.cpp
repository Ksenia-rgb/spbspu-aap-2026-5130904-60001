#include <iostream>
#include <cstddef>
namespace kuryanov {
  char * resize(char * arr, size_t & capacity, size_t & size) {
    size_t new_capacity = capacity * 2;
    char * result = new char[new_capacity];
    for (size_t i = 0; i < size; i++) {
      result[i] = arr[i];
    }
    delete[] arr;
    capacity = new_capacity;
    return result;
  }
  char * readline (size_t & capacity, size_t & size) {
    char * str = new char[capacity];
    char cur;
    while (std::cin.get(cur) && cur != '\n') {
      if (size == capacity) {
        str = resize(str, capacity, size);
      }

      str[size++] = cur;
    }
    return str;
  }

}
int main()
{
  size_t cap = 1;
  size_t size = 0;
  char * string = kuryanov::readline(cap, size);
  std::cout << size << " " << cap << "\n";
  for (size_t i= 0; i < size; ++i) {
    std::cout << string[i];
  }
  std::cout << "\n";
  delete[] string;

}
