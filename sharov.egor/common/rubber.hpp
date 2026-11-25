#ifndef RUBBER_HPP
#define RUBBER_HPP

#include <base-types.hpp>
#include <shape.hpp>

namespace sharov {
  class Rubber: public Shape {
  public:
    Rubber(double outerRadius, double innerRadius, const point_t &outerCenter, const point_t &innerCenter);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &position) override;
    void move(double dx, double dy) override;
    void scale(double coefficient) override;

  private:
    double outerRadius_;
    double innerRadius_;
    point_t outerCenter_;
    point_t innerCenter_;
  };
}

#endif
