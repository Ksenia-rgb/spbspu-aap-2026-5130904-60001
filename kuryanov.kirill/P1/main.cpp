#include <iostream>

int main() {

   int n = 1;
   int num = 0;
   int prev = 0;
   int cng = 0;
   while(n != 0) {

      std::cin >> n;

      if (std::cin.fail()) {
      std::cout << "Число не распознано\n";
      return 1;
      }

      if (num == 0) {
         prev = n;
         num+=1;
         continue;
      }

      if ((prev < 0 && n > 0) || (prev > 0 && n < 0)) {
         cng+=1;
      }
      prev = n;
      num+=1;

      }
      std::cout << cng << "\n";
      return 0;
}

