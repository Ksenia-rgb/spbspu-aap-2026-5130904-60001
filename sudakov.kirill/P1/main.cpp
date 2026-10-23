#include <iostream>
#include <limits>

int main()
{
  int fst_el = 1;
  int snd_el = std::numeric_limits< int >::min();
  int max_len = 0;
  int loc_min = std::numeric_limits< int >::max();
  int seq = 0;

  while (fst_el != 0) {
    std::cin >> fst_el;
    if (fst_el == 0 and seq == 0) {
      std::cerr << "Последовательность слишком короткая\n";
      return 2;
    }

    if (fst_el < loc_min and fst_el != 0) {
      loc_min = fst_el;
    }
    if (fst_el >= snd_el) {
      ++seq;
    }
    if (seq > max_len) {
      max_len = seq;
    }
    if (fst_el < snd_el) {
      seq = 1;
    }
    snd_el = fst_el;
  }
  if (std::cin.fail()) {
    std::cerr << "Ошибка ввода\n";
    return 1;
  }
  std::cout << max_len << "\n";
  std::cout << loc_min << "\n";
}
