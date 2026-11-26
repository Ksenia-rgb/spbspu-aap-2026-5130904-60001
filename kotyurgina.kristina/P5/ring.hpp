#ifndef RING_HPP
#define RING_HPP

#include "shape.hpp"

namespace kotyurgina
{
  class Ring: public Shape
  {
  public:
    Ring(const point_t& pos, double outer_radius, double inner_radius);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& new_pos) override;
    void move(double dx, double dy) override;
    void scale(double factor) override;

  private:
    double outer_radius_;
    double inner_radius_;
    point_t pos_;
  };
}

#endif
