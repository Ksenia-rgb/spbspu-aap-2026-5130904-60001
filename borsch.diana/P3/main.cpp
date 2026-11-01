#include <iostream>

int main(int argc, char* argv[])
{
  const int exitBadArguments = 1;
  const int argCount = 4;
  const int modeArg = 1;
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
  return 0;
}
