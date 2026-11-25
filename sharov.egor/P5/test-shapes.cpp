#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <vector>

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

static_assert(std::is_trivially_copyable< sharov::point_t >::value, "point_t must be trivially copyable");
static_assert(std::is_standard_layout< sharov::point_t >::value, "point_t must have the standard layout");
static_assert(std::is_trivially_copyable< sharov::rectangle_t >::value, "rectangle_t must be trivially copyable");
static_assert(std::is_standard_layout< sharov::rectangle_t >::value, "rectangle_t must have the standard layout");
static_assert(std::is_abstract< sharov::Shape >::value, "Shape must be an abstract interface");

namespace {
  const double TOLERANCE = 1e-9;
  int gCheckCount = 0;
  int gFailureCount = 0;
  int gDestroyedCount = 0;

  void checkClose(double actual, double expected, const char *const message)
  {
    ++gCheckCount;
    if (std::fabs(actual - expected) > TOLERANCE) {
      ++gFailureCount;
      std::cerr << "FAILED: " << message << ": expected " << expected << ", got " << actual << "\n";
    }
  }

  void checkTrue(bool condition, const char *const message)
  {
    ++gCheckCount;
    if (!condition) {
      ++gFailureCount;
      std::cerr << "FAILED: " << message << "\n";
    }
  }

  void checkPoint(const sharov::point_t &actual, const sharov::point_t &expected, const char *const message)
  {
    ++gCheckCount;
    if (std::fabs(actual.x - expected.x) > TOLERANCE || std::fabs(actual.y - expected.y) > TOLERANCE) {
      ++gFailureCount;
      std::cerr << "FAILED: " << message << ": expected (" << expected.x << ", " << expected.y << "), got (" << actual.x
                << ", " << actual.y << ")\n";
    }
  }

  void checkFrameRect(const sharov::rectangle_t &actual, const sharov::rectangle_t &expected, const char *const message)
  {
    ++gCheckCount;
    const bool matches = std::fabs(actual.width - expected.width) <= TOLERANCE
        && std::fabs(actual.height - expected.height) <= TOLERANCE
        && std::fabs(actual.pos.x - expected.pos.x) <= TOLERANCE
        && std::fabs(actual.pos.y - expected.pos.y) <= TOLERANCE;
    if (!matches) {
      ++gFailureCount;
      std::cerr << "FAILED: " << message << ": expected {width = " << expected.width << ", height = " << expected.height
                << ", pos = (" << expected.pos.x << ", " << expected.pos.y << ")}, got {width = " << actual.width
                << ", height = " << actual.height << ", pos = (" << actual.pos.x << ", " << actual.pos.y << ")}\n";
    }
  }

  template< typename Function >
  void checkInvalidArgument(Function function, const char *message)
  {
    ++gCheckCount;
    try {
      function();
    } catch (const std::invalid_argument &) {
      return;
    } catch (...) {
      ++gFailureCount;
      std::cerr << "FAILED: " << message << ": unexpected exception type\n";
      return;
    }
    ++gFailureCount;
    std::cerr << "FAILED: " << message << ": std::invalid_argument was not thrown\n";
  }

  class DestructionProbe: public sharov::Shape {
  public:
    ~DestructionProbe() override
    {
      ++gDestroyedCount;
    }

    double getArea() const override
    {
      return 1.0;
    }

    sharov::rectangle_t getFrameRect() const override
    {
      return sharov::rectangle_t{1.0, 1.0, sharov::point_t{0.0, 0.0}};
    }

    void move(const sharov::point_t &) override
    {}

    void move(double, double) override
    {}

    void scale(double) override
    {}
  };

