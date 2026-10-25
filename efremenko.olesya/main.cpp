#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

namespace efremenko
{
    void process_matrix(int mode, const char* input_file, const char* output_file)
    {
        std::ifstream in(input_file);
        if (!in.is_open())
        {
            std::cerr << "Error: Cannot open input file\n";
            std::exit(2);
        }

        int rows = 0, cols = 0;
        if (!(in >> rows >> cols))
        {
            std::cerr << "Error: Cannot read matrix dimensions\n";
            std::exit(2);
        }

        if (rows < 0 || cols < 0)
        {
            std::cerr << "Error: Invalid matrix dimensions\n";
            std::exit(2);
        }

        int** matrix = nullptr;
        int stack_data[10000];
        int* stack_row_ptrs[10000];

        if (mode == 1)
        {
            if (rows * cols > 10000)
            {
                std::cerr << "Error: Matrix too large for stack allocation\n";
                std::exit(2);
            }
            for (int i = 0; i < rows; ++i)
            {
                stack_row_ptrs[i] = &stack_data[i * cols];
            }
            matrix = stack_row_ptrs;
         }
         else
         {
            matrix = new int*[rows];
            for (int i = 0; i < rows; ++i)
            {
                matrix[i] = new int[cols];
            }
        }

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (!(in >> matrix[i][j]))
                {
                    std::cerr << "Error: Cannot read matrix elements\n";
                    if (mode == 2)
                    {
                        for (int k = 0; k < i; ++k) delete[] matrix[k];
                        delete[] matrix;
                    }
                    std::exit(2);
                }
            }
        }

        int dummy;
        if (in >> dummy)
        {
            std::cerr << "Error: Extra data in file\n";
            if (mode == 2)
            {
                for (int k = 0; k < rows; ++k) delete[] matrix[k];
                delete[] matrix;
            }
            std::exit(2);
        }

        int max_series = 0;
        int best_col = 0;
        if (rows > 0 && cols > 0)
        {
            for (int j = 0; j < cols; ++j)
            {
                int current_series = 1;
                int col_max_series = 1;
                for (int i = 1; i < rows; ++i)
                {
                    if (matrix[i][j] == matrix[i-1][j])
                    {
                        current_series++;
                        if (current_series > col_max_series)
                        {
                            col_max_series = current_series;
                        }
                    }
                    else
                    {
                        current_series = 1;
                    }
                }
                if (col_max_series > max_series)
                {
                    max_series = col_max_series;
                    best_col = j + 1;
                }
            }
        }

        int loc_min_count = 0;
        for (int i = 1; i < rows - 1; ++i)
        {
            for (int j = 1; j < cols - 1; ++j)
            {
                bool is_min = true;
                for (int di = -1; di <= 1; ++di)
                {
                    for (int dj = -1; dj <= 1; ++dj)
                    {
                        if (di == 0 && dj == 0)
                        {
                            continue;
                        }
                        if (matrix[i][j] >= matrix[i+di][j+dj])
                        {
                            is_min = false;
                            break;
                        }
                    }
                    if (!is_min)
                    {
                        break;
                    }
                }
                if (is_min)
                {
                    loc_min_count++;
                }
            }
        }

        std::ofstream out(output_file);
        if (!out.is_open()) {
            std::cerr << "Error: Cannot open output file\n";
            if (mode == 2)
            {
                for (int k = 0; k < rows; ++k)
                {
                    delete[] matrix[k];
                    delete[] matrix;
                }
            }
            std::exit(1);
        }

        out << best_col << "\n";
        out << loc_min_count << "\n";

        if (mode == 2)
        {
            for (int k = 0; k < rows; ++k)
            {
                delete[] matrix[k];
                delete[] matrix;
            }
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        std::cerr << "Usage: ./lab <1|2> <input> <output>\n";
        return 1;
    }

    if (std::strcmp(argv[1], "1") != 0 && std::strcmp(argv[1], "2") != 0)
    {
        std::cerr << "Error: First parameter must be 1 or 2\n";
        return 1;
    }

    int mode = argv[1][0] - '0';

    efremenko::process_matrix(mode, argv[2], argv[3]);

    return 0;
}
