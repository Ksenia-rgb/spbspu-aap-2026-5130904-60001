#include <iomanip>
#include <iostream>

#include <circle.hpp>
#include <diamond.hpp>
#include <ellipse.hpp>
#include <rectangle.hpp>
#include <ring.hpp>
#include <rubber.hpp>
#include <shape-utils.hpp>
#include <shape.hpp>
#include <square.hpp>
#include <triangle.hpp>

namespace sharov {
  namespace {
    constexpr double RECTANGLE_WIDTH = 6.0;
    constexpr double RECTANGLE_HEIGHT = 4.0;
    constexpr double SQUARE_SIDE = 3.0;
    constexpr double DIAMOND_HORIZONTAL = 5.0;
    constexpr double DIAMOND_VERTICAL = 3.0;
    constexpr double CIRCLE_RADIUS = 2.0;
    constexpr double RING_OUTER_RADIUS = 3.0;
    constexpr double RING_INNER_RADIUS = 1.5;
    constexpr double RUBBER_OUTER_RADIUS = 3.0;
    constexpr double RUBBER_INNER_RADIUS = 1.0;
    constexpr double ELLIPSE_HORIZONTAL = 4.0;
    constexpr double ELLIPSE_VERTICAL = 2.0;
    constexpr double TRIANGLE_LEG_X = 4.0;
    constexpr double TRIANGLE_LEG_Y = 3.0;

    constexpr point_t RECTANGLE_CENTER{-RECTANGLE_WIDTH, 1.0};
    constexpr point_t SQUARE_CENTER{-1.0, TRIANGLE_LEG_X};
    constexpr point_t DIAMOND_CENTER{TRIANGLE_LEG_X, DIAMOND_HORIZONTAL};
    constexpr point_t CIRCLE_CENTER{1.0, -CIRCLE_RADIUS};
    constexpr point_t RING_CENTER{-SQUARE_SIDE, -TRIANGLE_LEG_X};
    constexpr point_t RUBBER_OUTER_CENTER{-ELLIPSE_HORIZONTAL, RING_OUTER_RADIUS};
    constexpr point_t RUBBER_INNER_CENTER{RUBBER_OUTER_CENTER.x + HALF, RUBBER_OUTER_CENTER.y + HALF};
    constexpr point_t ELLIPSE_CENTER{RECTANGLE_WIDTH, -SQUARE_SIDE};
    constexpr point_t TRIANGLE_FIRST{0.0, 0.0};
    constexpr point_t TRIANGLE_SECOND{TRIANGLE_LEG_X, 0.0};
    constexpr point_t TRIANGLE_THIRD{0.0, TRIANGLE_LEG_Y};

    void printFrameRect(const rectangle_t &frameRect)
    {
      std::cout << "pos = (" << frameRect.pos.x << ", " << frameRect.pos.y << "), width = " << frameRect.width
                << ", height = " << frameRect.height;
    }

    double getTotalArea(Shape *const *const shapes, int count)
    {
      double totalArea = 0.0;
      for (int i = 0; i < count; ++i) {
        totalArea += shapes[i]->getArea();
      }
      return totalArea;
    }

    rectangle_t getCommonFrameRect(Shape *const *const shapes, int count)
    {
      const rectangle_t first = shapes[0]->getFrameRect();
      double minimumX = first.pos.x - first.width * HALF;
      double maximumX = first.pos.x + first.width * HALF;
      double minimumY = first.pos.y - first.height * HALF;
      double maximumY = first.pos.y + first.height * HALF;
      for (int i = 1; i < count; ++i) {
        const rectangle_t frameRect = shapes[i]->getFrameRect();
        const double left = frameRect.pos.x - frameRect.width * HALF;
        const double right = frameRect.pos.x + frameRect.width * HALF;
        const double bottom = frameRect.pos.y - frameRect.height * HALF;
        const double top = frameRect.pos.y + frameRect.height * HALF;
        if (left < minimumX) {
          minimumX = left;
        }
        if (right > maximumX) {
          maximumX = right;
        }
        if (bottom < minimumY) {
          minimumY = bottom;
        }
        if (top > maximumY) {
          maximumY = top;
        }
      }
      const point_t center{(minimumX + maximumX) * HALF, (minimumY + maximumY) * HALF};
      return rectangle_t{maximumX - minimumX, maximumY - minimumY, center};
    }