  void testRectangle()
  {
    sharov::Rectangle rectangle(4.0, 2.0, sharov::point_t{1.0, 2.0});
    checkClose(rectangle.getArea(), 8.0, "rectangle area");
    checkFrameRect(
        rectangle.getFrameRect(), sharov::rectangle_t{4.0, 2.0, sharov::point_t{1.0, 2.0}}, "rectangle frame rect");

    rectangle.move(sharov::point_t{5.0, 6.0});
    checkFrameRect(
        rectangle.getFrameRect(), sharov::rectangle_t{4.0, 2.0, sharov::point_t{5.0, 6.0}}, "rectangle move to point");

    rectangle.move(1.0, -1.0);
    checkFrameRect(
        rectangle.getFrameRect(), sharov::rectangle_t{4.0, 2.0, sharov::point_t{6.0, 5.0}}, "rectangle move by offset");

    rectangle.scale(2.0);
    checkClose(rectangle.getArea(), 32.0, "rectangle area after scaling");
    checkFrameRect(rectangle.getFrameRect(), sharov::rectangle_t{8.0, 4.0, sharov::point_t{6.0, 5.0}},
        "rectangle frame rect after scaling");

    rectangle.scale(0.25);
    checkClose(rectangle.getArea(), 2.0, "rectangle area after the second scaling");
    checkFrameRect(rectangle.getFrameRect(), sharov::rectangle_t{2.0, 1.0, sharov::point_t{6.0, 5.0}},
        "rectangle frame rect after the second scaling");

    checkInvalidArgument(
        []()
        {
          sharov::Rectangle const shape(0.0, 1.0, sharov::point_t{0.0, 0.0});
        },
        "rectangle zero width");
    checkInvalidArgument(
        []()
        {
          sharov::Rectangle const shape(-1.0, 1.0, sharov::point_t{0.0, 0.0});
        },
        "rectangle negative width");
    checkInvalidArgument(
        []()
        {
          sharov::Rectangle const shape(1.0, 0.0, sharov::point_t{0.0, 0.0});
        },
        "rectangle zero height");
    checkInvalidArgument(
        []()
        {
          sharov::Rectangle const shape(1.0, -2.0, sharov::point_t{0.0, 0.0});
        },
        "rectangle negative height");
    checkInvalidArgument(
        [&rectangle]()
        {
          rectangle.scale(0.0);
        },
        "rectangle zero scale coefficient");
    checkInvalidArgument(
        [&rectangle]()
        {
          rectangle.scale(-1.0);
        },
        "rectangle negative scale coefficient");
    checkClose(rectangle.getArea(), 2.0, "rectangle area is unchanged after a rejected scaling");
  }

  void testSquare()
  {
    sharov::Square square(3.0, sharov::point_t{-1.0, 4.0});
    checkClose(square.getArea(), 9.0, "square area");
    checkFrameRect(
        square.getFrameRect(), sharov::rectangle_t{3.0, 3.0, sharov::point_t{-1.0, 4.0}}, "square frame rect");

    square.move(sharov::point_t{2.0, 2.0});
    checkFrameRect(
        square.getFrameRect(), sharov::rectangle_t{3.0, 3.0, sharov::point_t{2.0, 2.0}}, "square move to point");

    square.move(-3.0, 1.0);
    checkFrameRect(
        square.getFrameRect(), sharov::rectangle_t{3.0, 3.0, sharov::point_t{-1.0, 3.0}}, "square move by offset");

    square.scale(2.0);
    checkClose(square.getArea(), 36.0, "square area after scaling");
    checkFrameRect(square.getFrameRect(), sharov::rectangle_t{6.0, 6.0, sharov::point_t{-1.0, 3.0}},
        "square frame rect after scaling");

    checkInvalidArgument(
        []()
        {
          sharov::Square const shape(0.0, sharov::point_t{0.0, 0.0});
        },
        "square zero side");
    checkInvalidArgument(
        []()
        {
          sharov::Square const shape(-2.0, sharov::point_t{0.0, 0.0});
        },
        "square negative side");
    checkInvalidArgument(
        [&square]()
        {
          square.scale(0.0);
        },
        "square zero scale coefficient");
    checkInvalidArgument(
        [&square]()
        {
          square.scale(-3.0);
        },
        "square negative scale coefficient");
  }

