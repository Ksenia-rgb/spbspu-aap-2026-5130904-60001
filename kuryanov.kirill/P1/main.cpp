#include <iostream>

int main() {

   int n = 1;
   size_t num = 0;
   int prev = 0;
   size_t cng = 0;
   size_t div_rem = 0;
   while(true) {

      std::cin >> n;

      if (std::cin.fail()) {
      std::cout << "Число не распознано\n";
      return 1;
      }
      if (n==0) {
         break;
      }
      if (num == 0) {
         prev = n;
         num += 1;
         continue;
      }

      if ((prev < 0 && n > 0) || (prev > 0 && n < 0)) {
         cng += 1;
      }
      if (n % prev == 0) {
         div_rem += 1;

      }

      prev = n;
      num += 1;


      }
      std::cout << cng << "\n";

      if (num < 2 ) {
         return 2;
      }
      std::cout << div_rem << "\n";
      return 0;
}

