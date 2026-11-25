#include <triangle.hpp>

#include <algorithm>
#include <cmath>
#include <stdexcept>

#include <shape-utils.hpp>

namespace sharov {
  namespace {
    double getDoubleArea(const point_t &first, const point_t &second, const point_t &third)
    {
      const double firstX = second.x - first.x;
      const double firstY = second.y - first.y;
      const double secondX = third.x - first.x;
      const double secondY = third.y - first.y;
      return firstX * secondY - firstY * secondX;
    }

    point_t getScaledPoint(const point_t &point, const point_t &center, double coefficient)
    {
      return point_t{center.x + (point.x - center.x) * coefficient, center.y + (point.y - center.y) * coefficient};
    }
  }

  Triangle::Triangle(const point_t &first, const point_t &second, const point_t &third):
    first_(first),
    second_(second),
    third_(third)
  {
    if (getDoubleArea(first_, second_, third_) == 0.0) {
      throw std::invalid_argument("triangle vertices must not lie on a single line");
    }
  }

  double Triangle::getArea() const
  {
    return std::fabs(getDoubleArea(first_, second_, third_)) * HALF;
  }

  rectangle_t Triangle::getFrameRect() const
  {
    const double minimumX = std::min(std::min(first_.x, second_.x), third_.x);
    const double maximumX = std::max(std::max(first_.x, second_.x), third_.x);
    const double minimumY = std::min(std::min(first_.y, second_.y), third_.y);
    const double maximumY = std::max(std::max(first_.y, second_.y), third_.y);
    const point_t center{(minimumX + maximumX) * HALF, (minimumY + maximumY) * HALF};
    return rectangle_t{maximumX - minimumX, maximumY - minimumY, center};
  }

  point_t Triangle::getCentroid() const
  {
    return point_t{(first_.x + second_.x + third_.x) / TRIANGLE_VERTEX_COUNT,
        (first_.y + second_.y + third_.y) / TRIANGLE_VERTEX_COUNT};
  }

  void Triangle::move(const point_t &position)
  {
    const point_t centroid = getCentroid();
    move(position.x - centroid.x, position.y - centroid.y);
  }

  void Triangle::move(double dx, double dy)
  {
    first_.x += dx;
    first_.y += dy;
    second_.x += dx;
    second_.y += dy;
    third_.x += dx;
    third_.y += dy;
  }

  void Triangle::scale(double coefficient)
  {
    validatePositive(coefficient, "scale coefficient must be positive");
    const point_t centroid = getCentroid();
    first_ = getScaledPoint(first_, centroid, coefficient);
    second_ = getScaledPoint(second_, centroid, coefficient);
    third_ = getScaledPoint(third_, centroid, coefficient);
  }

}
