#include <iostream>
#include <new>
#include <algorithm>

void matrix_change(int** matrix, size_t rows_func, size_t cols_func) {
        for (size_t i = 0; i < rows_func; ++i) {
            for (size_t j = 0; j < cols_func; ++j) {
                size_t d = std::min({i, j, rows_func - 1 - i, cols_func - 1 - j});
                matrix[i][j] += (d + 1);
            }
        }
    }

int main() {
    size_t rows, cols;
    std::cout << "Введите кол-во строк и столбцов через пробел: ";
    if (!(std::cin >> rows >> cols)) {
        std::cerr << "хуету ввёл, исправляйся!";
        return 2;
    }
    int ** matrix = nullptr;
    try {
        matrix = new int*[rows];
        for (size_t i = 0; i < rows; ++i) {
            matrix[i] = new int[cols];
        }
    }
    catch (const std::bad_alloc &) {
        return 1;
    }
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            std::cin >> matrix[i][j];
        }
    }
    
    matrix_change(matrix, rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << '\n';
    }
    for (size_t i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
    matrix = nullptr;
    return 0;
}
