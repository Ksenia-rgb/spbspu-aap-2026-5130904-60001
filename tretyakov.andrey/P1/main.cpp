#include <iostream>

int main()
{
  int kat1 = 1;
  int kat2 = 0;
  int perexodnik = 0;
  int gidrapousa = 0;
  int pthtrp = 0;
  std::cin >> kat1;
  if (!std::cin)
  {
    std::cout << "Input error\n";
    return 1;
  }
  kat2 = kat1;
  while (kat1 != 0)
  {
    std::cin >> kat1;
    if (!std::cin)
    {
      std::cerr << "Input error\n";
      return 1;
    }
    if (kat1 * kat1 == gidrapousa && kat1 != 0)
    {
      pthtrp = pthtrp + 1;
    }
    gidrapousa = kat1 * kat1 + kat2 * kat2;
    kat2 = kat1;
  }
  std::cout << "PTH-TRP = " << pthtrp << "\n";
  return 0;
}
