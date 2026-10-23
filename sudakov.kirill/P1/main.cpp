#include <iostream>
#include <limits>

int main(){
  int fstEl = 1;
  int sndEl = std::numeric_limits< int >::min();
  int max_len = 0;
  int loc_min = std::numeric_limits< int >::max();
  int c = 0;

  while (fstEl!=0) {
    std::cin >> fstEl;
    if (fstEl < loc_min and fstEl != 0) {
      loc_min = fstEl;
    }
    if (fstEl >= sndEl) {
      ++c;
    }
    if (c > max_len) {
      max_len = c;
    }
    if (fstEl < sndEl) {
      c = 1;
    }
    sndEl = fstEl;
  }
  if (std::cin.fail()) {
      std::cerr << "Ошибка ввода\n";
      return 1;
    }
  std::cout << max_len << "\n";
  std::cout << loc_min << "\n";
}
