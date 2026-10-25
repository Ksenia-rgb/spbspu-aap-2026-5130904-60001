#include <iostream>
#include <fstream>
#include <cstdlib>

void printMatrix(int** m, size_t rows, size_t cols, std::ostream& out) {
  out << rows << ' ' << cols;
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      out << ' ' << m[i][j];
    }
  }
  out << '\n';
}

int main(int argc, char* argv[]) {
  const int argsCount = 4;
  const size_t MAX_ELEMENTS = 10000;

  if (argc < argsCount) {
    std::cerr << "Not enough arguments\n";
    return 1;
  }
  if (argc > argsCount) {
    std::cerr << "Too many arguments\n";
    return 1;
  }
  int num = std::atoi(argv[1]);
  switch (num) {
    case 1:
    {
      std::ifstream input(argv[2]);
      if (!input.is_open()) {
          std::cerr << "Cannot open input file\n";
          return 2;
      }
      size_t rows = 0;
      size_t cols = 0;
      if (!(input >> rows >> cols)) {
        std::cerr << "Unexpected input\n";
        return 2;
      }

      if (cols != 0 && rows > MAX_ELEMENTS / cols) {
        std::cerr << "Matrix is too large\n";
        return 2;
      }
      int arr[MAX_ELEMENTS] = {};
      for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
          if(!(input >> arr[i * cols + j])) {
            std::cerr << "Unexpected input\n";
            return 2;
          }
        }
      }
      std::ofstream out(argv[3]);
      if (!out.is_open()) {
        std::cerr << "Cannot open output file\n";
        return 2;
      }
      break; 
    }
    
    case 2:
    {
      std::ifstream input(argv[2]);
      if (!input.is_open()) {
          std::cerr << "Cannot open input file\n";
          return 2;
      }
      size_t rows = 0;
      size_t cols = 0;
      if (!(input >> rows >> cols)) {
        std::cerr << "Unexpected input\n";
        return 2;
      }
      int** arr = static_cast<int**>(std::malloc(rows * sizeof(*arr)));
      if (arr == nullptr && rows > 0) {
        std::cerr << "Memory allocation failed\n";
        return 2;
      }
      for (size_t i = 0; i < rows; ++i) {
        arr[i] = static_cast<int*>(std::malloc(cols * sizeof(*arr[i])));
        if (arr[i] == nullptr && cols > 0) {
          for (size_t k = 0; k < i; ++k) {
            std::free(arr[k]);
          }
          std::free(arr);
          std::cerr << "Memory allocation failed\n";
          return 2;
        }
      }

      for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
          if (!(input >> arr[i][j])) {
              std::cerr << "Unexpected input\n";
              for (size_t k = 0; k < rows; ++k) {
                  std::free(arr[k]);
              }
              std::free(arr);
              return 2;
          }
        }
      }
      std::ofstream out(argv[3]);
      if (!out.is_open()) {
        std::cerr << "Cannot open output file\n";
        for (size_t i = 0; i < rows; ++i) {
          std::free(arr[i]);
        }
        std::free(arr);
        return 2;
      }
      for (size_t i = 0; i < rows; ++i) {
        std::free(arr[i]);
      }
      std::free(arr);

      break;

    }
    default:
    {
      std::cerr << "First parameter is not a number or out of range\n";
      return 1;
    }
  }
  return 0;
}
