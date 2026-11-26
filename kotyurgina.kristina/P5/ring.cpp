#include "ring.hpp"
#include <stdexcept>
#include <cmath>

kotyurgina::Ring::Ring(const point_t& pos, double outerRadius, double innerRadius):
  outerRadius_(outerRadius),
  innerRadius_(innerRadius),
  pos_(pos)
{
  if (innerRadius <= 0 || innerRadius >= outerRadius)
  {
    throw std::invalid_argument("Invalid ring dimensions");
  }
}

double kotyurgina::Ring::getArea() const
{
  const double pi = std::acos(-1.0);
  return pi * (outerRadius_ * outerRadius_ - innerRadius_ * innerRadius_);
}

kotyurgina::rectangle_t kotyurgina::Ring::getFrameRect() const
{
  return { 2 * outerRadius_, 2 * outerRadius_, pos_ };
}

void kotyurgina::Ring::move(const point_t& newPos)
{
  pos_ = newPos;
}

void kotyurgina::Ring::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void kotyurgina::Ring::scale(double factor)
{
  if (factor <= 0)
  {
    throw std::invalid_argument("Invalid scale factor");
  }
  outerRadius_ *= factor;
  innerRadius_ *= factor;
}