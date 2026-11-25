#include <climits>
#include <iostream>
#include <new>

#include "string-io.hpp"
#include "variants.hpp"

namespace sharov {
  namespace {
    constexpr int kResultCapacityReserve = 32;
  }

  int runLab()
  {
    int sourceLength = 0;
    const char *const source = readString(std::cin, &sourceLength);
    if (source == nullptr) {
      std::cerr << "error: cannot allocate memory for the input string\n";
      return 1;
    }

    if (sourceLength > INT_MAX - kResultCapacityReserve) {
      delete[] source;
      std::cerr << "error: the input string is too long\n";
      return 1;
    }

    const int resultCapacity = sourceLength + kResultCapacityReserve;
    char *result = nullptr;
    try {
      result = new char[resultCapacity];
    } catch (const std::bad_alloc &) {
      delete[] source;
      std::cerr << "error: cannot allocate memory for the result\n";
      return 1;
    }

    int exitCode = 0;
    const int activeCount = getActiveVariantCount();
    for (int i = 0; i < activeCount; ++i) {
      const char *const name = getActiveVariant(i);
      const int resultLength = applyVariant(name, source, result, resultCapacity);
      if (resultLength < 0) {
        std::cerr << "error: cannot apply variant " << name << "\n";
        exitCode = 1;
        break;
      }
      std::cout << result << "\n";
    }

    delete[] result;
    delete[] source;
    return exitCode;
  }
}

int main()
{
  return sharov::runLab();
}
