#ifndef ELLIPSE_HPP
#define ELLIPSE_HPP

#include <base-types.hpp>
#include <shape.hpp>

namespace sharov {
  class Ellipse: public Shape {
  public:
    Ellipse(double horizontalRadius, double verticalRadius, const point_t &center);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &position) override;
    void move(double dx, double dy) override;
    void scale(double coefficient) override;

  private:
    double horizontalRadius_;
    double verticalRadius_;
    point_t center_;
  };
}

#endif
