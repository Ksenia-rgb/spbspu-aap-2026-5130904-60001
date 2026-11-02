#include <iostream>
#include <limits>

int main()
{
  int fst_el = 1;
  int snd_el = std::numeric_limits< int >::min();
  size_t max_len = 0;
  int loc_min = std::numeric_limits< int >::max();
  size_t seq = 0;

  while (std::cin >> fst_el && fst_el != 0) {
    if (fst_el < loc_min && fst_el != 0) {
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
  if (fst_el == 0 && seq == 0) {
      std::cerr << "The sequence is too short\n";
      return 2;
    }
  std::cout << max_len << "\n";
  std::cout << loc_min << "\n";
}
