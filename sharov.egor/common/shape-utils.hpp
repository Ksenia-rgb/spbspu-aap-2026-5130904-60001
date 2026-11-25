#ifndef SHAPE_UTILS_HPP
#define SHAPE_UTILS_HPP

#include <stdexcept>

namespace sharov {
  constexpr double PI = 3.14159265358979323846;
  constexpr double HALF = 0.5;
  constexpr double DIAMETER_FACTOR = 2.0;
  constexpr double TRIANGLE_VERTEX_COUNT = 3.0;

  inline void validatePositive(double value, const char *const message)
  {
    if (!(value > 0.0)) {
      throw std::invalid_argument(message);
    }
  }
}

#endif
