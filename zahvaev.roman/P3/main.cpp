#include <iostream>
#include <new>
#include <algorithm>

int** matrix_change(int** matrix, size_t rows_func, size_t cols_func) {
    int** new_matrix = new int*[rows_func];
    try {
        for (size_t i = 0; i < rows_func; ++i) {
            new_matrix[i] = new int[cols_func];
        }
    }
    catch (const std::bad_alloc&) {
        for (size_t i = 0; i < rows_func; ++i) {
            delete[] new_matrix[i];
        }
        delete[] new_matrix;
        throw;
    }
    for (size_t i = 0; i < rows_func; ++i) {
        for (size_t j = 0; j < cols_func; ++j) {
            size_t d = std::min({
                i, j, rows_func - 1 - i, cols_func - 1 - j
            });
            new_matrix[i][j] = matrix[i][j] + (d + 1);
        }
    }
    return new_matrix;
}
