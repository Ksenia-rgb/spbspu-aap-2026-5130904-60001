#include <iostream>

int incSeq(int a, int a0)
{
  if (a > a0)
  {
    return 1;
  }

  return 0;
}

int cntMax(int a, int am, int res_cm)
{
  if (am < a && a != 0)
  {
    return 1;
  }

  if (am == a)
  {
    return ++res_cm;
  }

  return res_cm;
}

int main()
{
  int a = 0;
  int a0 = 0;
  int am = 0;
  int res_ic = 0;
  int res_cm = 1;

  std::cin >> a;

  if (!std::cin)
  {
    std::cerr << "Wrong sequence\n";
    return 1;
  }

  if (a == 0)
  {
    std::cerr << "Not enough data\n";
    return 2;
  }

  am = a;

  for (size_t i = 1; i > 0; ++i)
  {
    a0 = a;

    std::cin >> a;

    if (!std::cin)
    {
      std::cerr << "Wrong sequence\n";
      return 1;
    }

    if (a == 0)
    {
      a0 = 0;
      i = -1;
    }

    res_ic += incSeq(a, a0);
    res_cm = cntMax(a, am, res_cm);

    am = a;
  }
  std::cout << res_ic << "\n";
  std::cout << res_cm << "\n";
}
