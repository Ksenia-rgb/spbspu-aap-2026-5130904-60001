#include "ring.hpp"
#include <stdexcept>
#include <cmath>

kotyurgina::Ring::Ring(const point_t& pos, double outer_radius, double inner_radius):
  outer_radius_(outer_radius),
  inner_radius_(inner_radius),
  pos_(pos)
{
  if (inner_radius <= 0 || inner_radius >= outer_radius)
  {
    throw std::invalid_argument("Invalid ring dimensions");
  }
}

double kotyurgina::Ring::getArea() const
{
  const double pi = std::acos(-1.0);
  return pi * (outer_radius_ * outer_radius_ - inner_radius_ * inner_radius_);
}

kotyurgina::rectangle_t kotyurgina::Ring::getFrameRect() const
{
  return {2 * outer_radius_, 2 * outer_radius_, pos_};
}

void kotyurgina::Ring::move(const point_t& new_pos)
{
  pos_ = new_pos;
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
  outer_radius_ *= factor;
  inner_radius_ *= factor;
}
