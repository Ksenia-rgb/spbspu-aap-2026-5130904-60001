#include "bubble.hpp"
#include <stdexcept>
#include <cmath>

kotyurgina::Bubble::Bubble(const point_t& circleCenter, const point_t& pos, double radius):
  radius_(radius),
  circleCenter_(circleCenter),
  pos_(pos)
{
  const double dx = pos_.x - circleCenter_.x;
  const double dy = pos_.y - circleCenter_.y;
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
  return { 2 * radius_, 2 * radius_, circleCenter_ };
}

void kotyurgina::Bubble::move(const point_t& newPos)
{
  move(newPos.x - pos_.x, newPos.y - pos_.y);
}

void kotyurgina::Bubble::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
  circleCenter_.x += dx;
  circleCenter_.y += dy;
}

void kotyurgina::Bubble::scale(double factor)
{
  if (factor <= 0)
  {
    throw std::invalid_argument("Invalid scale factor");
  }

  circleCenter_.x = pos_.x + (circleCenter_.x - pos_.x) * factor;
  circleCenter_.y = pos_.y + (circleCenter_.y - pos_.y) * factor;
  radius_ *= factor;
}