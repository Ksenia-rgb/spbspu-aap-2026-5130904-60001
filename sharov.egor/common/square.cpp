#include <square.hpp>

#include <shape-utils.hpp>

namespace sharov {
  Square::Square(double side, const point_t &center):
    side_(side),
    center_(center)
  {
    validatePositive(side_, "square side must be positive");
  }

  double Square::getArea() const
  {
    return side_ * side_;
  }

  rectangle_t Square::getFrameRect() const
  {
    return rectangle_t{side_, side_, center_};
  }

  void Square::move(const point_t &position)
  {
    center_ = position;
  }

  void Square::move(double dx, double dy)
  {
    center_.x += dx;
    center_.y += dy;
  }

  void Square::scale(double coefficient)
  {
    validatePositive(coefficient, "scale coefficient must be positive");
    side_ *= coefficient;
  }

}
