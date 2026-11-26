#include "bubble.hpp"
#include <stdexcept>
#include <cmath>

kotyurgina::Bubble::Bubble(const point_t& circle_center, const point_t& pos, double radius):
  radius_(radius),
  circle_center_(circle_center),
  pos_(pos)
{
  const double dx = pos_.x - circle_center_.x;
  const double dy = pos_.y - circle_center_.y;
  const double distance = std::hypot(dx, dy);

  if (radius_ <= 0 || distance == 0 || distance >= radius_)
  {
    throw std::invalid_argument("Invalid bubble dimensions");
  }
}

double kotyurgina::Bubble::getArea() const
{
  const double pi = std::acos(-1.0);
  return pi * radius_ * radius_;
}

kotyurgina::rectangle_t kotyurgina::Bubble::getFrameRect() const
{
  return {2 * radius_, 2 * radius_, circle_center_};
}

void kotyurgina::Bubble::move(const point_t& new_pos)
{
  move(new_pos.x - pos_.x, new_pos.y - pos_.y);
}

void kotyurgina::Bubble::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
  circle_center_.x += dx;
  circle_center_.y += dy;
}

void kotyurgina::Bubble::scale(double factor)
{
  if (factor <= 0)
  {
    throw std::invalid_argument("Invalid scale factor");
  }

  circle_center_.x = pos_.x + (circle_center_.x - pos_.x) * factor;
  circle_center_.y = pos_.y + (circle_center_.y - pos_.y) * factor;
  radius_ *= factor;
}
