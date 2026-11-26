#ifndef KOTYURGINA_RING_HPP
#define KOTYURGINA_RING_HPP

#include "shape.hpp"

namespace kotyurgina
{
  class Ring: public Shape
  {
  public:
    Ring(const point_t& pos, double outerRadius, double innerRadius);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& newPos) override;
    void move(double dx, double dy) override;
    void scale(double factor) override;

  private:
    double outerRadius_;
    double innerRadius_;
    point_t pos_;
};
}

#endif