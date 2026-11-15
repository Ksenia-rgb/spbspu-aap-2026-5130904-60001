#include <iostream>
#include <fstream>
#include <cstring>
#include <cstddef>

namespace efremenko {
    int read_matrix(std::ifstream& in, int* matrix, size_t& rows, size_t& cols) {
        long long r, c;
        if (!(in >> r >> c)) return 1;
        if (r < 0 || c < 0) return 2;
        
        rows = static_cast<size_t>(r);
        cols = static_cast<size_t>(c);

        for (size_t i = 0; i < rows * cols; ++i) {
            if (!(in >> matrix[i])) return 3;
        }

        int dummy;
        if (in >> dummy) return 4;

        return 0;
    }
// NUM-COL-LSR
    size_t calculate_num_col_lsr(const int* matrix, size_t rows, size_t cols) {
        size_t max_series = 0;
        size_t best_col = 0;
        if (rows == 0 || cols == 0) return 0;

        for (size_t j = 0; j < cols; ++j) {
            size_t current_series = 1;
            size_t col_max_series = 1;
            for (size_t i = 1; i < rows; ++i) {
                if (matrix[i * cols + j] == matrix[(i - 1) * cols + j]) {
                    current_series++;
                    if (current_series > col_max_series) {
                        col_max_series = current_series;
                    }
                } else {
                    current_series = 1;
                }
            }
            if (col_max_series > max_series) {
                max_series = col_max_series;
                best_col = j + 1;
            }
        }
        return best_col;
    }
// CNT-LOC-MIN
    size_t calculate_cnt_loc_min(const int* matrix, size_t rows, size_t cols) {
        size_t count = 0;
        if (rows < 3 || cols < 3) return 0;

        for (size_t i = 1; i < rows - 1; ++i) {
            for (size_t j = 1; j < cols - 1; ++j) {
                bool is_min = true;
                for (int di = -1; di <= 1; ++di) {
                    for (int dj = -1; dj <= 1; ++dj) {
                        if (di == 0 && dj == 0) continue;
                        
                        size_t ni = i + di;
                        size_t nj = j + dj;
                        
                        if (matrix[i * cols + j] >= matrix[ni * cols + nj]) {
                            is_min = false;
                            break;
                        }
                    }
                    if (!is_min) break;
                }
                if (is_min) count++;
            }
        }
        return count;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Error: Invalid arguments count\n";
        return 1;
    }

    if (std::strcmp(argv[1], "1") != 0 && std::strcmp(argv[1], "2") != 0) {
        std::cerr << "Error: First parameter must be 1 or 2\n";
        return 1;
    }

    int mode = argv[1][0] - '0';

    std::ifstream in(argv[2]);
    if (!in.is_open()) {
        std::cerr << "Error: Cannot open input file\n";
        return 2;
    }

    size_t rows = 0, cols = 0;
    int* matrix = nullptr;
    int stack_data[10000];

    long long temp_r, temp_c;
    if (!(in >> temp_r >> temp_c) || temp_r < 0 || temp_c < 0) {
        std::cerr << "Error: Invalid matrix dimensions\n";
        return 2;
    }
    
    in.clear();
    in.seekg(0, std::ios::beg);

    if (mode == 1) {
        if (temp_r * temp_c > 10000) {
            std::cerr << "Error: Matrix too large for stack\n";
            return 2;
        }
        matrix = stack_data;
    } else {
        matrix = new int[temp_r * temp_c];
    }

    int read_status = efremenko::read_matrix(in, matrix, rows, cols);
    if (read_status != 0) {
        std::cerr << "Error: Invalid matrix data in file\n";
        if (mode == 2) delete[] matrix;
        return 2;
    }

    size_t res1 = efremenko::calculate_num_col_lsr(matrix, rows, cols);
    size_t res2 = efremenko::calculate_cnt_loc_min(matrix, rows, cols);

    std::ofstream out(argv[3]);
    if (!out.is_open()) {
        std::cerr << "Error: Cannot open output file\n";
        if (mode == 2) delete[] matrix;
        return 2;
    }

    out << res1 << "\n";
    out << res2 << "\n";

    if (mode == 2) {
        delete[] matrix;
    }

    return 0;
}
