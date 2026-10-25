#include <iostream>
#include <fstream>

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
