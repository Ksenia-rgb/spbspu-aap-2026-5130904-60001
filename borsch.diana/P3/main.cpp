#include <fstream>
#include <iostream>

int main(int argc, char* argv[])
{
  const int exitBadArguments = 1;
  const int exitBadData = 2;
  const int argCount = 4;
  const int modeArg = 1;
  const int inputArg = 2;
  const char fixedMode = '1';
  const char dynamicMode = '2';

  if (argc != argCount) {
    std::cerr << "Usage: ./lab num input output\n";
    return exitBadArguments;
  }

  const char* mode = argv[modeArg];
  const bool isFixed = (mode[0] == fixedMode) && (mode[1] == '\0');
  const bool isDynamic = (mode[0] == dynamicMode) && (mode[1] == '\0');
  if (!isFixed && !isDynamic) {
    std::cerr << "First parameter must be 1 or 2\n";
    return exitBadArguments;
  }

  std::ifstream input(argv[inputArg]);
  if (!input) {
    std::cerr << "Cannot open input file\n";
    return exitBadData;
  }

  int rows = 0;
  int cols = 0;
  if (!(input >> rows >> cols) || (rows < 0) || (cols < 0)) {
    std::cerr << "Invalid matrix size\n";
    return exitBadData;
  }
  return 0;
}