  void testDiamond()
  {
    sharov::Diamond diamond(6.0, 4.0, sharov::point_t{4.0, 5.0});
    checkClose(diamond.getArea(), 12.0, "diamond area");
    checkFrameRect(
        diamond.getFrameRect(), sharov::rectangle_t{6.0, 4.0, sharov::point_t{4.0, 5.0}}, "diamond frame rect");

    diamond.scale(0.5);
    checkClose(diamond.getArea(), 3.0, "diamond area after scaling");
    checkFrameRect(diamond.getFrameRect(), sharov::rectangle_t{3.0, 2.0, sharov::point_t{4.0, 5.0}},
        "diamond frame rect after scaling");

    diamond.move(-1.0, 2.0);
    checkFrameRect(
        diamond.getFrameRect(), sharov::rectangle_t{3.0, 2.0, sharov::point_t{3.0, 7.0}}, "diamond move by offset");

    checkInvalidArgument(
        []()
        {
          sharov::Diamond const shape(0.0, 1.0, sharov::point_t{0.0, 0.0});
        },
        "diamond zero horizontal diagonal");
    checkInvalidArgument(
        []()
        {
          sharov::Diamond const shape(1.0, 0.0, sharov::point_t{0.0, 0.0});
        },
        "diamond zero vertical diagonal");
    checkInvalidArgument(
        []()
        {
          sharov::Diamond const shape(-2.0, 1.0, sharov::point_t{0.0, 0.0});
        },
        "diamond negative horizontal diagonal");
    checkInvalidArgument(
        [&diamond]()
        {
          diamond.scale(0.0);
        },
        "diamond zero scale coefficient");
  }

  void testCircle()
  {
    sharov::Circle circle(2.0, sharov::point_t{1.0, -2.0});
    checkClose(circle.getArea(), 4.0 * sharov::PI, "circle area");
    checkFrameRect(
        circle.getFrameRect(), sharov::rectangle_t{4.0, 4.0, sharov::point_t{1.0, -2.0}}, "circle frame rect");

    circle.scale(3.0);
    checkClose(circle.getArea(), 36.0 * sharov::PI, "circle area after scaling");
    checkFrameRect(circle.getFrameRect(), sharov::rectangle_t{12.0, 12.0, sharov::point_t{1.0, -2.0}},
        "circle frame rect after scaling");

    circle.move(sharov::point_t{-5.0, 7.0});
    checkFrameRect(
        circle.getFrameRect(), sharov::rectangle_t{12.0, 12.0, sharov::point_t{-5.0, 7.0}}, "circle move to point");

    checkInvalidArgument(
        []()
        {
          sharov::Circle const shape(0.0, sharov::point_t{0.0, 0.0});
        },
        "circle zero radius");
    checkInvalidArgument(
        []()
        {
          sharov::Circle const shape(-2.0, sharov::point_t{0.0, 0.0});
        },
        "circle negative radius");
    checkInvalidArgument(
        [&circle]()
        {
          circle.scale(0.0);
        },
        "circle zero scale coefficient");
  }

  void testRing()
  {
    sharov::Ring ring(5.0, 3.0, sharov::point_t{-3.0, -4.0});
    checkClose(ring.getArea(), 16.0 * sharov::PI, "ring area");
    checkFrameRect(
        ring.getFrameRect(), sharov::rectangle_t{10.0, 10.0, sharov::point_t{-3.0, -4.0}}, "ring frame rect");

    ring.scale(0.5);
    checkClose(ring.getArea(), 4.0 * sharov::PI, "ring area after scaling");
    checkFrameRect(ring.getFrameRect(), sharov::rectangle_t{5.0, 5.0, sharov::point_t{-3.0, -4.0}},
        "ring frame rect after scaling");

    checkInvalidArgument(
        []()
        {
          sharov::Ring const shape(3.0, 5.0, sharov::point_t{0.0, 0.0});
        },
        "ring inner radius is greater than the outer one");
    checkInvalidArgument(
        []()
        {
          sharov::Ring const shape(5.0, 5.0, sharov::point_t{0.0, 0.0});
        },
        "ring radii are equal");
    checkInvalidArgument(
        []()
        {
          sharov::Ring const shape(0.0, 0.0, sharov::point_t{0.0, 0.0});
        },
        "ring zero radii");
    checkInvalidArgument(
        []()
        {
          sharov::Ring const shape(5.0, 0.0, sharov::point_t{0.0, 0.0});
        },
        "ring zero inner radius");
    checkInvalidArgument(
        []()
        {
          sharov::Ring const shape(5.0, -1.0, sharov::point_t{0.0, 0.0});
        },
        "ring negative inner radius");
    checkInvalidArgument(
        [&ring]()
        {
          ring.scale(0.0);
        },
        "ring zero scale coefficient");
  }

