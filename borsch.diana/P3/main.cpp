#include <iostream>

int main(int argc, char*[])
{
  const int exitBadArguments = 1;
  const int argCount = 4;

  if (argc != argCount) {
    std::cerr << "Usage: ./lab num input output\n";
    return exitBadArguments;
  }
  return 0;
}
