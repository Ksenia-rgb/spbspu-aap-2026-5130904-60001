#include <iostream>
#include <cstddef>
#include <cstdlib>
#include "rectangle.hpp"
#include "circle.hpp"

using std::size_t;

namespace grebenshchikov
{
  void printShapes(const Shape* const shapes[], size_t count);
  void scaleShapes(Shape* const shapes[], size_t count, point_t pos, double factor);
}

void grebenshchikov::printShapes(const Shape* const shapes[], size_t count)
{
  double totalArea = 0.0;

  const rectangle_t frame = shapes[0]->getFrameRect();
  double left = frame.pos.x - frame.width / 2.0;
  double right = frame.pos.x + frame.width / 2.0;
  double bottom = frame.pos.y - frame.height / 2.0;
  double top = frame.pos.y + frame.height / 2.0;

  for (size_t i = 0; i < count; i++)
  {
    const double area = shapes[i]->getArea();
    const rectangle_t frameRect = shapes[i]->getFrameRect();

    const double currentLeft = frameRect.pos.x - frameRect.width / 2.0;
    const double currentRight = frameRect.pos.x + frameRect.width / 2.0;
    const double currentBottom = frameRect.pos.y - frameRect.height / 2.0;
    const double currentTop = frameRect.pos.y + frameRect.height / 2.0;

    if (currentLeft < left)
    {
      left = currentLeft;
    }
    if (currentRight > right)
    {
      right = currentRight;
    }
    if (currentTop > top)
    {
      top = currentTop;
    }
    if (currentBottom < bottom)
    {
      bottom = currentBottom;
    }

    std::cout << area << ' ' << frameRect.height << ' ' << frameRect.width << ' ' << frameRect.pos.x << ' '
              << frameRect.pos.y << '\n';
    totalArea += area;
  }

  const point_t totalCenter{(left + right) / 2.0, (bottom + top) / 2.0};
  const double totalWidth = right - left;
  const double totalHeight = top - bottom;

  std::cout << totalArea << '\n';
  std::cout << totalHeight << ' ' << totalWidth << ' ' << totalCenter.x << ' ' << totalCenter.y << '\n';
}

void grebenshchikov::scaleShapes(Shape* const shapes[], size_t count, point_t pos, double factor)
{
  for (size_t i = 0; i < count; i++)
  {
    const point_t oldCenter = shapes[i]->getFrameRect().pos;
    const point_t newCenter{pos.x + (oldCenter.x - pos.x) * factor, pos.y + (oldCenter.y - pos.y) * factor};

    shapes[i]->scale(factor);
    shapes[i]->move(newCenter);
  }
}

int main()
{
  grebenshchikov::Rectangle rect({1.0, 3.0}, 4.0, 2.0);
  grebenshchikov::Circle circle({6.0, 3.0}, 1.0);

  constexpr size_t count = 2;
  grebenshchikov::Shape** const shapes
      = static_cast< grebenshchikov::Shape** >(std::malloc(count * sizeof(grebenshchikov::Shape*)));

  if (shapes == nullptr)
  {
    std::cerr << "Not enough memory\n";
    return 2;
  }

  shapes[0] = &rect;
  shapes[1] = &circle;

  grebenshchikov::printShapes(shapes, count);

  grebenshchikov::point_t pos{};
  double factor = 0.0;
  if (!(std::cin >> pos.x >> pos.y >> factor) || !(factor > 0.0))
  {
    std::cerr << "Expected coordinates and a positive scale factor\n";
    std::free(shapes);
    return 1;
  }

  grebenshchikov::scaleShapes(shapes, count, pos, factor);
  grebenshchikov::printShapes(shapes, count);

  std::free(shapes);
  return 0;
}
