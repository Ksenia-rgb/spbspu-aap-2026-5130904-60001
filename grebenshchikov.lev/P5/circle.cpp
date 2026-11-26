#include "circle.hpp"
#include <stdexcept>

namespace grebenshchikov
{
  constexpr double pi = 3.141592653589793;
}

grebenshchikov::Circle::Circle(point_t pos, double radius):
  center_(pos),
  radius_(radius)
{
  if (!(radius > 0.0))
  {
    throw std::logic_error("radius must be positive\n");
  }
}

double grebenshchikov::Circle::getArea() const
{
  return pi * radius_ * radius_;
}

grebenshchikov::rectangle_t grebenshchikov::Circle::getFrameRect() const
{
  const double maxY = center_.y + radius_;
  const double minY = center_.y - radius_;
  const double maxX = center_.x + radius_;
  const double minX = center_.x - radius_;
  const double width = maxX - minX;
  const double height = maxY - minY;
  return {width, height, center_};
}

void grebenshchikov::Circle::move(point_t newPos)
{
  center_ = newPos;
}

void grebenshchikov::Circle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void grebenshchikov::Circle::scale(double factor)
{
  if (!(factor > 0.0))
  {
    throw std::logic_error("Scale factor must be positive\n");
  }
  radius_ *= factor;
}
