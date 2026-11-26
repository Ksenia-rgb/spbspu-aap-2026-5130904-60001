#include <iostream>
#include <stdexcept>
#include "rectangle.hpp"
#include "ring.hpp"
#include "bubble.hpp"

int main()
{
  kotyurgina::Rectangle rectangle({ 0.0, 0.0 }, 4.0, 6.0);
  kotyurgina::Ring ring({ 5.0, 5.0 }, 3.0, 1.0);
  kotyurgina::Bubble bubble({ 2.0, 2.0 }, { 3.0, 2.0 }, 2.0);

  kotyurgina::Shape* shapes[] = { &rectangle, &ring, &bubble };

  const size_t count = sizeof(shapes) / sizeof(shapes[0]);
  double totalArea = 0.0;

  for (size_t i = 0; i < count; i++)
  {
    const double area = shapes[i]->getArea();
    std::cout << area << '\n';
    totalArea += area;
  }
  std::cout << totalArea << '\n';
  return 0;
}