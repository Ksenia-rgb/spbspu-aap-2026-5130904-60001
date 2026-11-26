#include "rectangle.hpp"
#include <stdexcept>
namespace grebenshchikov
{
  Rectangle::Rectangle(point_t pos, double width, double height): 
    rect_{width, height, pos}
  {}

  double Rectangle::getArea() const
  {
    return rect_.width * rect_.height;
  }

  rectangle_t Rectangle::getFrameRect() const
  {
    return rect_;
  }

  void Rectangle::move(point_t newPos)
  {
    rect_.pos = newPos;
  }

  void Rectangle::move(double dx, double dy)
  {
    rect_.pos.x += dx;
    rect_.pos.y += dy;
  }

  void Rectangle::scale(double factor)
  {
    if (factor <= 0)
    {
      throw std::logic_error("Scale factor must be positive");
    }
    rect_.height *= factor;
    rect_.width *= factor;
  }
}