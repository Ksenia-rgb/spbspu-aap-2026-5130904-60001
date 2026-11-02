#include <fstream>
#include <iostream>

namespace manokhin{
  void copy(size_t size, int * old_arr, int * new_arr)
  {
    for (const int * i = old_arr; i != size + old_arr; i++) {
      *new_arr = *i;
      new_arr++;
    }
  }

  int * extendArr(size_t n, size_t m, size_t size, int * arr)
  {
    int * new_arr = new int[size + n * m+ 2];
    copy(size, arr, new_arr);
    delete [] arr;
    return new_arr;
  }

 std::ofstream & outputArr(std::ofstream & output, int * arr, size_t size)
  {
    size_t p = 0;
    while (p < size) {
      output << ' ' << arr[p++];
    }
    return output;
  }

  void lft_bot_cnt(int * arr, const long long n, const long long m, const size_t orig_m, size_t p, size_t k)
  {
    if (n <= 0 || m <= 0) {
      return;
    }
    for (long long i = 0; i < m; i++) {
      arr[p] += k;
      k++;
      p++;
    }
    p--;
    for (long long i = 0; i < n - 1; i++) {
      p -= orig_m;
      arr[p] += k;
      k++;
    }
    for (long long i = 0; i < m - 1; i++) {
      p--;
      arr[p] += k;
      k++;
    }
    for (long long i = 0; i < n - 2; i++) {
      p += orig_m;
      arr[p] += k;
      k++;
    }
    lft_bot_cnt(arr, n - 2, m - 2, orig_m, ++p, k);
  }

  void fll_inc_wav(int * arr, const long long n, const long long m, const size_t orig_m, size_t p, size_t k)
  {
    if (n <= 0 || m <= 0) {
      return;
    }
    for (long long i = 0; i < m; i++) {
      arr[p] += k;
      p++;
    }
    p--;
    for (long long i = 0; i < n - 1; i++) {
      p += orig_m;
      arr[p] += k;
    }
    for (long long i = 0; i < m - 1; i++) {
      p--;
      arr[p] += k;
    }
    for (long long i = 0; i < n - 2; i++) {
      p -= orig_m;
      arr[p] += k;
    }
    fll_inc_wav(arr, n - 2, m - 2, orig_m, ++p, ++k);
  }
}

using namespace manokhin;

int main(int argc, char ** argv)
{
  if (argc < 4) {
    std::cerr << "Not enough arguments" << '\n';
    return 1;
  }
  if (argc > 4) {
    std::cerr << "Too many arguments" << '\n';
    return 1;
  }

  std::ifstream input(argv[2]);
  std::ofstream output(argv[3]);

  if (!input.is_open()) {
    std::cerr << "Cannot open input file" << '\n';
    return 2;
  }
  if (!output.is_open()) {
    std::cerr << "Cannot open output file" << '\n';
    return 2;
  }

  char par = argv[1][0];

  if ((par == '1' || par == '2') && argv[1][1] == '\0') {
    if (par == '1') {
      int arr[10000] = {0};
    } else {
      int * arr = nullptr;
    }
  }
  return 0;
}
