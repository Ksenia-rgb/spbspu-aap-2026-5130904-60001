#include <algorithm>
#include <cmath>
#include <stdexcept>
#include "base-types.hpp"
#include "shape.hpp"

namespace
{
  double getTriArea(const erin::point_t & a, const erin::point_t & b, const erin::point_t & c)
  {
    return 0.5 * std::fabs((b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y));
  }

  erin::point_t getCenter(const erin::point_t & a, const erin::point_t & b, const erin::point_t & c)
  {
    return { (a.x + b.x + c.x) / 3.0, (a.y + b.y + c.y) / 3.0 };
  }

  void scalePt(erin::point_t & p, const erin::point_t & mid, double k)
  {
    p.x = mid.x + (p.x - mid.x) * k;
    p.y = mid.y + (p.y - mid.y) * k;
  }
}

namespace erin
{
  class Rectangle: public Shape
  {
  public:
    Rectangle(const point_t & pos, double w, double h):
      pos_(pos),
      w_(w),
      h_(h)
    {
      if (w_ <= 0.0 || h_ <= 0.0)
      {
        throw std::invalid_argument("Invalid rectangle size");
      }
    }

    double getArea() const override
    {
      return w_ * h_;
    }

    rectangle_t getFrameRect() const override
    {
      return { w_, h_, pos_ };
    }

    void move(const point_t & pos) override
    {
      pos_ = pos;
    }

    void move(double dx, double dy) override
    {
      pos_.x += dx;
      pos_.y += dy;
    }

    void scale(double k) override
    {
      if (k <= 0.0)
      {
        throw std::invalid_argument("Invalid scale factor");
      }
      w_ *= k;
      h_ *= k;
    }

  private:
    point_t pos_;
    double w_;
    double h_;
  };

  class Square: public Shape
  {
  public:
    Square(const point_t & pos, double side):
      pos_(pos),
      side_(side)
    {
      if (side_ <= 0.0)
      {
        throw std::invalid_argument("Invalid square side");
      }
    }

    double getArea() const override
    {
      return side_ * side_;
    }

    rectangle_t getFrameRect() const override
    {
      return { side_, side_, pos_ };
    }

    void move(const point_t & pos) override
    {
      pos_ = pos;
    }

    void move(double dx, double dy) override
    {
      pos_.x += dx;
      pos_.y += dy;
    }

    void scale(double k) override
    {
      if (k <= 0.0)
      {
        throw std::invalid_argument("Invalid scale factor");
      }
      side_ *= k;
    }

  private:
    point_t pos_;
    double side_;
  };

  class Triangle: public Shape
  {
  public:
    Triangle(const point_t & a, const point_t & b, const point_t & c):
      a_(a),
      b_(b),
      c_(c)
    {
      if (getTriArea(a_, b_, c_) <= 0.0)
      {
        throw std::invalid_argument("Invalid triangle vertices");
      }
    }

    double getArea() const override
    {
      return getTriArea(a_, b_, c_);
    }

    rectangle_t getFrameRect() const override
    {
      const double min_x = std::min(a_.x, std::min(b_.x, c_.x));
      const double max_x = std::max(a_.x, std::max(b_.x, c_.x));
      const double min_y = std::min(a_.y, std::min(b_.y, c_.y));
      const double max_y = std::max(a_.y, std::max(b_.y, c_.y));
      return { max_x - min_x, max_y - min_y, { (min_x + max_x) / 2.0, (min_y + max_y) / 2.0 } };
    }

    void move(const point_t & pos) override
    {
      const point_t mid = getCenter(a_, b_, c_);
      move(pos.x - mid.x, pos.y - mid.y);
    }

    void move(double dx, double dy) override
    {
      a_.x += dx;
      a_.y += dy;
      b_.x += dx;
      b_.y += dy;
      c_.x += dx;
      c_.y += dy;
    }

    void scale(double k) override
    {
      if (k <= 0.0)
      {
        throw std::invalid_argument("Invalid scale factor");
      }
      const point_t mid = getCenter(a_, b_, c_);
      scalePt(a_, mid, k);
      scalePt(b_, mid, k);
      scalePt(c_, mid, k);
    }

  private:
    point_t a_;
    point_t b_;
    point_t c_;
  };
}

int main()
{
  return 0;
}
