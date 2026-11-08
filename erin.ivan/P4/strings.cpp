#include "strings.hpp"

#include <cstdlib>
#include <iostream>

static int hasSym(const char * beg, const char * end, char ch)
{
  for (const char * p = beg; p != end; ++p)
  {
    if (*p == ch)
    {
      return 1;
    }
  }
  return 0;
}

size_t erin::getLen(const char * str)
{
  size_t len = 0;
  while (str[len] != '\0')
  {
    ++len;
  }
  return len;
}

char * erin::readStr(std::istream & in, size_t * out_len)
{
  constexpr size_t init_cap = 16;
  constexpr size_t grow_step = 2;
  size_t cap = init_cap;
  size_t len = 0;

  char * buf = static_cast< char * >(std::malloc(cap * sizeof(char)));
  if (buf == nullptr)
  {
    return nullptr;
  }

  in >> std::noskipws;
  char ch = '\0';
  while ((in >> ch) && (ch != '\n'))
  {
    if (len + 1 >= cap)
    {
      const size_t new_cap = cap * grow_step;
      char * new_buf = static_cast< char * >(std::malloc(new_cap * sizeof(char)));
      if (new_buf == nullptr)
      {
        std::free(buf);
        in >> std::skipws;
        return nullptr;
      }
      for (size_t i = 0; i < len; ++i)
      {
        new_buf[i] = buf[i];
      }
      std::free(buf);
      buf = new_buf;
      cap = new_cap;
    }
    buf[len] = ch;
    ++len;
  }
  in >> std::skipws;

  buf[len] = '\0';
  if (out_len != nullptr)
  {
    *out_len = len;
  }
  return buf;
}

char * erin::uniteStr(char * dst, const char * s1, const char * s2)
{
  char * out = dst;
  const char * p1 = s1;
  const char * p2 = s2;

  while ((*p1 != '\0') && (*p2 != '\0'))
  {
    *out = *p1;
    ++out;
    ++p1;
    *out = *p2;
    ++out;
    ++p2;
  }
  while (*p1 != '\0')
  {
    *out = *p1;
    ++out;
    ++p1;
  }
  while (*p2 != '\0')
  {
    *out = *p2;
    ++out;
    ++p2;
  }
  *out = '\0';
  return dst;
}

char * erin::findRep(char * dst, const char * src)
{
  char * out = dst;
  const size_t len = erin::getLen(src);
  const char * end = src + len;

  for (const char * cur = src; cur != end; ++cur)
  {
    if ((hasSym(src, cur, *cur) == 0) && (hasSym(cur + 1, end, *cur) != 0))
    {
      *out = *cur;
      ++out;
    }
  }
  *out = '\0';
  return dst;
}
