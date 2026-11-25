#include <rectangle.hpp>

#include <shape-utils.hpp>

namespace sharov {
  Rectangle::Rectangle(double width, double height, const point_t &center):
    width_(width),
    height_(height),
    center_(center)
  {
    validatePositive(width_, "rectangle width must be positive");
    validatePositive(height_, "rectangle height must be positive");
  }

  double Rectangle::getArea() const
  {
    return width_ * height_;
  }

  rectangle_t Rectangle::getFrameRect() const
  {
    return rectangle_t{width_, height_, center_};
  }

  void Rectangle::move(const point_t &position)
  {
    center_ = position;
  }

  void Rectangle::move(double dx, double dy)
  {
    center_.x += dx;
    center_.y += dy;
  }

  void Rectangle::scale(double coefficient)
  {
    validatePositive(coefficient, "scale coefficient must be positive");
    width_ *= coefficient;
    height_ *= coefficient;
  }

}
