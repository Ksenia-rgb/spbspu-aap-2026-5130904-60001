#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cerr << "invalid number of argumments\n";
    return 1;
  }
  std::string num = argv[1];
  if (num != "1" && num != "2")
  {
    std::cerr << "invalid task number\n";
    return 1;
  }
  return 0;
}