    void printReport(const char *const title, Shape *const *const shapes, const char *const *const names, int count)
    {
      std::cout << title << "\n";
      for (int i = 0; i < count; ++i) {
        std::cout << "  " << names[i] << ": area = " << shapes[i]->getArea() << ", frame rect: ";
        printFrameRect(shapes[i]->getFrameRect());
        std::cout << "\n";
      }
      std::cout << "  total area = " << getTotalArea(shapes, count) << "\n";
      std::cout << "  common frame rect: ";
      printFrameRect(getCommonFrameRect(shapes, count));
      std::cout << "\n";
    }

    void scaleShape(Shape &shape, const point_t &point, double coefficient)
    {
      const point_t center = shape.getFrameRect().pos;
      shape.move(point_t{point.x - center.x, point.y - center.y});
      shape.scale(coefficient);
      const point_t scaledCenter = shape.getFrameRect().pos;
      const point_t targetCenter{
          point.x + (center.x - point.x) * coefficient, point.y + (center.y - point.y) * coefficient};
      shape.move(targetCenter.x - scaledCenter.x, targetCenter.y - scaledCenter.y);
    }

    void scaleShapes(Shape *const *const shapes, int count, const point_t &point, double coefficient)
    {
      for (int i = 0; i < count; ++i) {
        scaleShape(*shapes[i], point, coefficient);
      }
    }
  }

  int run()
  {
    Rectangle rectangle(RECTANGLE_WIDTH, RECTANGLE_HEIGHT, RECTANGLE_CENTER);
    Square square(SQUARE_SIDE, SQUARE_CENTER);
    Diamond diamond(DIAMOND_HORIZONTAL, DIAMOND_VERTICAL, DIAMOND_CENTER);
    Circle circle(CIRCLE_RADIUS, CIRCLE_CENTER);
    Ring ring(RING_OUTER_RADIUS, RING_INNER_RADIUS, RING_CENTER);
    Rubber rubber(RUBBER_OUTER_RADIUS, RUBBER_INNER_RADIUS, RUBBER_OUTER_CENTER, RUBBER_INNER_CENTER);
    Ellipse ellipse(ELLIPSE_HORIZONTAL, ELLIPSE_VERTICAL, ELLIPSE_CENTER);
    Triangle triangle(TRIANGLE_FIRST, TRIANGLE_SECOND, TRIANGLE_THIRD);

    Shape *const shapes[] = {&rectangle, &square, &diamond, &circle, &ring, &rubber, &ellipse, &triangle};
    const char *const names[] = {"Rectangle", "Square", "Diamond", "Circle", "Ring", "Rubber", "Ellipse", "Triangle"};
    const int shapeCount = static_cast< int >(sizeof(shapes) / sizeof(shapes[0]));

    std::cout << std::fixed << std::setprecision(4);
    printReport("Shapes before scaling:", shapes, names, shapeCount);

    double pointX = 0.0;
    double pointY = 0.0;
    double coefficient = 0.0;
    std::cout << "\nEnter the scaling point and the coefficient (x y coefficient): ";
    if (!(std::cin >> pointX >> pointY >> coefficient)) {
      std::cerr << "error: failed to read the scaling point and the coefficient\n";
      return 1;
    }
    if (!(coefficient > 0.0)) {
      std::cerr << "error: the scale coefficient must be positive\n";
      return 2;
    }

    scaleShapes(shapes, shapeCount, point_t{pointX, pointY}, coefficient);
    printReport("\nShapes after scaling:", shapes, names, shapeCount);
    return 0;
  }
}

int main()
{
  return sharov::run();
}
