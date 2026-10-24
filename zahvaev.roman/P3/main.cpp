#include <iostream>
#include <new>
#include <cstddef>

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
    if (found == false) {
        return 0;
    }
    return maxSum;
}
