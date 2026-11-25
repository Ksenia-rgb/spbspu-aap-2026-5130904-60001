#include <cctype>
#include <iostream>
#include <memory>
#include <new>

namespace borsch {
  char *removeLatin(const char *source, char *destination);
  int hasSame(const char *first, const char *second);
  std::unique_ptr< char[] > readLine(std::istream &input);
}

char *borsch::removeLatin(const char *source, char *destination)
{
  std::size_t length = 0;
  for (std::size_t i = 0; source[i] != '\0'; ++i) {
    if (!std::isalpha(static_cast< unsigned char >(source[i]))) {
      destination[length] = source[i];
      ++length;
    }
  }
  destination[length] = '\0';
  return destination;
}

int borsch::hasSame(const char *first, const char *second)
{
  const int hasCommon = 1;
  for (std::size_t i = 0; first[i] != '\0'; ++i) {
    for (std::size_t j = 0; second[j] != '\0'; ++j) {
      if (first[i] == second[j]) {
        return hasCommon;
      }
    }
  }
  return 0;
}

std::unique_ptr< char[] > borsch::readLine(std::istream &input)
{
  const std::size_t startCapacity = 16;
  const std::size_t growthFactor = 2;
  std::size_t capacity = startCapacity;
  std::size_t size = 0;
  std::unique_ptr< char[] > line(new char[capacity]);
  char symbol = '\0';
  while (input.get(symbol) && (symbol != '\n')) {
    if ((size + 1) == capacity) {
      const std::size_t newCapacity = capacity * growthFactor;
      std::unique_ptr< char[] > bigger(new char[newCapacity]);
      for (std::size_t i = 0; i < size; ++i) {
        bigger[i] = line[i];
      }
      line.swap(bigger);
      capacity = newCapacity;
    }
    line[size] = symbol;
    ++size;
  }
  line[size] = '\0';
  return line;
}

int main()
{
  try {
    const std::unique_ptr< char[] > line = borsch::readLine(std::cin);
    if (std::cin.bad()) {
      std::cerr << "Input error\n";
      return 2;
    }
  } catch (const std::bad_alloc &) {
    std::cerr << "Not enough memory\n";
    return 1;
  }
  return 0;
}
