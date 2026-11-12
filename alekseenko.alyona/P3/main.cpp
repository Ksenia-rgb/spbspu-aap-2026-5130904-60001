#include <iostream>
#include <fstream>
#include <limits>
#include <climits>
#include <cstddef>
#include <new>

namespace alekseenko {

int num_col_lsr(const int* matrix, size_t n, size_t m)
{
    if (n == 0 || m == 0)
        return 0;

    size_t max_length = 1;
    int answer = 1;

    for (size_t j = 0; j < m; ++j) {
        size_t current_length = 1;

        for (size_t i = 1; i < n; ++i) {
            if (matrix[i * m + j] == matrix[(i - 1) * m + j])
                ++current_length;
            else
                current_length = 1;

            if (current_length > max_length) {
                max_length = current_length;
                answer = static_cast<int>(j + 1);
            }
        }
    }

    return answer;
}

long long min_sum_mdg(const int* matrix, size_t n, size_t m)
{
    if (n == 0 || m == 0)
        return 0;

    long long min_sum = LLONG_MAX;

    for (size_t start_col = 0; start_col < m; ++start_col) {
        size_t i = 0;
        size_t j = start_col;
        long long sum = 0;

        while (i < n) {
            sum += matrix[i * m + j];
            ++i;

            if (j == 0)
                break;

            --j;
        }

        if (sum < min_sum)
            min_sum = sum;
    }

    for (size_t start_row = 1; start_row < n; ++start_row) {
        size_t i = start_row;
        size_t j = m - 1;
        long long sum = 0;

        while (i < n) {
            sum += matrix[i * m + j];
            ++i;

            if (j == 0)
                break;

            --j;
        }

        if (sum < min_sum)
            min_sum = sum;
    }

    return min_sum;
}

bool valid_dimensions(long long rows, long long cols)
{
    if (rows < 0 || cols < 0)
        return false;

    if ((rows == 0) != (cols == 0))
        return false;

    if (rows > 0 &&
        static_cast<unsigned long long>(rows) >
            static_cast<unsigned long long>(std::numeric_limits<size_t>::max()) /
            static_cast<unsigned long long>(cols))
        return false;

    return true;
}

bool read_matrix(std::ifstream& input, int* matrix, size_t n, size_t m)
{
    for (size_t i = 0; i < n * m; ++i) {
        long long value;

        if (!(input >> value))
            return false;

        if (value < INT_MIN || value > INT_MAX)
            return false;

        matrix[i] = static_cast<int>(value);
    }

    char extra;

    if (input >> extra)
        return false;

    return true;
}

} // namespace alekseenko

int main(int argc, char* argv[])
{
    if (argc != 4) {
        std::cerr << "Error: expected 3 arguments\n";
        return 1;
    }

    int mode = 0;

    if (argv[1][0] == '1' && argv[1][1] == '\0') {
        mode = 1;
    } else if (argv[1][0] == '2' && argv[1][1] == '\0') {
        mode = 2;
    } else {
        std::cerr << "Error: mode must be 1 or 2\n";
        return 1;
    }

    std::ifstream input(argv[2]);

    if (!input) {
        std::cerr << "Error: cannot open input file\n";
        return 2;
    }

    long long rows_input, cols_input;

    if (!(input >> rows_input >> cols_input) ||
        !alekseenko::valid_dimensions(rows_input, cols_input)) {
        std::cerr << "Error: invalid matrix dimensions\n";
        return 2;
    }

    size_t n = static_cast<size_t>(rows_input);
    size_t m = static_cast<size_t>(cols_input);

    std::ofstream output(argv[3]);

    if (!output) {
        std::cerr << "Error: cannot open output file\n";
        return 2;
    }

    if (n == 0 && m == 0) {
        char extra;

        if (input >> extra) {
            std::cerr << "Error: extra data\n";
            return 2;
        }

        output << "0 0\n";
        return 0;
    }

    if (n > std::numeric_limits<size_t>::max() / m) {
        std::cerr << "Error: matrix is too large\n";
        return 2;
    }

    size_t count = n * m;

    if (mode == 1) {
        const size_t MAX_ELEMENTS = 10000;

        if (count > MAX_ELEMENTS) {
            std::cerr << "Error: matrix is too large for mode 1\n";
            return 2;
        }

        int matrix[MAX_ELEMENTS];

        if (!alekseenko::read_matrix(input, matrix, n, m)) {
            std::cerr << "Error: invalid matrix data\n";
            return 2;
        }

        output << alekseenko::num_col_lsr(matrix, n, m)
               << ' '
               << alekseenko::min_sum_mdg(matrix, n, m)
               << '\n';
    } else {
        int* matrix = nullptr;

        try {
            matrix = new int[count];
        } catch (const std::bad_alloc&) {
            std::cerr << "Error: memory allocation failed\n";
            return 2;
        }

        if (!alekseenko::read_matrix(input, matrix, n, m)) {
            delete[] matrix;
            std::cerr << "Error: invalid matrix data\n";
            return 2;
        }

        output << alekseenko::num_col_lsr(matrix, n, m)
               << ' '
               << alekseenko::min_sum_mdg(matrix, n, m)
               << '\n';

        delete[] matrix;
    }

    return 0;
}
