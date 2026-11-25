#include "triangle.hpp"

#include <stdexcept>

namespace
{
  double minOf(double a, double b, double c)
  {
    const double ab = (a < b) ? a : b;
    return (ab < c) ? ab : c;
  }

  double maxOf(double a, double b, double c)
  {
    const double ab = (a > b) ? a : b;
    return (ab > c) ? ab : c;
  }

  double cross(const sumtsov::point_t &a, const sumtsov::point_t &b, const sumtsov::point_t &c)
  {
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
  }

  sumtsov::point_t scaleAround(const sumtsov::point_t &p, const sumtsov::point_t &center, double factor)
  {
    return {center.x + (p.x - center.x) * factor, center.y + (p.y - center.y) * factor};
  }
}

sumtsov::Triangle::Triangle(const point_t &a, const point_t &b, const point_t &c):
  a_(a),
  b_(b),
  c_(c)
{
  if (cross(a, b, c) == 0.0)
  {
    throw std::invalid_argument("triangle vertices must not be collinear");
  }
}

double sumtsov::Triangle::getArea() const
{
  const double value = cross(a_, b_, c_);
  return ((value < 0.0) ? -value : value) / 2.0;
}

sumtsov::rectangle_t sumtsov::Triangle::getFrameRect() const
{
  const double left = minOf(a_.x, b_.x, c_.x);
  const double right = maxOf(a_.x, b_.x, c_.x);
  const double bottom = minOf(a_.y, b_.y, c_.y);
  const double top = maxOf(a_.y, b_.y, c_.y);
  return {right - left, top - bottom, {(left + right) / 2.0, (bottom + top) / 2.0}};
}

void sumtsov::Triangle::move(const point_t &target)
{
  const point_t center = getCenter();
  move(target.x - center.x, target.y - center.y);
}

void sumtsov::Triangle::move(double dx, double dy)
{
  a_.x += dx;
  a_.y += dy;
  b_.x += dx;
  b_.y += dy;
  c_.x += dx;
  c_.y += dy;
}

void sumtsov::Triangle::scale(double factor)
{
  if (factor <= 0.0)
  {
    throw std::invalid_argument("scale factor must be positive");
  }
  const point_t center = getCenter();
  a_ = scaleAround(a_, center, factor);
  b_ = scaleAround(b_, center, factor);
  c_ = scaleAround(c_, center, factor);
}

sumtsov::point_t sumtsov::Triangle::getCenter() const
{
  return {(a_.x + b_.x + c_.x) / 3.0, (a_.y + b_.y + c_.y) / 3.0};
}
