#include <fstream>
#include <iostream>

namespace zhdaneev
{
    struct Matrix
    {
        std::size_t rows;
        std::size_t cols;
        long long* data;
    };
bool readMatrix(std::ifstream& input, Matrix& matrix)
{
    if (!(input >> matrix.rows >> matrix.cols))
    {
        return false;
    }

    if (matrix.rows == 0 || matrix.cols == 0)
    {
        if (matrix.rows != 0 || matrix.cols != 0)
        {
            return false;
        }

        matrix.data = nullptr;
        return input.peek() == std::ifstream::traits_type::eof();
    }

    if (matrix.rows > static_cast<size_t>(-1) / matrix.cols)
    {
        return false;
    }

    const size_t count = matrix.rows * matrix.cols;
    matrix.data = new long long[count];

    for (size_t i = 0; i < count; ++i)
    {
        if (!(input >> matrix.data[i]))
        {
            delete[] matrix.data;
            matrix.data = nullptr;
            return false;
        }
    }

    input >> std::ws;

    if (!input.eof())
    {
        delete[] matrix.data;
        matrix.data = nullptr;
        return false;
    }

    return true;
}

int main()
{
    return 0;
}
