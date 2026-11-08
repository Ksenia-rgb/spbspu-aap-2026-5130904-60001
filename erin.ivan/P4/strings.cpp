#include "strings.hpp"

size_t erin::getLen(const char * str)
{
  size_t len = 0;
  while (str[len] != '\0')
  {
    ++len;
  }
  return len;
}
