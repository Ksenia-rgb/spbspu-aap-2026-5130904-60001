#include <ring.hpp>

#include <shape-utils.hpp>

namespace sharov {
  Ring::Ring(double outerRadius, double innerRadius, const point_t &center):
    outerRadius_(outerRadius),
    innerRadius_(innerRadius),
    center_(center)
  {
    validatePositive(outerRadius_, "ring outer radius must be positive");
    validatePositive(innerRadius_, "ring inner radius must be positive");
    if (!(outerRadius_ > innerRadius_)) {
      throw std::invalid_argument("ring outer radius must be greater than the inner radius");
    }
  }

  double Ring::getArea() const
  {
    return PI * (outerRadius_ * outerRadius_ - innerRadius_ * innerRadius_);
  }

  rectangle_t Ring::getFrameRect() const
  {
    return rectangle_t{DIAMETER_FACTOR * outerRadius_, DIAMETER_FACTOR * outerRadius_, center_};
  }

  void Ring::move(const point_t &position)
  {
    center_ = position;
  }

  void Ring::move(double dx, double dy)
  {
    center_.x += dx;
    center_.y += dy;
  }

  void Ring::scale(double coefficient)
  {
    validatePositive(coefficient, "scale coefficient must be positive");
    outerRadius_ *= coefficient;
    innerRadius_ *= coefficient;
  }

}
