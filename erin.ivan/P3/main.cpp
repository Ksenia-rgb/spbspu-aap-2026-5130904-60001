#include <cstdlib>
#include <fstream>
#include <iostream>
#include "matrix.hpp"

int main(int argc, char ** argv)
{
  if (argc != 4)
  {
    std::cerr << "Wrong args count\n";
    return 1;
  }

  char * end = nullptr;
  long num = std::strtol(argv[1], &end, 10);
  if (argv[1][0] == '\0' || *end != '\0' || (num != 1 && num != 2))
  {
    std::cerr << "Wrong first arg\n";
    return 1;
  }

  std::ifstream in(argv[2]);
  if (!in.is_open())
  {
    std::cerr << "Cannot open input\n";
    return 2;
  }

  return 0;
}
