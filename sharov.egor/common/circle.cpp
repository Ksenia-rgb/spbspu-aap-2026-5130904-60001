#include <circle.hpp>

#include <shape-utils.hpp>

namespace sharov {
  Circle::Circle(double radius, const point_t &center):
    radius_(radius),
    center_(center)
  {
    validatePositive(radius_, "circle radius must be positive");
  }

  double Circle::getArea() const
  {
    return PI * radius_ * radius_;
  }

  rectangle_t Circle::getFrameRect() const
  {
    return rectangle_t{DIAMETER_FACTOR * radius_, DIAMETER_FACTOR * radius_, center_};
  }

  void Circle::move(const point_t &position)
  {
    center_ = position;
  }

  void Circle::move(double dx, double dy)
  {
    center_.x += dx;
    center_.y += dy;
  }

  void Circle::scale(double coefficient)
  {
    validatePositive(coefficient, "scale coefficient must be positive");
    radius_ *= coefficient;
  }

}
