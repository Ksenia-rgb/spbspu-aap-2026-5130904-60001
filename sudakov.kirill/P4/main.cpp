#include <cctype>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <new>

namespace sudakov {
  std::istream& readLine(std::istream& input, char*& line)
  {
    size_t capacity = 10;
    size_t size = 0;
    line = new char[capacity];

    char symbol = '\0';
    while (input.get(symbol) and symbol != '\n') {
      if (size + 1 == capacity) {
        capacity *= 2;
        char* const new_line = new char[capacity];
        for (size_t i = 0; i < size; ++i) {
          new_line[i] = line[i];
        }
        delete[] line;
        line = new_line;
      }
      line[size] = symbol;
      ++size;
    }
    line[size] = '\0';
    return input;
  }

  char* toLower(char* result, const char* source)
  {
    size_t i = 0;
    while (source[i] != '\0') {
      const unsigned char symbol = static_cast< unsigned char >(source[i]);
      result[i] = static_cast< char >(std::tolower(symbol));
      ++i;
    }
    result[i] = '\0';
    return result;
  }
}

int main()
{
  char* line = nullptr;
  char* result = nullptr;
  try {
    sudakov::readLine(std::cin, line);
    if (!std::cin and line[0] == '\0') {
      delete[] line;
      std::cerr << "Input is empty\n";
      return 1;
    }
    result = new char[std::strlen(line) + 1];
  } catch (const std::bad_alloc&) {
    delete[] line;
    std::cerr << "Not enough memory\n";
    return 1;
  }

  sudakov::toLower(result, line);
  std::cout << result << '\n';

  delete[] result;
  delete[] line;
}
