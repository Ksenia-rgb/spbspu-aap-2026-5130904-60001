#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace grebenshchikov
{
  class Rectangle: public Shape
  {
  public:
    Rectangle(point_t pos, double width, double height);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t newPos) override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
  private:
    rectangle_t rect_;
  };
}

#endif
