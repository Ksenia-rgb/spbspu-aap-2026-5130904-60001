#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iosfwd>
#include <cstddef>

std::istream& readMatrix(std::istream& in, int* m, size_t r, size_t c);
void printMatrix(std::ostream& out, const int* m, size_t r, size_t c);
size_t countNzrDig(const int* m, size_t r, size_t c);
void lftBotCnt(int* m, size_t r, size_t c);

#endif