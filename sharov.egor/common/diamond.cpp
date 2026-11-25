#include <diamond.hpp>

#include <shape-utils.hpp>

namespace sharov {
  Diamond::Diamond(double horizontalDiagonal, double verticalDiagonal, const point_t &center):
    horizontalDiagonal_(horizontalDiagonal),
    verticalDiagonal_(verticalDiagonal),
    center_(center)
  {
    validatePositive(horizontalDiagonal_, "diamond horizontal diagonal must be positive");
    validatePositive(verticalDiagonal_, "diamond vertical diagonal must be positive");
  }

  double Diamond::getArea() const
  {
    return horizontalDiagonal_ * verticalDiagonal_ * HALF;
  }

  rectangle_t Diamond::getFrameRect() const
  {
    return rectangle_t{horizontalDiagonal_, verticalDiagonal_, center_};
  }

  void Diamond::move(const point_t &position)
  {
    center_ = position;
  }

  void Diamond::move(double dx, double dy)
  {
    center_.x += dx;
    center_.y += dy;
  }

  void Diamond::scale(double coefficient)
  {
    validatePositive(coefficient, "scale coefficient must be positive");
    horizontalDiagonal_ *= coefficient;
    verticalDiagonal_ *= coefficient;
  }

}
