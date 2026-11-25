#include "rectangle.hpp"

#include <stdexcept>

sumtsov::Rectangle::Rectangle(const point_t &pos, double width, double height):
  pos_(pos),
  width_(width),
  height_(height)
{
  if ((width <= 0.0) || (height <= 0.0))
  {
    throw std::invalid_argument("rectangle sides must be positive");
  }
}

double sumtsov::Rectangle::getArea() const
{
  return width_ * height_;
}

sumtsov::rectangle_t sumtsov::Rectangle::getFrameRect() const
{
  return {width_, height_, pos_};
}

void sumtsov::Rectangle::move(const point_t &target)
{
  pos_ = target;
}

void sumtsov::Rectangle::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void sumtsov::Rectangle::scale(double factor)
{
  if (factor <= 0.0)
  {
    throw std::invalid_argument("scale factor must be positive");
  }
  width_ *= factor;
  height_ *= factor;
}
