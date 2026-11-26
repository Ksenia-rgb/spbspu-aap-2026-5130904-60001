#ifndef BUBBLE_HPP
#define BUBBLE_HPP

#include "shape.hpp"

namespace kotyurgina
{
  class Bubble: public Shape
  {
  public:
    Bubble(const point_t& circle_center, const point_t& pos, double radius);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& new_pos) override;
    void move(double dx, double dy) override;
    void scale(double factor) override;

  private:
    double radius_;
    point_t circle_center_;
    point_t pos_;
  };
}

#endif
