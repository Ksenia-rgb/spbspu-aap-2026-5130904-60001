#ifndef STRINGS_HPP
#define STRINGS_HPP

#include <iostream>
#include <cstddef>

char* readLine(std::istream* in, size_t* out_len);
int hasSam(const char* str1, const char* str2);
size_t countDgt(const char* str);
char* dgtSnd(char* dst, const char* src1, const char* src2);

#endif
