#include <rubber.hpp>

#include <cmath>
#include <stdexcept>

#include <shape-utils.hpp>

namespace sharov {
  namespace {
    double getDistance(const point_t &first, const point_t &second)
    {
      const double dx = first.x - second.x;
      const double dy = first.y - second.y;
      return std::sqrt(dx * dx + dy * dy);
    }
  }

  Rubber::Rubber(double outerRadius, double innerRadius, const point_t &outerCenter, const point_t &innerCenter):
    outerRadius_(outerRadius),
    innerRadius_(innerRadius),
    outerCenter_(outerCenter),
    innerCenter_(innerCenter)
  {
    validatePositive(outerRadius_, "rubber outer radius must be positive");
    validatePositive(innerRadius_, "rubber inner radius must be positive");
    if (!(outerRadius_ > innerRadius_)) {
      throw std::invalid_argument("rubber outer radius must be greater than the inner radius");
    }
    const double distance = getDistance(outerCenter_, innerCenter_);
    if (!(distance > 0.0)) {
      throw std::invalid_argument("rubber circles must not be coaxial");
    }
    if (!(distance + innerRadius_ <= outerRadius_)) {
      throw std::invalid_argument("rubber inner circle must lie inside the outer one");
    }
  }

  double Rubber::getArea() const
  {
    return PI * (outerRadius_ * outerRadius_ - innerRadius_ * innerRadius_);
  }

  rectangle_t Rubber::getFrameRect() const
  {
    return rectangle_t{DIAMETER_FACTOR * outerRadius_, DIAMETER_FACTOR * outerRadius_, outerCenter_};
  }

  void Rubber::move(const point_t &position)
  {
    move(position.x - innerCenter_.x, position.y - innerCenter_.y);
  }

  void Rubber::move(double dx, double dy)
  {
    outerCenter_.x += dx;
    outerCenter_.y += dy;
    innerCenter_.x += dx;
    innerCenter_.y += dy;
  }

  void Rubber::scale(double coefficient)
  {
    validatePositive(coefficient, "scale coefficient must be positive");
    outerRadius_ *= coefficient;
    innerRadius_ *= coefficient;
    outerCenter_.x = innerCenter_.x + (outerCenter_.x - innerCenter_.x) * coefficient;
    outerCenter_.y = innerCenter_.y + (outerCenter_.y - innerCenter_.y) * coefficient;
  }

}
