#ifndef RING_HPP
#define RING_HPP

#include <base-types.hpp>
#include <shape.hpp>

namespace sharov {
  class Ring: public Shape {
  public:
    Ring(double outerRadius, double innerRadius, const point_t &center);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &position) override;
    void move(double dx, double dy) override;
    void scale(double coefficient) override;

  private:
    double outerRadius_;
    double innerRadius_;
    point_t center_;
  };
}

#endif
