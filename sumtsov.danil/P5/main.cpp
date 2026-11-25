#include <cstddef>
#include <exception>
#include <iostream>

#include "ellipse.hpp"
#include "rectangle.hpp"
#include "shape.hpp"
#include "triangle.hpp"

namespace
{
  void scaleAbout(sumtsov::Shape *shape, const sumtsov::point_t &target, double factor)
  {
    const sumtsov::point_t before = shape->getFrameRect().pos;
    shape->move(target);
    const sumtsov::point_t moved = shape->getFrameRect().pos;
    shape->scale(factor);
    shape->move(factor * (before.x - moved.x), factor * (before.y - moved.y));
  }

  void scaleAll(sumtsov::Shape **shapes, size_t count, const sumtsov::point_t &target, double factor)
  {
    for (size_t i = 0; i < count; ++i)
    {
      scaleAbout(shapes[i], target, factor);
    }
  }

  void printFrame(std::ostream &out, const sumtsov::rectangle_t &frame)
  {
    out << "center (" << frame.pos.x << ", " << frame.pos.y << ") ";
    out << "width " << frame.width << " height " << frame.height << '\n';
  }

  void printInfo(std::ostream &out, sumtsov::Shape *const *shapes, size_t count)
  {
    double total = 0.0;
    const sumtsov::rectangle_t first = shapes[0]->getFrameRect();
    double left = first.pos.x - first.width / 2.0;
    double right = first.pos.x + first.width / 2.0;
    double bottom = first.pos.y - first.height / 2.0;
    double top = first.pos.y + first.height / 2.0;

    for (size_t i = 0; i < count; ++i)
    {
      const double area = shapes[i]->getArea();
      const sumtsov::rectangle_t frame = shapes[i]->getFrameRect();
      out << "shape " << i << " area " << area << '\n';
      out << "shape " << i << " frame ";
      printFrame(out, frame);
      total += area;

      const double f_left = frame.pos.x - frame.width / 2.0;
      const double f_right = frame.pos.x + frame.width / 2.0;
      const double f_bottom = frame.pos.y - frame.height / 2.0;
      const double f_top = frame.pos.y + frame.height / 2.0;
      left = (f_left < left) ? f_left : left;
      right = (f_right > right) ? f_right : right;
      bottom = (f_bottom < bottom) ? f_bottom : bottom;
      top = (f_top > top) ? f_top : top;
    }

    out << "total area " << total << '\n';
    out << "total frame ";
    printFrame(out, {right - left, top - bottom, {(left + right) / 2.0, (bottom + top) / 2.0}});
  }

  void destroyAll(sumtsov::Shape **shapes, size_t count)
  {
    for (size_t i = 0; i < count; ++i)
    {
      delete shapes[i];
    }
  }
}

int main()
{
  constexpr size_t count = 3;
  sumtsov::Shape *shapes[count] = {nullptr, nullptr, nullptr};

  try
  {
    shapes[0] = new sumtsov::Rectangle({1.0, 1.0}, 4.0, 2.0);
    shapes[1] = new sumtsov::Triangle({0.0, 0.0}, {4.0, 0.0}, {0.0, 3.0});
    shapes[2] = new sumtsov::Ellipse({-2.0, 3.0}, 3.0, 2.0);
  }
  catch (const std::exception &error)
  {
    std::cerr << "Error: " << error.what() << '\n';
    destroyAll(shapes, count);
    return 2;
  }

  sumtsov::point_t target = {0.0, 0.0};
  double factor = 0.0;
  if (!(std::cin >> target.x >> target.y >> factor) || (factor <= 0.0))
  {
    std::cerr << "Error: invalid scale parameters\n";
    destroyAll(shapes, count);
    return 1;
  }

  std::cout << "before scaling:\n";
  printInfo(std::cout, shapes, count);

  try
  {
    scaleAll(shapes, count, target, factor);
  }
  catch (const std::exception &error)
  {
    std::cerr << "Error: " << error.what() << '\n';
    destroyAll(shapes, count);
    return 1;
  }

  std::cout << "after scaling:\n";
  printInfo(std::cout, shapes, count);

  destroyAll(shapes, count);
  return 0;
}
