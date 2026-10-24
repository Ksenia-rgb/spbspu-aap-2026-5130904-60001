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
  delete [] arr;
  return new_arr;
}

void outputArr(int * arr, size_t size, std::ofstream & output) {
  size_t p = 0, n = 0, m = 0;
  while (p < size) {
    n = arr[p++];
    m = arr[p++];
    output << n << " " << m;
    for (size_t i = 0; i < n*m; i++) {
      output << ' ' << arr[p++];
    }
    output << '\n';
  }
}

void lft_bot_cnt(int * arr, size_t size) {

}

void fll_inc_wav(int * arr, size_t size) {

}

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

    int matrix1[10000] = {};
    copy(p, arr, matrix1);
    lft_bot_cnt(arr, p);

    int matrix2[10000] = {};
    copy(p, arr, matrix2);
    fll_inc_wav(arr, p);

    outputArr(matrix1, p, output);
    output << '\n';
    outputArr(matrix2, p, output);
  }
  else if (argv[1][0] == '2' && argv[1][1] == '\0')
  {
    int * arr = nullptr;
    size_t n = 0, m = 0, p = 0;

    while (input >> n >> m) {  // shlyapa
      try {
        arr = extendArr(n, m, p, arr);
      } catch (std::bad_alloc &) {
        std::cerr << "Bad alloc" << '\n';
        delete [] arr;
        return 2;
      }

      arr[p++] = n;
      arr[p++] = m;

      for (int i = 0; i < n*m; i++) {
        if (!(input >> arr[p++])) {
          std::cerr << "Bad input" << '\n';
          delete [] arr;
          return 2;
        }
      }
    }

    if (!input.eof()) {
      std::cerr << "Bad input" << '\n';
      delete [] arr;
      return 2;
    }

    int * matrix1 = nullptr;

    try {
      matrix1 = new int[p];
    } catch (const std::bad_alloc &) {
      std::cerr << "Bad alloc" << '\n';
      delete [] arr;
      return 2;
    }

    copy(p, arr, matrix1);
    lft_bot_cnt(arr, p);

    int * matrix2 = nullptr;

    try {
      matrix2 = new int[p];
    } catch (const std::bad_alloc &) {
      std::cerr << "Bad alloc" << '\n';
      delete [] matrix1;
      delete [] arr;
      return 2;
    }

    fll_inc_wav(arr, p);

    outputArr(matrix1, p, output);
    output << '\n';
    outputArr(matrix2, p, output);

    delete [] arr;
    delete [] matrix1;
    delete [] matrix2;
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