  void testRubber()
  {
    sharov::Rubber rubber(5.0, 3.0, sharov::point_t{-3.0, -4.0}, sharov::point_t{-2.0, -4.0});
    checkClose(rubber.getArea(), 16.0 * sharov::PI, "rubber area");
    checkFrameRect(rubber.getFrameRect(),
        sharov::rectangle_t{10.0, 10.0, sharov::point_t{-3.0, -4.0}}, "rubber frame rect");

    rubber.move(sharov::point_t{1.0, 1.0});
    checkFrameRect(rubber.getFrameRect(),
        sharov::rectangle_t{10.0, 10.0, sharov::point_t{0.0, 1.0}}, "rubber frame rect after moving to a point");
    checkClose(rubber.getArea(), 16.0 * sharov::PI, "rubber area after moving");

    rubber.move(1.0, -2.0);
    checkFrameRect(rubber.getFrameRect(),
        sharov::rectangle_t{10.0, 10.0, sharov::point_t{1.0, -1.0}}, "rubber frame rect after shifting");

    rubber.scale(0.5);
    checkClose(rubber.getArea(), 4.0 * sharov::PI, "rubber area after scaling");
    checkFrameRect(rubber.getFrameRect(),
        sharov::rectangle_t{5.0, 5.0, sharov::point_t{1.5, -1.0}}, "rubber frame rect after scaling");

    checkInvalidArgument(
        []()
        {
          sharov::Rubber const shape(3.0, 5.0, sharov::point_t{0.0, 0.0}, sharov::point_t{0.5, 0.0});
        },
        "rubber inner radius is greater than the outer one");
    checkInvalidArgument(
        []()
        {
          sharov::Rubber const shape(5.0, 5.0, sharov::point_t{0.0, 0.0}, sharov::point_t{0.5, 0.0});
        },
        "rubber radii are equal");
    checkInvalidArgument(
        []()
        {
          sharov::Rubber const shape(5.0, 3.0, sharov::point_t{2.0, 2.0}, sharov::point_t{2.0, 2.0});
        },
        "rubber circles are coaxial");
    checkInvalidArgument(
        []()
        {
          sharov::Rubber const shape(5.0, 3.0, sharov::point_t{0.0, 0.0}, sharov::point_t{3.0, 0.0});
        },
        "rubber inner circle does not lie inside the outer one");
    checkInvalidArgument(
        []()
        {
          sharov::Rubber const shape(0.0, 0.0, sharov::point_t{0.0, 0.0}, sharov::point_t{0.5, 0.0});
        },
        "rubber zero radii");
    checkInvalidArgument(
        []()
        {
          sharov::Rubber const shape(5.0, -1.0, sharov::point_t{0.0, 0.0}, sharov::point_t{0.5, 0.0});
        },
        "rubber negative inner radius");
    checkInvalidArgument(
        [&rubber]()
        {
          rubber.scale(0.0);
        },
        "rubber zero scale coefficient");
  }

  void testEllipse()
  {
    sharov::Ellipse ellipse(3.0, 2.0, sharov::point_t{6.0, -3.0});
    checkClose(ellipse.getArea(), 6.0 * sharov::PI, "ellipse area");
    checkFrameRect(
        ellipse.getFrameRect(), sharov::rectangle_t{6.0, 4.0, sharov::point_t{6.0, -3.0}}, "ellipse frame rect");

    ellipse.scale(2.0);
    checkClose(ellipse.getArea(), 24.0 * sharov::PI, "ellipse area after scaling");
    checkFrameRect(ellipse.getFrameRect(), sharov::rectangle_t{12.0, 8.0, sharov::point_t{6.0, -3.0}},
        "ellipse frame rect after scaling");

    ellipse.move(2.0, 3.0);
    checkFrameRect(
        ellipse.getFrameRect(), sharov::rectangle_t{12.0, 8.0, sharov::point_t{8.0, 0.0}}, "ellipse move by offset");

    checkInvalidArgument(
        []()
        {
          sharov::Ellipse const shape(0.0, 1.0, sharov::point_t{0.0, 0.0});
        },
        "ellipse zero horizontal radius");
    checkInvalidArgument(
        []()
        {
          sharov::Ellipse const shape(1.0, 0.0, sharov::point_t{0.0, 0.0});
        },
        "ellipse zero vertical radius");
    checkInvalidArgument(
        []()
        {
          sharov::Ellipse const shape(-1.0, 2.0, sharov::point_t{0.0, 0.0});
        },
        "ellipse negative horizontal radius");
    checkInvalidArgument(
        [&ellipse]()
        {
          ellipse.scale(-1.0);
        },
        "ellipse negative scale coefficient");
  }

