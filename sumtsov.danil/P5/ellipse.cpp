#include "ellipse.hpp"

#include <stdexcept>

namespace
{
  constexpr double pi = 3.14159265358979323846;
  constexpr double two = 2.0;
}

sumtsov::Ellipse::Ellipse(const point_t &pos, double radius_x, double radius_y):
  pos_(pos),
  radius_x_(radius_x),
  radius_y_(radius_y)
{
  if ((radius_x <= 0.0) || (radius_y <= 0.0))
  {
    throw std::invalid_argument("ellipse radii must be positive");
  }
}

double sumtsov::Ellipse::getArea() const
{
  return pi * radius_x_ * radius_y_;
}

sumtsov::rectangle_t sumtsov::Ellipse::getFrameRect() const
{
  return {two * radius_x_, two * radius_y_, pos_};
}

void sumtsov::Ellipse::move(const point_t &target)
{
  pos_ = target;
}

void sumtsov::Ellipse::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void sumtsov::Ellipse::scale(double factor)
{
  if (factor <= 0.0)
  {
    throw std::invalid_argument("scale factor must be positive");
  }
  radius_x_ *= factor;
  radius_y_ *= factor;
}
