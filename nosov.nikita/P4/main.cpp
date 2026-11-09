#include <cctype>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <istream>
#include <new>

namespace nosov {
  char* readLine(std::istream& in)
  {
    const std::size_t growthFactor = 2;
    const std::size_t startCapacity = 16;
    std::size_t capacity = startCapacity;
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
      const int lower = alphabet[i];
      const int upper = std::toupper(lower);
      if ((std::strchr(str, lower) != nullptr) || (std::strchr(str, upper) != nullptr)) {
        ++count;
      }
    }
    return count;
  }

  char* removeVowels(const char* source, char* result)
  {
    const char vowels[] = "aeiou";
    std::size_t resultSize = 0;
    for (std::size_t i = 0; source[i] != '\0'; ++i) {
      const int lower = std::tolower(static_cast< unsigned char >(source[i]));
      if (std::strchr(vowels, lower) == nullptr) {
        result[resultSize] = source[i];
        ++resultSize;
      }
    }
    result[resultSize] = '\0';
    return result;
  }
}

int main()
{
  const char* const line = nosov::readLine(std::cin);
  if (line == nullptr) {
    std::cerr << "Not enough memory\n";
    return 1;
  }
  char* const withoutVowels = new (std::nothrow) char[std::strlen(line) + 1];
  if (withoutVowels == nullptr) {
    delete[] line;
    std::cerr << "Not enough memory\n";
    return 1;
  }
  std::cout << nosov::countDifferentLetters(line) << "\n";
  std::cout << nosov::removeVowels(line, withoutVowels) << "\n";
  delete[] withoutVowels;
  delete[] line;
  return 0;
}
