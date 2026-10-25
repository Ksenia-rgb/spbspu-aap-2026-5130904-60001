#include <cstring>
#include <fstream>
#include <iostream>

int main(int argc, char * argv[])
{
  if (argc != 4)
  {
    std::cerr << "Invalid arguments\n";
    return 1;
  }

  if (std::strcmp(argv[1], "1") != 0 && std::strcmp(argv[1], "2") != 0)
  {
    std::cerr << "Invalid mode\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  if (!input)
  {
    std::cerr << "Cannot open input file\n";
    return 2;
  }

  int input_rows = 0;
  int input_cols = 0;
  if(!(input >> input_rows >> input_cols) || input_rows < 0 || input_cols < 0)
  {
    std::cerr << "Invalid matrix\n";
    return 2;
  }

  return 0;
}
