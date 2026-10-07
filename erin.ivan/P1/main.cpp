#include <iostream>

namespace erin
{
  int task()
  {
   int a = 0;
   int b = 0;
   int c = 0;
   int countLocMax = 0;
   int pred = 0;
   int countSgnChg = 0;
   int len = 0;
   int now = 0;

   while (std::cin >> now && now != 0)
   {
    a = b;
    b = c;
    c = now;
    len++;

    if (len >= 3)
    {
     if (b > a && b > c)
     {
       countLocMax++;
     }
    }

    if ((pred > 0 && now < 0) || (pred < 0 && now > 0))
    {
      countSgnChg++;
    }
    pred = now;
   }

   if (!std::cin)
   {
    std::cerr << "Invalid input\n";
    return 1;
   }

   if (len == 0)
   {
    std::cerr << "Empty sequence\n";
    return 2;
   }

   std::cout << countLocMax << "\n";
   std::cout << countSgnChg << "\n";
   return 0;
  }
}

int main()
{
  return erin::task();
}
