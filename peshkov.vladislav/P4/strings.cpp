#include "strings.hpp"
#include <cctype>
#include <cstring>
#include <new>

char* readLine(std::istream* in, size_t* out_len)
{
  constexpr size_t initial_capacity = 16;
  size_t capacity = initial_capacity;
  char* buffer = new (std::nothrow) char[capacity];
  if (buffer == nullptr) {
    return nullptr;
  }
  size_t length = 0;
  char ch = 0;
  while (in->get(ch) && ch != '\n') {
    if (length + 1 == capacity) {
      const size_t new_capacity = capacity * 2;
      char* const bigger = new (std::nothrow) char[new_capacity];
      if (bigger == nullptr) {
        delete[] buffer;
        return nullptr;
      }
      std::memcpy(bigger, buffer, length);
      delete[] buffer;
      buffer = bigger;
      capacity = new_capacity;
    }
    buffer[length] = ch;
    ++length;
  }
  buffer[length] = '\0';
  *out_len = length;
  return buffer;
}

int hasSam(const char* str1, const char* str2)
{
  for (const char* i = str1; *i != '\0'; ++i) {
    for (const char* j = str2; *j != '\0'; ++j) {
      if (*i == *j) {
        return 1;
      }
    }
  }
  return 0;
}

size_t countDgt(const char* str)
{
  size_t count = 0;
  for (const char* i = str; *i != '\0'; ++i) {
    if (std::isdigit(static_cast< unsigned char >(*i))) {
      ++count;
    }
  }
  return count;
}

char* dgtSnd(char* dst, const char* src1, const char* src2)
{
  size_t pos = 0;
  for (const char* i = src1; *i != '\0'; ++i) {
    dst[pos] = *i;
    ++pos;
  }
  for (const char* i = src2; *i != '\0'; ++i) {
    if (std::isdigit(static_cast< unsigned char >(*i))) {
      dst[pos] = *i;
      ++pos;
    }
  }
  dst[pos] = '\0';
  return dst;
}
