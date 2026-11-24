#include <algorithm>
#include <cmath>
#include <cstddef>
#include <exception>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include "base-types.hpp"
#include "shape.hpp"

namespace
{
  constexpr double half = 0.5;
  constexpr double tri_verts = 3.0;

  double getTriArea(const erin::point_t &a, const erin::point_t &b, const erin::point_t &c)
  {
    return half * std::fabs((b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y));
  }

  erin::point_t getCenter(const erin::point_t &a, const erin::point_t &b, const erin::point_t &c)
  {
    return {(a.x + b.x + c.x) / tri_verts, (a.y + b.y + c.y) / tri_verts};
  }

  void scalePt(erin::point_t &p, const erin::point_t &mid, double k)
  {
    p.x = mid.x + (p.x - mid.x) * k;
    p.y = mid.y + (p.y - mid.y) * k;
  }

  void scaleAll(erin::Shape *const *arr, size_t cnt, const erin::point_t &pt, double k)
  {
    if (k <= 0.0)
    {
      throw std::invalid_argument("Invalid scale factor");
    }
    for (size_t i = 0; i < cnt; ++i)
    {
      const erin::point_t p1 = arr[i]->getFrameRect().pos;
      arr[i]->move(pt);
      const erin::point_t p2 = arr[i]->getFrameRect().pos;
      const double dx = p2.x - p1.x;
      const double dy = p2.y - p1.y;
      arr[i]->scale(k);
      arr[i]->move(-dx * k, -dy * k);
    }
  }

  erin::rectangle_t getFrame(const erin::Shape *const *arr, size_t cnt)
  {
    if (cnt == 0)
    {
      return {0.0, 0.0, {0.0, 0.0}};
    }
    const erin::rectangle_t r0 = arr[0]->getFrameRect();
    double min_x = r0.pos.x - r0.width * half;
    double max_x = r0.pos.x + r0.width * half;
    double min_y = r0.pos.y - r0.height * half;
    double max_y = r0.pos.y + r0.height * half;

    for (size_t i = 1; i < cnt; ++i)
    {
      const erin::rectangle_t r = arr[i]->getFrameRect();
      min_x = std::min(min_x, r.pos.x - r.width * half);
      max_x = std::max(max_x, r.pos.x + r.width * half);
      min_y = std::min(min_y, r.pos.y - r.height * half);
      max_y = std::max(max_y, r.pos.y + r.height * half);
    }

    return {max_x - min_x, max_y - min_y, {(min_x + max_x) * half, (min_y + max_y) * half}};
  }

  void printRect(std::ostream &out, const erin::rectangle_t &r)
  {
    out << "w=" << r.width << " h=" << r.height;
    out << " pos=(" << r.pos.x << ", " << r.pos.y << ")";
  }

  void printAll(std::ostream &out, const erin::Shape *const *arr, size_t cnt)
  {
    double sum = 0.0;
    for (size_t i = 0; i < cnt; ++i)
    {
      const double area = arr[i]->getArea();
      const erin::rectangle_t r = arr[i]->getFrameRect();
      sum += area;
      out << "Shape " << (i + 1) << ": area=" << area << ", frame: ";
      printRect(out, r);
      out << "\n";
    }
    out << "Total area: " << sum << "\n";
    out << "Total frame: ";
    printRect(out, getFrame(arr, cnt));
    out << "\n";
  }

  void freeAll(erin::Shape **arr, size_t cnt)
  {
    if (!arr)
    {
      return;
    }
    for (size_t i = 0; i < cnt; ++i)
    {
      delete arr[i];
    }
    delete[] arr;
  }
}

namespace erin
{
  class Rectangle: public Shape
  {
  public:
    Rectangle(const point_t &pos, double w, double h):
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
      return {w_, h_, pos_};
    }

    void move(const point_t &pos) override
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
    Square(const point_t &pos, double side):
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
      return {side_, side_, pos_};
    }

    void move(const point_t &pos) override
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
    Triangle(const point_t &a, const point_t &b, const point_t &c):
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
      return {max_x - min_x, max_y - min_y, {(min_x + max_x) * half, (min_y + max_y) * half}};
    }

    void move(const point_t &pos) override
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
  constexpr size_t cnt = 3;
  constexpr double r_x = 1.0;
  constexpr double r_y = 2.0;
  constexpr double r_w = 4.0;
  constexpr double r_h = 6.0;
  constexpr double s_x = -3.0;
  constexpr double s_y = 1.0;
  constexpr double s_side = 5.0;
  constexpr double t_x = 4.0;
  constexpr double t_y = 3.0;
  erin::Shape **arr = nullptr;

  try
  {
    arr = new erin::Shape *[cnt]();
    arr[0] = new erin::Rectangle({r_x, r_y}, r_w, r_h);
    arr[1] = new erin::Square({s_x, s_y}, s_side);
    arr[2] = new erin::Triangle({0.0, 0.0}, {t_x, 0.0}, {0.0, t_y});

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Before:\n";
    printAll(std::cout, arr, cnt);

    erin::point_t pt = {0.0, 0.0};
    double k = 0.0;
    if (!(std::cin >> pt.x >> pt.y >> k))
    {
      freeAll(arr, cnt);
      std::cerr << "Invalid input\n";
      return 1;
    }

    scaleAll(arr, cnt, pt, k);

    std::cout << "After:\n";
    printAll(std::cout, arr, cnt);
  }
  catch (const std::exception &e)
  {
    freeAll(arr, cnt);
    std::cerr << e.what() << "\n";
    return 1;
  }

  freeAll(arr, cnt);
  return 0;
}
