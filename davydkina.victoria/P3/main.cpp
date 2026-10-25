const int max_size = 10000;

int same(const char *a, const char *b)
{
    int i = 0;

    while (a[i] != '\0' && b[i] != '\0')
    {
        if (a[i] != b[i])
        {
            return 0;
        }

        i++;
    }

    return a[i] == b[i];
}

int check_column(const int *matrix, int rows, int cols, int col)
{
    for (int row = 1; row < rows; row++)
    {
        if (matrix[row * cols + col] ==
            matrix[(row - 1) * cols + col])
        {
            return 0;
        }
    }

    return 1;
}

int count_columns(const int *matrix, int rows, int cols)
{
    int result = 0;

    for (int col = 0; col < cols; col++)
    {
        result += check_column(matrix, rows, cols, col);
    }

    return result;
}

int check_diagonal(const int *matrix, int rows, int cols,
                   int start_row, int start_col)
{
    int row = start_row;
    int col = start_col;
    int length = 0;

    while (row < rows && col < cols)
    {
        if (matrix[row * cols + col] == 0)
        {
            return 0;
        }

        length++;
        row++;
        col++;
    }

    if (length < 2)
    {
        return 0;
    }

    return 1;
}

int count_diagonals(const int *matrix, int rows, int cols)
{
    int result = 0;

    for (int col = 0; col < cols; col++)
    {
        result += check_diagonal(matrix, rows, cols, 0, col);
    }

    for (int row = 1; row < rows; row++)
    {
        result += check_diagonal(matrix, rows, cols, row, 0);
    }

    return result;
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        std::cerr << "error: expected 3 arguments\n";
        return 1;
    }

    int num;

    if (same(argv[1], "1"))
    {
        num = 1;
    }
    else if (same(argv[1], "2"))
    {
        num = 2;
    }
    else
    {
        std::cerr << "error: first argument must be 1 or 2\n";
        return 1;
    }

    std::ifstream input(argv[2]);

    if (!input)
    {
        std::cerr << "error: cannot open input file\n";
        return 2;
    }

    int rows, cols;

    if (!(input >> rows >> cols) ||
        rows < 0 || cols < 0 ||
        ((rows == 0) != (cols == 0)))
    {
        std::cerr << "error: invalid matrix\n";
        return 2;
    }

    unsigned long long size =
        static_cast<unsigned long long>(rows) *
        static_cast<unsigned long long>(cols);

    if (num == 1 && size > max_size)
    {
        std::cerr << "error: invalid matrix\n";
        return 2;
    }

    int fixed[max_size];
    int *matrix = fixed;

    if (num == 2 && size > 0)
    {
        try
        {
            matrix = new int[size];
        }
        catch (...)
        {
            std::cerr << "error: not enough memory\n";
            return 2;
        }
    }

    for (unsigned long long i = 0; i < size; i++)
    {
        if (!(input >> matrix[i]))
        {
            std::cerr << "error: invalid matrix\n";

            if (num == 2 && size > 0)
            {
                delete[] matrix;
            }

            return 2;
        }
    }

    char extra;

    if (input >> extra)
    {
        std::cerr << "error: extra data in input file\n";

        if (num == 2 && size > 0)
        {
            delete[] matrix;
        }

        return 2;
    }

    input.close();

    int columns_result = count_columns(matrix, rows, cols);
    int diagonals_result = count_diagonals(matrix, rows, cols);

    std::ofstream output(argv[3]);

    if (!output)
    {
        std::cerr << "error: cannot open output file\n";

        if (num == 2 && size > 0)
        {
            delete[] matrix;
        }

        return 2;
    }

    output << columns_result << '\n';
    output << diagonals_result << '\n';

    if (!output)
    {
        std::cerr << "error: cannot write output file\n";

        if (num == 2 && size > 0)
        {
            delete[] matrix;
        }

        return 2;
    }

    output.close();

    if (num == 2 && size > 0)
    {
        delete[] matrix;
    }

    return 0;
}
