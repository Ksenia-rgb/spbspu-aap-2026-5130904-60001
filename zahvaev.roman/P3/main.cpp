#include <algorithm>
#include <climits>
#include <cstddef>
#include <cstring>
#include <fstream>
#include <iostream>
#include <new>

void freeMatrix(int** m, size_t rows) {
    for (size_t i = 0; i < rows; ++i) {
        delete[] m[i];
    }
    delete[] m;
}
int** matrix_change(int** matrix, size_t rows_func, size_t cols_func) {
    int** new_matrix = new int*rows_func;
    try {
        for (size_t i = 0; i < rows_func; ++i) {
            new_matrix[i] = new int[cols_func];
        }
        for (size_t i = 0; i < rows_func; ++i) {
            for (size_t j = 0; j < cols_func; ++j) {
                size_t d = std::min({i, j, rows_func - 1 - i, cols_func - 1 - j});
                long long value = static_cast<long long>(matrix[i][j]) + d + 1;
                if (value > INT_MAX) {
                    throw "Error: integer overflow";
                }
                new_matrix[i][j] = static_cast<int>(value);
            }
        }
    }
    catch (...) {
        freeMatrix(new_matrix, rows_func);
        throw;
    }
    return new_matrix;
}
long long maxDiagonalSum(int** a, size_t rows, size_t cols) {
    if (rows == 0 || cols == 0) {
        return 0;
    }
    size_t secondary = cols - 1;
    long long maxSum = 0;
    bool found = false;
    for (size_t diagonal = 0; diagonal < rows + cols - 1; ++diagonal) {
        if (diagonal == secondary) {
            continue;
        }
        long long sum = 0;
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                if (i + j == diagonal) {
                    sum = sum + a[i][j];
                }
            }
        }
        if (found == false || sum > maxSum) {
            maxSum = sum;
            found = true;
        }
    }
    return maxSum;
}
int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Error: wrong number of arguments\n";
        return 1;
    }
    if (std::strcmp(argv[1], "1") != 0 && std::strcmp(argv[1], "2") != 0) {
        std::cerr << "Error: first parameter must be 1 or 2\n";
        return 1;
    }
std::ifstream in(argv[2]);
std::ofstream out(argv[3]);
if (!in || !out) {
    std::cerr << "Error: cannot open file\n";
    return 2;
}

long long r = 0;
long long c = 0;
if (!(in >> r >> c) || r < 0 || c < 0) {
    std::cerr << "Error: invalid matrix size\n";
    return 2;
}
return 0;
}
