#include <cctype>
#include <cstddef>
#include <iostream>
#include <new>

namespace ignashev {
  char* readLine(std::istream& in);
  size_t getStringLength(const char* str);
  int hasRepeatedDigits(const char* str);
  char* removeVowels(char* dest, const char* src);
}

namespace {
  int isLatinVowel(char ch)
  {
    const unsigned char uch = static_cast< unsigned char >(ch);
    if (!std::isalpha(uch)) {
      return 0;
    }
    const int lower = std::tolower(uch);
    const int is_first_group = (lower == 'a') || (lower == 'e') || (lower == 'i');
    const int is_second_group = (lower == 'o') || (lower == 'u') || (lower == 'y');
    return (is_first_group || is_second_group) ? 1 : 0;
  }
}

char* ignashev::readLine(std::istream& in)
{
  const size_t initial_capacity = 16;
  const size_t growth_factor = 2;
  const size_t null_term_space = 1;
  size_t capacity = initial_capacity;
  size_t length = 0;
  char* buffer = new char[capacity];
  char current = 0;

  in >> std::noskipws;
  while ((in >> current) && (current != '\n')) {
    if (length + null_term_space == capacity) {
      const size_t new_capacity = capacity * growth_factor;
      char* new_buffer = nullptr;
      try {
        new_buffer = new char[new_capacity];
      } catch (const std::bad_alloc&) {
        delete[] buffer;
        throw;
      }
      for (size_t i = 0; i < length; ++i) {
        new_buffer[i] = buffer[i];
      }
      delete[] buffer;
      buffer = new_buffer;
      capacity = new_capacity;
    }
    buffer[length] = current;
    ++length;
  }
  in >> std::skipws;

  if ((length == 0) && (!in)) {
    delete[] buffer;
    return nullptr;
  }

  buffer[length] = '\0';
  return buffer;
}

size_t ignashev::getStringLength(const char* str)
{
  size_t length = 0;
  while (str[length] != '\0') {
    ++length;
  }
  return length;
}

int ignashev::hasRepeatedDigits(const char* str)
{
  const size_t digits_count = 10;
  const int found = 1;
  const int not_found = 0;
  size_t counts[digits_count] = {};

  for (size_t i = 0; str[i] != '\0'; ++i) {
    const unsigned char uch = static_cast< unsigned char >(str[i]);
    if (std::isdigit(uch)) {
      const size_t digit_index = static_cast< size_t >(str[i] - '0');
      ++counts[digit_index];
      if (counts[digit_index] > found) {
        return found;
      }
    }
  }
  return not_found;
}

char* ignashev::removeVowels(char* dest, const char* src)
{
  size_t dest_index = 0;
  for (size_t i = 0; src[i] != '\0'; ++i) {
    if (isLatinVowel(src[i]) == 0) {
      dest[dest_index] = src[i];
      ++dest_index;
    }
  }
  dest[dest_index] = '\0';
  return dest;
}

int main()
{
  char* input = nullptr;
  try {
    input = ignashev::readLine(std::cin);
  } catch (const std::bad_alloc&) {
    std::cerr << "Memory allocation failed\n";
    return 1;
  }

  if (input == nullptr) {
    std::cerr << "Failed to read input string\n";
    return 1;
  }

  const size_t null_term_space = 1;
  const size_t length = ignashev::getStringLength(input);
  char* without_vowels = nullptr;
  try {
    without_vowels = new char[length + null_term_space];
  } catch (const std::bad_alloc&) {
    delete[] input;
    std::cerr << "Memory allocation failed\n";
    return 1;
  }

  const int repeated_digits = ignashev::hasRepeatedDigits(input);
  ignashev::removeVowels(without_vowels, input);

  std::cout << repeated_digits << '\n';
  std::cout << without_vowels << '\n';

  delete[] without_vowels;
  delete[] input;
  return 0;
}
