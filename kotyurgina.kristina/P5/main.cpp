#include <iostream>
#include <algorithm>
#include <stdexcept>
#include "rectangle.hpp"
#include "ring.hpp"
#include "bubble.hpp"

namespace kotyurgina
{
  rectangle_t getTotalFrameRect(Shape* const* shapes, size_t count);
  void printShapes(Shape* const* shapes, size_t count);
  void scaleShapes(Shape* const* shapes, size_t count, const point_t& pos, double factor);
}

int main()
{
  try
  {
    kotyurgina::Rectangle rectangle({ 0.0, 0.0 }, 4.0, 6.0);
    kotyurgina::Ring ring({ 5.0, 5.0 }, 3.0, 1.0);
    kotyurgina::Bubble bubble({ 2.0, 2.0 }, { 3.0, 2.0 }, 2.0);

    kotyurgina::Shape* shapes[] = { &rectangle, &ring, &bubble };
    const size_t count = sizeof(shapes) / sizeof(shapes[0]);

    kotyurgina::point_t pos = { 0.0, 0.0 };
    double factor = 0.0;

    if (!(std::cin >> pos.x >> pos.y >> factor))
    {
      std::cerr << "Invalid input\n";
      return 1;
    }

    if (factor <= 0)
    {
      std::cerr << "Invalid scale factor\n";
      return 1;
    }
    std::cout << "Before scaling:\n";
    kotyurgina::printShapes(shapes, count);

    kotyurgina::scaleShapes(shapes, count, pos, factor);

    std::cout << "\nAfter scaling:\n";
    kotyurgina::printShapes(shapes, count);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 2;
  }

  return 0;
}

kotyurgina::rectangle_t kotyurgina::getTotalFrameRect(Shape* const* shapes, size_t count)
{
  if (count == 0)
  {
    throw std::invalid_argument("Empty array of shapes");
  }

  const rectangle_t first = shapes[0]->getFrameRect();

  double left = first.pos.x - first.width / 2;
  double right = first.pos.x + first.width / 2;
  double bottom = first.pos.y - first.height / 2;
  double top = first.pos.y + first.height / 2;

  for (size_t i = 1; i < count; i++)
  {
    const rectangle_t rect = shapes[i]->getFrameRect();

    left = std::min(left, rect.pos.x - rect.width / 2);
    right = std::max(right, rect.pos.x + rect.width / 2);
    bottom = std::min(bottom, rect.pos.y - rect.height / 2);
    top = std::max(top, rect.pos.y + rect.height / 2);
  }

  return { right - left, top - bottom,
    { (left + right) / 2, (bottom + top) / 2 } };
}

void kotyurgina::printShapes(Shape* const* shapes, size_t count)
{
  double totalArea = 0.0;
  const char* const names[] = { "Rectangle", "Ring", "Bubble" };

  for (size_t i = 0; i < count; i++)
  {
    const double area = shapes[i]->getArea();
    const rectangle_t rect = shapes[i]->getFrameRect();

    totalArea += area;

    std::cout << names[i] << '\n';
    std::cout << "Area: " << area << '\n';
    std::cout << "Frame rectangle: "
        << rect.width << ' ' << rect.height << ' '
        << rect.pos.x << ' ' << rect.pos.y << '\n';
  }

  const rectangle_t totalRect = getTotalFrameRect(shapes, count);

  std::cout << "Total area: " << totalArea << '\n';
  std::cout << "Total frame rectangle: "
      << totalRect.width << ' ' << totalRect.height << ' '
      << totalRect.pos.x << ' ' << totalRect.pos.y << '\n';
}

void kotyurgina::scaleShapes(Shape* const* shapes, size_t count, const point_t& pos, double factor)
{
  if (factor <= 0)
  {
    throw std::invalid_argument("Invalid scale factor");
  }

  for (size_t i = 0; i < count; i++)
  {
    const point_t before = shapes[i]->getFrameRect().pos;

    shapes[i]->scale(factor);

    const point_t after = shapes[i]->getFrameRect().pos;

    const double newX = pos.x + (before.x - pos.x) * factor;
    const double newY = pos.y + (before.y - pos.y) * factor;

    shapes[i]->move(newX - after.x, newY - after.y);
  }
}
