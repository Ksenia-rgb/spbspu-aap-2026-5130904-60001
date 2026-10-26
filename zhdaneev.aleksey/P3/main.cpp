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
  long long divideRounded(long long numerator, long long denominator)
  {
    long long quotient = numerator / denominator;
    long long remainder = numerator % denominator;

    if (remainder >= (denominator + 1) / 2)
    {
        ++quotient;
    }
    else if (remainder <= -((denominator + 1) / 2))
    {
        --quotient;
    }

    return quotient;
  }
  bool buildSmoothed(const Matrix& source, Matrix& result)
  {
        result.rows = source.rows;
        result.cols = source.cols;
        result.data = nullptr;

        if (source.rows == 0 || source.cols == 0)
        {
            return true;
        }

        const size_t maxSize = static_cast<size_t>(-1);

        if (source.rows > maxSize / source.cols)
        {
            return false;
        }

        const size_t count = source.rows * source.cols;

        if (count > maxSize / sizeof(long long))
        {
            return false;
        }

        result.data = new long long[count];

        for (size_t row = 0; row < source.rows; ++row)
        {
            for (size_t col = 0; col < source.cols; ++col)
            {
                long long sum = 0;
                long long neighbors = 0;

                const size_t rowStart = row == 0 ? 0 : row - 1;
                const size_t rowEnd =
                    row + 1 < source.rows ? row + 1 : row;

                const size_t colStart = col == 0 ? 0 : col - 1;
                const size_t colEnd =
                    col + 1 < source.cols ? col + 1 : col;

                for (size_t r = rowStart; r <= rowEnd; ++r)
                {
                    for (size_t c = colStart; c <= colEnd; ++c)
                    {
                        if (r == row && c == col)
                        {
                            continue;
                        }

                        sum += source.data[r * source.cols + c];
                        ++neighbors;
                    }
                }

                const size_t index = row * source.cols + col;

                if (index >= count)
                {
                    delete[] result.data;
                    result.data = nullptr;
                    return false;
                }

                if (neighbors == 0)
                {
                    result.data[index] =
                        source.data[row * source.cols + col];
                }
                else
                {
                    result.data[index] =
                        divideRounded(sum * 10, neighbors);
                }
            }
        }

        return true;
  }
  void writeMatrix(std::ofstream& output, const Matrix& matrix)
  {
    output << matrix.rows << ' ' << matrix.cols;

    for (size_t i = 0; i < matrix.rows * matrix.cols; ++i)
    {
        output << ' ' << matrix.data[i];
    }

    output << '\n';
  }
  void writeSmoothed(std::ofstream& output, const Matrix& matrix)
  {
    output << matrix.rows << ' ' << matrix.cols;

    for (size_t i = 0; i < matrix.rows * matrix.cols; ++i)
    {
        const long long value = matrix.data[i];
        const long long whole = value / 10;
        const long long fraction =
            value < 0 ? -(value % 10) : value % 10;

        if (fraction == 0)
        {
            output << ' ' << whole;
        }
        else
        {
            output << ' ' << whole << '.' << fraction;
        }
    }

    output << '\n';
  }
}
int main()
{
    return 0;
}
