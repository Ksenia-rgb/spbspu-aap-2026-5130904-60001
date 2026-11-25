#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <base-types.hpp>
#include <shape.hpp>

namespace sharov {
  class Triangle: public Shape {
  public:
    Triangle(const point_t &first, const point_t &second, const point_t &third);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &position) override;
    void move(double dx, double dy) override;
    void scale(double coefficient) override;

  private:
    point_t getCentroid() const;

    point_t first_;
    point_t second_;
    point_t third_;
  };
}

#endif
