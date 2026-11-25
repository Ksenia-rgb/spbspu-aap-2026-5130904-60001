#include <ellipse.hpp>

#include <shape-utils.hpp>

namespace sharov {
  Ellipse::Ellipse(double horizontalRadius, double verticalRadius, const point_t &center):
    horizontalRadius_(horizontalRadius),
    verticalRadius_(verticalRadius),
    center_(center)
  {
    validatePositive(horizontalRadius_, "ellipse horizontal radius must be positive");
    validatePositive(verticalRadius_, "ellipse vertical radius must be positive");
  }

  double Ellipse::getArea() const
  {
    return PI * horizontalRadius_ * verticalRadius_;
  }

  rectangle_t Ellipse::getFrameRect() const
  {
    return rectangle_t{DIAMETER_FACTOR * horizontalRadius_, DIAMETER_FACTOR * verticalRadius_, center_};
  }

  void Ellipse::move(const point_t &position)
  {
    center_ = position;
  }

  void Ellipse::move(double dx, double dy)
  {
    center_.x += dx;
    center_.y += dy;
  }

  void Ellipse::scale(double coefficient)
  {
    validatePositive(coefficient, "scale coefficient must be positive");
    horizontalRadius_ *= coefficient;
    verticalRadius_ *= coefficient;
  }

}
