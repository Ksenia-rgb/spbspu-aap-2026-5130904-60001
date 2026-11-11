#include <fstream>
#include <iostream>
#include <limits>
#include <new>

namespace zhdaneev
{
    const size_t MAX_FIXED_ELEMENTS = 10000;

    struct Matrix
    {
        size_t rows;
        size_t cols;
        long long* data;
    };

    bool getCount(size_t rows, size_t cols, size_t& count)
    {
        if (rows == 0 || cols == 0)
        {
            count = 0;
            return rows == 0 && cols == 0;
        }
        if (rows > static_cast<size_t>(-1) / cols)
        {
            return false;
        }
        count = rows * cols;
        return count <= static_cast<size_t>(-1) / sizeof(long long);
    }

    bool readMatrix(std::ifstream& input, Matrix& matrix, long long* storage,
        size_t capacity, bool allocate)
    {
        matrix.rows = 0;
        matrix.cols = 0;
        matrix.data = nullptr;
        if (!(input >> matrix.rows >> matrix.cols))
        {
            return false;
        }

        size_t count = 0;
        if (!getCount(matrix.rows, matrix.cols, count))
        {
            return false;
        }
        if (count == 0)
        {
            input >> std::ws;
            return input.eof();
        }
        if (!allocate && count > capacity)
        {
            return false;
        }

        matrix.data = allocate ? new (std::nothrow) long long[count] : storage;
        if (matrix.data == nullptr)
        {
            return false;
        }
        for (size_t i = 0; i < count; ++i)
        {
            if (!(input >> matrix.data[i]))
            {
                if (allocate)
                {
                    delete[] matrix.data;
                }
                matrix.data = nullptr;
                return false;
            }
        }
        input >> std::ws;
        if (!input.eof())
        {
            if (allocate)
            {
                delete[] matrix.data;
            }
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
            
            for (size_t row = bottom + 1; row-- > top;)
            {
                matrix.data[row * matrix.cols + left] -= step++;
            }
            
            for (size_t col = left + 1; col <= right; ++col)
            {
                matrix.data[top * matrix.cols + col] -= step++;
            }
            
            if (bottom > top && right > left)
            {
                for (size_t row = top + 1; row <= bottom; ++row)
                {
                    matrix.data[row * matrix.cols + right] -= step++;
                }
            }
            
            if (bottom > top && right > left + 1)
            {
                for (size_t col = right; col-- > left + 1;)
                {
                    matrix.data[bottom * matrix.cols + col] -= step++;
                }
            }

            if (right == left || bottom == top)
            {
                break;
            }
            ++top;
            --bottom;
            ++left;
            --right;
        }
    }

    long long roundedTenths(long long sum, long long count)
    {
        
        const long long numerator = sum * 10;
        long long quotient = numerator / count;
        const long long remainder = numerator % count;
        if (remainder >= 0)
        {
            if (remainder >= (count + 1) / 2)
            {
                ++quotient;
            }
        }
        else if (-remainder >= (count + 1) / 2)
        {
            --quotient;
        }
        return quotient;
    }

    bool buildSmoothed(const Matrix& source, Matrix& result)
    {
        result.rows = source.rows;
        result.cols = source.cols;
        size_t count = 0;
        if (!getCount(source.rows, source.cols, count))
        {
            return false;
        }
        if (count == 0)
        {
            return true;
        }
        for (size_t row = 0; row < source.rows; ++row)
        {
            for (size_t col = 0; col < source.cols; ++col)
            {
                long long sum = 0;
                long long neighbors = 0;
                const size_t rowStart = row == 0 ? 0 : row - 1;
                const size_t rowEnd = row + 1 < source.rows ? row + 1 : row;
                const size_t colStart = col == 0 ? 0 : col - 1;
                const size_t colEnd = col + 1 < source.cols ? col + 1 : col;

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
                result.data[index] = neighbors == 0
                    ? source.data[index] * 10
                    : roundedTenths(sum, neighbors);
            }
        }
        return true;
    }

    void writeMatrix(std::ofstream& output, const Matrix& matrix)
    {
        output << matrix.rows << ' ' << matrix.cols;
        const size_t count = matrix.rows * matrix.cols;
        for (size_t i = 0; i < count; ++i)
        {
            output << ' ' << matrix.data[i];
        }
        output << '\n';
    }

