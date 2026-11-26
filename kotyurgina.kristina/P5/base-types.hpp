#ifndef KOTYURGINA_BASE_TYPES_HPP
#define KOTYURGINA_BASE_TYPES_HPP

namespace kotyurgina
{
  struct point_t
  {
    double x;
    double y;
  };

  struct rectangle_t
  {
    double width;
    double height;
    point_t pos;
  };
}

#endif
