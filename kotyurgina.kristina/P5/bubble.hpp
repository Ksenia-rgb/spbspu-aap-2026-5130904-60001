#ifndef KOTYURGINA_BUBBLE_HPP
#define KOTYURGINA_BUBBLE_HPP

#include "shape.hpp"

namespace kotyurgina
{
  class Bubble: public Shape
  {
  public:
    Bubble(const point_t& circleCenter, const point_t& pos, double radius);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& newPos) override;
    void move(double dx, double dy) override;
    void scale(double factor) override;

  private:
    double radius_;
    point_t circleCenter_;
    point_t pos_;
  };
}

#endif