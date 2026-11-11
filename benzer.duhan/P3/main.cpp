

#include <iostream>
#include <fstream>
#include <new>
#include <limits>

namespace benzer {

    int countLocalMax(const int* matrix, int rows, int cols) {
        int count = 0;

        for (int i = 1; i < rows - 1; ++i) {
            for (int j = 1; j < cols - 1; ++j) {
                int value = matrix[i * cols + j];
                bool isMax = true;

                for (int di = -1; di <= 1; ++di) {
                    for (int dj = -1; dj <= 1; ++dj) {
                        if (di == 0 && dj == 0) {
                            continue;
                        }

                        int neighbor =
                            matrix[(i + di) * cols + (j + dj)];

                        if (value <= neighbor) {
                            isMax = false;
                        }
                    }
                }

                if (isMax) {
                    ++count;
                }
            }
        }

        return count;
    }

    int countLocalMin(const int* matrix, int rows, int cols) {
        int count = 0;

        for (int i = 1; i < rows - 1; ++i) {
            for (int j = 1; j < cols - 1; ++j) {
                int value = matrix[i * cols + j];
                bool isMin = true;

                for (int di = -1; di <= 1; ++di) {
                    for (int dj = -1; dj <= 1; ++dj) {
                        if (di == 0 && dj == 0) {
                            continue;
                        }

                        int neighbor =
                            matrix[(i + di) * cols + (j + dj)];

                        if (value >= neighbor) {
                            isMin = false;
                        }
                    }
                }

                if (isMin) {
                    ++count;
                }
            }
        }

        return count;
    }

}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Error: expected 3 arguments\n";
        return 1;
    }

    int mode = 0;

    try {
        std::size_t pos = 0;
        mode = std::stoi(argv[1], &pos);

        if (pos != std::string(argv[1]).size() ||
            (mode != 1 && mode != 2)) {
            std::cerr << "Error: invalid mode\n";
            return 1;
        }
    } catch (...) {
        std::cerr << "Error: invalid mode\n";
        return 1;
    }

    std::ifstream input(argv[2]);

    if (!input.is_open()) {
        std::cerr << "Error: cannot open input file\n";
        return 2;
    }

    long long r, c;

    if (!(input >> r >> c) || r < 0 || c < 0 ||
        ((r == 0) != (c == 0)) ||
        r > std::numeric_limits<int>::max() ||
        c > std::numeric_limits<int>::max()) {
        std::cerr << "Error: invalid matrix dimensions\n";
        return 2;
    }

    if (r != 0 && c > std::numeric_limits<int>::max() / r) {
        std::cerr << "Error: matrix is too large\n";
        return 2;
    }

    int rows = static_cast<int>(r);
    int cols = static_cast<int>(c);
    int size = rows * cols;

    if (mode == 1 && size > 10000) {
        std::cerr << "Error: matrix exceeds fixed array limit\n";
        return 2;
    }

    int fixedMatrix[10000];
    int* matrix = nullptr;

    if (size > 0) {
        if (mode == 2) {
            matrix = new (std::nothrow) int[size];

            if (matrix == nullptr) {
                std::cerr << "Error: memory allocation failed\n";
                return 2;
            }
        } else {
            matrix = fixedMatrix;
        }
    }

    for (int i = 0; i < size; ++i) {
        long long value;

        if (!(input >> value) ||
            value < std::numeric_limits<int>::min() ||
            value > std::numeric_limits<int>::max()) {
            std::cerr << "Error: invalid matrix data\n";

            if (mode == 2) {
                delete[] matrix;
            }

            return 2;
        }

        matrix[i] = static_cast<int>(value);
    }

    std::string extra;

    if (input >> extra) {
        std::cerr << "Error: extra data in input file\n";

        if (mode == 2) {
            delete[] matrix;
        }

        return 2;
    }

    input.close();

    std::ofstream output(argv[3]);

    if (!output.is_open()) {
        std::cerr << "Error: cannot open output file\n";

        if (mode == 2) {
            delete[] matrix;
        }

        return 2;
    }

    int maxCount = 0;
    int minCount = 0;

    if (size > 0) {
        maxCount = benzer::countLocalMax(matrix, rows, cols);
        minCount = benzer::countLocalMin(matrix, rows, cols);
    }

    output << maxCount << '\n';
    output << minCount << '\n';

    output.close();

    if (mode == 2) {
        delete[] matrix;
    }

    return 0;
}
