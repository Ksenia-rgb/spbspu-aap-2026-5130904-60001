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
  void applyBottomLeftClockwise(Matrix& matrix)
  {
    if (matrix.rows == 0 || matrix.cols == 0)
    {
        return;
    }

    size_t top = 0;
    size_t bottom = matrix.rows - 1;
    size_t left = 0;
    size_t right = matrix.cols - 1;
    long long step = 1;

    while (top <= bottom && left <= right)
    {
        for (size_t col = left; col <= right; ++col)
        {
            if (bottom == matrix.rows - 1 && col == left)
            {
                continue;
            }

            matrix.data[bottom * matrix.cols + col] -= step++;
        }

        if (bottom > top)
        {
            for (size_t row = bottom; row-- > top;)
            {
                matrix.data[row * matrix.cols + right] -= step++;
            }
        }

        if (right > left && top < bottom)
        {
            for (size_t col = right; col-- > left;)
            {
                matrix.data[top * matrix.cols + col] -= step++;
            }
        }

        if (right > left && bottom > top + 1)
        {
            for (size_t row = top + 1; row < bottom; ++row)
            {
                matrix.data[row * matrix.cols + left] -= step++;
            }
        }

        if (bottom == 0 || right == 0)
        {
            break;
        }

        ++top;
        --bottom;
        ++left;
        --right;
    }
  }
}
int main()
{
    return 0;
}
