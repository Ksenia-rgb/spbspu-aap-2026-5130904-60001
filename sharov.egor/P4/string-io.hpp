#ifndef STRING_IO_HPP
#define STRING_IO_HPP

#include <iosfwd>

namespace sharov {
  char *readString(std::istream &input, int *length);
}

#endif
