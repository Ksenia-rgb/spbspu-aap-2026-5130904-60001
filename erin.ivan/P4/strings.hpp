#ifndef STRINGS_HPP
#define STRINGS_HPP

#include <cstddef>
#include <iosfwd>

namespace erin
{
  char * readStr(std::istream & in, size_t * out_len);
  char * uniteStr(char * dst, const char * s1, const char * s2);
  char * findRep(char * dst, const char * src);
}

#endif
