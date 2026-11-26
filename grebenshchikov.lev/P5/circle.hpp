#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace grebenshchikov
{
  class Circle: public Shape
  {
  public:
    Circle(point_t pos, double radius);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t newPos) override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
  private:
    point_t center_;
    double radius_;
  };
}

#endif
