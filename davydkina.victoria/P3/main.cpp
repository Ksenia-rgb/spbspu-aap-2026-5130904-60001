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
