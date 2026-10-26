#include <iostream>

int main(int argc, char** argv)
{
  const int argumentsCount = 4;
  if (argc < argumentsCount) {
    std::cerr << "Not enough arguments\n";
    return 1;
  }
  if (argc > argumentsCount) {
    std::cerr << "Too many arguments\n";
    return 1;
  }

  const char* num = argv[1];
  const bool isFixed = (num[0] == '1' && num[1] == '\0');
  const bool isDynamic = (num[0] == '2' && num[1] == '\0');
  if (!isFixed && !isDynamic) {
    std::cerr << "First parameter is wrong\n";
    return 1;
  }
  return 0;
}