  void testTriangle()
  {
    sharov::Triangle triangle(sharov::point_t{0.0, 0.0}, sharov::point_t{4.0, 0.0}, sharov::point_t{0.0, 3.0});
    checkClose(triangle.getArea(), 6.0, "triangle area");
    checkFrameRect(
        triangle.getFrameRect(), sharov::rectangle_t{4.0, 3.0, sharov::point_t{2.0, 1.5}}, "triangle frame rect");

    triangle.move(sharov::point_t{10.0, 10.0});
    checkFrameRect(triangle.getFrameRect(), sharov::rectangle_t{4.0, 3.0, sharov::point_t{10.0 + 2.0 / 3.0, 10.5}},
        "triangle move to point keeps the centroid");

    triangle.scale(2.0);
    checkClose(triangle.getArea(), 24.0, "triangle area after scaling");
    checkFrameRect(triangle.getFrameRect(), sharov::rectangle_t{8.0, 6.0, sharov::point_t{10.0 + 4.0 / 3.0, 11.0}},
        "triangle frame rect after scaling about the centroid");

    sharov::Triangle const reversed(sharov::point_t{0.0, 0.0}, sharov::point_t{0.0, 3.0}, sharov::point_t{4.0, 0.0});
    checkClose(reversed.getArea(), 6.0, "triangle area does not depend on the vertex order");

    checkInvalidArgument(
        []()
        {
          sharov::Triangle const shape(sharov::point_t{0.0, 0.0}, sharov::point_t{1.0, 1.0}, sharov::point_t{2.0, 2.0});
        },
        "triangle with collinear vertices");
    checkInvalidArgument(
        []()
        {
          sharov::Triangle const shape(sharov::point_t{1.0, 1.0}, sharov::point_t{1.0, 1.0}, sharov::point_t{2.0, 2.0});
        },
        "triangle with coincident vertices");
    checkInvalidArgument(
        [&triangle]()
        {
          triangle.scale(0.0);
        },
        "triangle zero scale coefficient");
    checkInvalidArgument(
        [&triangle]()
        {
          triangle.scale(-2.0);
        },
        "triangle negative scale coefficient");
    checkClose(triangle.getArea(), 24.0, "triangle area is unchanged after a rejected scaling");
  }

  void testPolymorphism()
  {
    sharov::Rectangle rectangle(6.0, 4.0, sharov::point_t{-6.0, 1.0});
    sharov::Square square(3.0, sharov::point_t{-1.0, 4.0});
    sharov::Diamond diamond(5.0, 3.0, sharov::point_t{4.0, 5.0});
    sharov::Circle circle(2.0, sharov::point_t{1.0, -2.0});
    sharov::Ring ring(3.0, 1.5, sharov::point_t{-3.0, -4.0});
    sharov::Ellipse ellipse(4.0, 2.0, sharov::point_t{6.0, -3.0});
    sharov::Triangle triangle(sharov::point_t{0.0, 0.0}, sharov::point_t{4.0, 0.0}, sharov::point_t{0.0, 3.0});

    sharov::Shape *const shapes[] = {&rectangle, &square, &diamond, &circle, &ring, &ellipse, &triangle};
    const int shapeCount = static_cast< int >(sizeof(shapes) / sizeof(shapes[0]));
    checkTrue(shapeCount == 7, "the polymorphic array contains every implemented shape");

    double totalArea = 0.0;
    for (int i = 0; i < shapeCount; ++i) {
      totalArea += shapes[i]->getArea();
    }
    const double expectedTotalArea = 24.0 + 9.0 + 7.5 + 4.0 * sharov::PI + 6.75 * sharov::PI + 8.0 * sharov::PI + 6.0;
    checkClose(totalArea, expectedTotalArea, "total area of the polymorphic array");

    double minimumX = 0.0;
    double maximumX = 0.0;
    double minimumY = 0.0;
    double maximumY = 0.0;
    for (int i = 0; i < shapeCount; ++i) {
      const sharov::rectangle_t frameRect = shapes[i]->getFrameRect();
      const double left = frameRect.pos.x - frameRect.width / 2.0;
      const double right = frameRect.pos.x + frameRect.width / 2.0;
      const double bottom = frameRect.pos.y - frameRect.height / 2.0;
      const double top = frameRect.pos.y + frameRect.height / 2.0;
      if (i == 0 || left < minimumX) {
        minimumX = left;
      }
      if (i == 0 || right > maximumX) {
        maximumX = right;
      }
      if (i == 0 || bottom < minimumY) {
        minimumY = bottom;
      }
      if (i == 0 || top > maximumY) {
        maximumY = top;
      }
    }
    const sharov::rectangle_t commonFrameRect{maximumX - minimumX, maximumY - minimumY,
        sharov::point_t{(minimumX + maximumX) / 2.0, (minimumY + maximumY) / 2.0}};
    checkFrameRect(commonFrameRect, sharov::rectangle_t{19.0, 13.5, sharov::point_t{0.5, -0.25}},
        "common frame rect of the polymorphic array");
  }

