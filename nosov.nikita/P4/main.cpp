#include <cstddef>
#include <cstring>
#include <iostream>
#include <new>

namespace nosov {
  char* readLine(std::istream& in)
  {
    const std::size_t growthFactor = 2;
    std::size_t capacity = 16;
    char* line = new (std::nothrow) char[capacity];
    if (line == nullptr) {
      return nullptr;
    }
    std::size_t size = 0;
    char symbol = '\0';
    while (in.get(symbol) && (symbol != '\n')) {
      if (size + 1 == capacity) {
        const std::size_t newCapacity = capacity * growthFactor;
        char* const newLine = new (std::nothrow) char[newCapacity];
        if (newLine == nullptr) {
          delete[] line;
          return nullptr;
        }
        std::memcpy(newLine, line, size);
        delete[] line;
        line = newLine;
        capacity = newCapacity;
      }
      line[size] = symbol;
      ++size;
    }
    line[size] = '\0';
    return line;
  }

  std::size_t countDifferentLetters(const char* str)
  {
    const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    std::size_t count = 0;
    for (std::size_t i = 0; alphabet[i] != '\0'; ++i) {
      if (std::strchr(str, alphabet[i]) != nullptr) {
        ++count;
      }
    }
    return count;
  }
}

int main()
{
  char* const line = nosov::readLine(std::cin);
  if (line == nullptr) {
    std::cerr << "Not enough memory\n";
    return 1;
  }
  std::cout << nosov::countDifferentLetters(line) << "\n";
  delete[] line;
  return 0;
}
