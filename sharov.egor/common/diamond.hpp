#ifndef DIAMOND_HPP
#define DIAMOND_HPP

#include <base-types.hpp>
#include <shape.hpp>

namespace sharov {
  class Diamond: public Shape {
  public:
    Diamond(double horizontalDiagonal, double verticalDiagonal, const point_t &center);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &position) override;
    void move(double dx, double dy) override;
    void scale(double coefficient) override;

  private:
    double horizontalDiagonal_;
    double verticalDiagonal_;
    point_t center_;
  };
}

#endif