  void testScalingAboutExternalPoint()
  {
    sharov::Rectangle rectangle(6.0, 4.0, sharov::point_t{-6.0, 1.0});
    sharov::Square square(3.0, sharov::point_t{-1.0, 4.0});
    sharov::Diamond diamond(5.0, 3.0, sharov::point_t{4.0, 5.0});
    sharov::Circle circle(2.0, sharov::point_t{1.0, -2.0});
    sharov::Ring ring(3.0, 1.5, sharov::point_t{-3.0, -4.0});
    sharov::Ellipse ellipse(4.0, 2.0, sharov::point_t{6.0, -3.0});
    sharov::Triangle triangle(sharov::point_t{0.0, 0.0}, sharov::point_t{4.0, 0.0}, sharov::point_t{0.0, 3.0});

    sharov::Shape *const shapes[] = {&rectangle, &square, &diamond, &circle, &ring, &ellipse, &triangle};
    const int shapeCount = static_cast< int >(sizeof(shapes) / sizeof(shapes[0]));
    const sharov::point_t point{3.0, -2.0};
    const double coefficient = 2.5;

    std::vector< double > areas(shapeCount);
    std::vector< sharov::rectangle_t > frames(shapeCount);
    for (int i = 0; i < shapeCount; ++i) {
      areas[i] = shapes[i]->getArea();
      frames[i] = shapes[i]->getFrameRect();
    }

    for (int i = 0; i < shapeCount; ++i) {
      sharov::Shape &shape = *shapes[i];
      const sharov::point_t center = shape.getFrameRect().pos;
      shape.move(sharov::point_t{point.x - center.x, point.y - center.y});
      shape.scale(coefficient);
      const sharov::point_t scaledCenter = shape.getFrameRect().pos;
      const sharov::point_t targetCenter{
          point.x + (center.x - point.x) * coefficient, point.y + (center.y - point.y) * coefficient};
      shape.move(targetCenter.x - scaledCenter.x, targetCenter.y - scaledCenter.y);
    }

    for (int i = 0; i < shapeCount; ++i) {
      const sharov::rectangle_t actualFrame = shapes[i]->getFrameRect();
      const sharov::point_t expectedCenter{
          point.x + (frames[i].pos.x - point.x) * coefficient, point.y + (frames[i].pos.y - point.y) * coefficient};
      checkPoint(actualFrame.pos, expectedCenter, "frame center after scaling about an external point");
      checkClose(actualFrame.width, frames[i].width * coefficient, "frame width after scaling about an external point");
      checkClose(
          actualFrame.height, frames[i].height * coefficient, "frame height after scaling about an external point");
      checkClose(
          shapes[i]->getArea(), areas[i] * coefficient * coefficient, "area after scaling about an external point");
    }
  }

  void testVirtualDestructor()
  {
    gDestroyedCount = 0;
    const sharov::Shape *const shape = new DestructionProbe();
    delete shape;
    checkTrue(gDestroyedCount == 1, "the virtual destructor is called through a Shape pointer");
  }
}

int main()
{
  testRectangle();
  testSquare();
  testDiamond();
  testCircle();
  testRing();
  testRubber();
  testEllipse();
  testTriangle();
  testPolymorphism();
  testScalingAboutExternalPoint();
  testVirtualDestructor();

  std::cout << "checks: " << gCheckCount << ", failures: " << gFailureCount << "\n";
  return gFailureCount == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
