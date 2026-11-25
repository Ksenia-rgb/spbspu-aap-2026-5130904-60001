#include "string-io.hpp"

#include <climits>
#include <istream>
#include <new>

namespace sharov {
  namespace {
    constexpr int kInitialCapacity = 16;
    constexpr int kGrowthFactor = 2;
  }

  char *readString(std::istream &input, int *const length)
  {
    int capacity = kInitialCapacity;
    char *buffer = nullptr;
    try {
      buffer = new char[capacity];
    } catch (const std::bad_alloc &) {
      return nullptr;
    }

    int size = 0;
    char character = '\0';
    input >> std::noskipws;
    while (input.get(character)) {
      if (character == '\n') {
        break;
      }
      if (size + 1 >= capacity) {
        if (capacity > INT_MAX / kGrowthFactor) {
          delete[] buffer;
          return nullptr;
        }
        const int newCapacity = capacity * kGrowthFactor;
        char *grown = nullptr;
        try {
          grown = new char[newCapacity];
        } catch (const std::bad_alloc &) {
          delete[] buffer;
          return nullptr;
        }
        for (int i = 0; i < size; ++i) {
          grown[i] = buffer[i];
        }
        delete[] buffer;
        buffer = grown;
        capacity = newCapacity;
      }
      buffer[size] = character;
      ++size;
    }
    buffer[size] = '\0';
    if (length != nullptr) {
      *length = size;
    }
    return buffer;
  }
}
