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

  char* removeVowels(char* result, const char* source)
  {
    size_t i = 0;
    size_t j = 0;
    while (source[i] != '\0') {
      const unsigned char symbol = static_cast< unsigned char >(source[i]);
      const char lower = static_cast< char >(std::tolower(symbol));
      if (lower != 'a' and lower != 'e' and lower != 'i' and lower != 'o' and lower != 'u') {
        result[j] = source[i];
        ++j;
      }
      ++i;
    }
    result[j] = '\0';
    return result;
  }
}

int main()
{
  char* line = nullptr;
  char* lower_result = nullptr;
  char* no_vowels = nullptr;
  try {
    sudakov::readLine(std::cin, line);
    if (!std::cin and line[0] == '\0') {
      delete[] line;
      std::cerr << "Input is empty\n";
      return 1;
    }
    const size_t result_size = std::strlen(line) + 1;
    lower_result = new char[result_size];
    no_vowels = new char[result_size];
  } catch (const std::bad_alloc&) {
    delete[] no_vowels;
    delete[] lower_result;
    delete[] line;
    std::cerr << "Not enough memory\n";
    return 1;
  }

  sudakov::toLower(lower_result, line);
  sudakov::removeVowels(no_vowels, line);
  std::cout << lower_result << '\n';
  std::cout << no_vowels << '\n';

  delete[] no_vowels;
  delete[] lower_result;
  delete[] line;
}
