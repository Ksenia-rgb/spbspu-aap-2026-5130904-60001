#include "rectangle.hpp"
#include <stdexcept>

kotyurgina::Rectangle::Rectangle(const point_t& pos, double width, double height):
  rect_{width, height, pos}
{
  if (width <= 0 || height <= 0)
  {
    throw std::invalid_argument("Invalid rectangle dimensions");
  }
}

double kotyurgina::Rectangle::getArea() const
{
  return rect_.width * rect_.height;
}

kotyurgina::rectangle_t kotyurgina::Rectangle::getFrameRect() const
{
  return rect_;
}

void kotyurgina::Rectangle::move(const point_t& new_pos)
{
  rect_.pos = new_pos;
}

void kotyurgina::Rectangle::move(double dx, double dy)
{
  rect_.pos.x += dx;
  rect_.pos.y += dy;
}

void kotyurgina::Rectangle::scale(double factor)
{
  if (factor <= 0)
  {
    throw std::invalid_argument("Invalid scale factor");
  }
  rect_.width *= factor;
  rect_.height *= factor;
}
