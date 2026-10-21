#include <fstream>
#include <iostream>

void copy(size_t size, int * old_arr, int * new_arr) {
  for (size_t i = 0; i < size; i++) {
    new_arr[i] = old_arr[i];
  }
}

int * extendArr(size_t n, size_t m, size_t size, int * arr) {
  int * new_arr = new int[size + n*m+2];
  copy(size, arr, new_arr);
  return new_arr;
};

void outputArr(int * arr, size_t size, std::ofstream & output) {
  size_t p = 0;
  output << arr[p++];
};

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

  if (argv[1][0] == '1' && argv[1][1] == '\0')
  {
    int arr[10000] = {0};
    size_t a = 0, p = 0;

    while (input >> a) {
      arr[p++] = a;
    }

    if (!input.eof()) {
      std::cerr << "Bad input" << '\n';
      return 2;
    }

    // int matrix1 = lft_bot_cnt();
    // int matrix2 = fll_inc_wav();
    // outputMatrix();
  }
  else if (argv[1][0] == '2' && argv[1][1] == '\0')
  {
    int * arr = nullptr;
    size_t n = 0, m = 0, p = 0;

    while (input >> n >> m) {
      try {
        arr = extendArr(n, m, p, arr);
      } catch (std::bad_alloc &) {
        std::cerr << "Bad alloc" << '\n';
        // rmArr();
        return 2;
      }

      arr[p++] = n;
      arr[p++] = m;
      for (int i = 0; i < n*m; i++) {
        int x = 0;
        input >> x;
        arr[p++] = x;
      }
    }

    if (!input.eof()) {
      std::cerr << "Bad input" << '\n';
      // rmArr();
      return 2;
    }

    // int matrix1 = lft_bot_cnt();
    // int matrix2 = fll_inc_wav();

    outputArr(arr, p, output);
  }
  else {
    if (argv[1][0] >= '0' && argv[1][0] <= '9') {
      std::cerr << "First parameter is out of range" << '\n';
    } else {
      std::cerr << "First parameter is not a number" << '\n';
    }
    return 1;
  }

  return 0;
}