    void writeSmoothed(std::ofstream& output, const Matrix& matrix)
    {
        output << matrix.rows << ' ' << matrix.cols;
        const size_t count = matrix.rows * matrix.cols;
        for (size_t i = 0; i < count; ++i)
        {
            const long long value = matrix.data[i];
            const long long whole = value / 10;
            const long long fraction = value < 0 ? -(value % 10) : value % 10;
            if (fraction == 0)
            {
                output << ' ' << whole;
            }
            else if (value < 0 && whole == 0)
            {
                output << " -0." << fraction;
            }
            else
            {
                output << ' ' << whole << '.' << fraction;
            }
        }
        output << '\n';
    }

    bool parseTaskNumber(const char* text, int& number)
    {
        if (text[0] == '\0')
        {
            return false;
        }
        number = 0;
        for (size_t i = 0; text[i] != '\0'; ++i)
        {
            if (text[i] < '0' || text[i] > '9')
            {
                return false;
            }
            const int digit = text[i] - '0';
            if (number > (std::numeric_limits<int>::max() - digit) / 10)
            {
                return false;
            }
            number = number * 10 + digit;
        }
        return number == 1 || number == 2;
    }

    int run(const char* inputName, const char* outputName, int number)
    {
        std::ifstream input(inputName);
        if (!input)
        {
            std::cerr << "Error: cannot open input file\n";
            return 2;
        }

        long long fixedOriginal[MAX_FIXED_ELEMENTS];
        long long fixedSpiral[MAX_FIXED_ELEMENTS];
        long long fixedSmooth[MAX_FIXED_ELEMENTS];
        Matrix original{ 0, 0, nullptr };
        if (!readMatrix(input, original, fixedOriginal, MAX_FIXED_ELEMENTS,
            number == 2))
        {
            std::cerr << "Error: invalid matrix data or matrix too large\n";
            return 2;
        }

        size_t count = 0;
        getCount(original.rows, original.cols, count);
        Matrix spiral{ original.rows, original.cols, nullptr };
        Matrix smoothed{ original.rows, original.cols, nullptr };

        if (number == 1)
        {
            for (size_t i = 0; i < count; ++i)
            {
                fixedSpiral[i] = original.data[i];
            }
            spiral.data = fixedSpiral;
            smoothed.data = fixedSmooth;
        }
        else
        {
            spiral.data = count == 0 ? nullptr : new (std::nothrow) long long[count];
            smoothed.data = count == 0 ? nullptr : new (std::nothrow) long long[count];
            if (count != 0 && (spiral.data == nullptr || smoothed.data == nullptr))
            {
                delete[] original.data;
                delete[] spiral.data;
                delete[] smoothed.data;
                std::cerr << "Error: not enough memory\n";
                return 2;
            }
            for (size_t i = 0; i < count; ++i)
            {
                spiral.data[i] = original.data[i];
            }
        }

        applyBottomLeftClockwise(spiral);
        if (!buildSmoothed(original, smoothed))
        {
            if (number == 2)
            {
                delete[] original.data;
                delete[] spiral.data;
                delete[] smoothed.data;
            }
            std::cerr << "Error: cannot build smoothed matrix\n";
            return 2;
        }

        std::ofstream output(outputName);
        if (!output)
        {
            if (number == 2)
            {
                delete[] original.data;
                delete[] spiral.data;
                delete[] smoothed.data;
            }
            std::cerr << "Error: cannot open output file\n";
            return 2;
        }
        writeMatrix(output, spiral);
        writeSmoothed(output, smoothed);

        if (number == 2)
        {
            delete[] original.data;
            delete[] spiral.data;
            delete[] smoothed.data;
        }
        if (!output)
        {
            std::cerr << "Error: writing output failed\n";
            return 2;
        }
        return 0;
    }
}

int main(int argc, char* argv[])
{
    using namespace zhdaneev;
    if (argc != 4)
    {
        std::cerr << "Error: expected 3 command-line arguments\n";
        return 1;
    }
    int number = 0;
    if (!parseTaskNumber(argv[1], number))
    {
        std::cerr << "Error: first parameter must be 1 or 2\n";
        return 1;
    }
    return run(argv[2], argv[3], number);
}
