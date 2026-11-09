#include <cstddef>
#include <iostream>
#include <new>

namespace nosov {
  char* readLine(std::istream& in)
  {
    const std::size_t capacity = 16;
    char* const line = new (std::nothrow) char[capacity];
    if (line == nullptr) {
      return nullptr;
    }
    std::size_t size = 0;
    char symbol = '\0';
    while ((size + 1 < capacity) && in.get(symbol) && (symbol != '\n')) {
      line[size] = symbol;
      ++size;
    }
    line[size] = '\0';
    return line;
  }
}

int main()
{
  char* const line = nosov::readLine(std::cin);
  if (line == nullptr) {
    std::cerr << "Not enough memory\n";
    return 1;
  }
  std::cout << line << "\n";
  delete[] line;
  return 0;
}
