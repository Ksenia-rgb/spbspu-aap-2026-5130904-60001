#include "circle.hpp"
#include <stdexcept>

namespace grebenshchikov
{
  constexpr double pi = 3.141592653589793;

  Circle::Circle(point_t pos, double radius): 
    center_(pos),
    radius_(radius)
  {
    if (radius <= 0.0)
    {
      throw std::logic_error("radius must be positive\n");
    }
  }

  double Circle::getArea() const
  {
    return pi * radius_ * radius_;
  }

  rectangle_t Circle::getFrameRect() const
  {
    double maxY, minY, maxX, minX;
    maxY = center_.y + radius_;
    minY = center_.y - radius_;
    maxX = center_.x + radius_;
    minX = center_.x - radius_;
    double width, height;
    width = maxX - minX;
    height = maxY - minY;
    rectangle_t res;
    res.width = width;
    res.height = height;
    res.pos = center_;
    return res;
  }

  void Circle::move(point_t newPos)
  {
    center_ = newPos;
  }

  void Circle::move(double dx, double dy)
  {
    center_.x += dx;
    center_.y += dy;
  }

  void Circle::scale(double factor)
  {
    if (factor <= 0)
    {
      throw std::logic_error("Scale factor must be positive\n");
    }
    radius_ *= factor;
  }
}