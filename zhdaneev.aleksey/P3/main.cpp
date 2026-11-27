#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <new>
#include <stdexcept>

namespace zhdaneev
{
    const std::size_t MAX_FIXED_ELEMENTS = 10000;

    bool isValidSize(std::size_t rows, std::size_t cols)
    {
        if (rows == 0 || cols == 0)
        {
            return rows == 0 && cols == 0;
        }
        const std::size_t maxSize = std::numeric_limits<std::size_t>::max();
        return rows <= maxSize / cols
            && rows * cols <= maxSize / sizeof(long long);
    }

    std::istream& readMatrix(std::istream& input, long long* data, std::size_t count)
    {
        for (std::size_t i = 0; i < count && input; ++i)
        {
            input >> data[i];
        }
        return input;
    }

    template <class T>
    std::ostream& writeMatrix(std::ostream& output, const T* data,
        std::size_t rows, std::size_t cols)
    {
        output << rows << ' ' << cols;
        const std::size_t count = rows * cols;
        for (std::size_t i = 0; i < count; ++i)
        {
            output << ' ' << data[i];
        }
        return output;
    }

    void applyBottomLeftClockwise(long long* data, std::size_t rows, std::size_t cols)
    {
        if (rows == 0 || cols == 0)
        {
            return;
        }

        std::size_t top = 0;
        std::size_t bottom = rows - 1;
        std::size_t left = 0;
        std::size_t right = cols - 1;
        long long step = 1;

        while (top <= bottom && left <= right)
        {
            for (std::size_t row = bottom + 1; row-- > top;)
            {
                data[row * cols + left] -= step++;
            }
            for (std::size_t col = left + 1; col <= right; ++col)
            {
                data[top * cols + col] -= step++;
            }
            if (bottom > top && right > left)
            {
                for (std::size_t row = top + 1; row <= bottom; ++row)
                {
                    data[row * cols + right] -= step++;
                }
            }
            if (bottom > top && right > left + 1)
            {
                for (std::size_t col = right; col-- > left + 1;)
                {
                    data[bottom * cols + col] -= step++;
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

    // среднее sum / count, округлённое до десятых, в виде целого числа десятых
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

    void buildSmoothed(const long long* source, double* result,
        std::size_t rows, std::size_t cols)
    {
        for (std::size_t row = 0; row < rows; ++row)
        {
            for (std::size_t col = 0; col < cols; ++col)
            {
                long long sum = 0;
                long long neighbors = 0;
                const std::size_t rowStart = row == 0 ? 0 : row - 1;
                const std::size_t rowEnd = row + 1 < rows ? row + 1 : row;
                const std::size_t colStart = col == 0 ? 0 : col - 1;
                const std::size_t colEnd = col + 1 < cols ? col + 1 : col;

                for (std::size_t r = rowStart; r <= rowEnd; ++r)
                {
                    for (std::size_t c = colStart; c <= colEnd; ++c)
                    {
                        if (r == row && c == col)
                        {
                            continue;
                        }
                        sum += source[r * cols + c];
                        ++neighbors;
                    }
                }

                const std::size_t index = row * cols + col;
                result[index] = neighbors == 0
                    ? static_cast<double>(source[index])
                    : static_cast<double>(roundedTenths(sum, neighbors)) / 10.0;
            }
        }
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
    char* end = nullptr;
    const long number = std::strtol(argv[1], &end, 10);
    if (end == argv[1] || *end != '\0' || (number != 1 && number != 2))
    {
        std::cerr << "Error: first parameter must be 1 or 2\n";
        return 1;
    }

    long long fixedOriginal[MAX_FIXED_ELEMENTS];
    long long fixedSpiral[MAX_FIXED_ELEMENTS];
    double fixedSmooth[MAX_FIXED_ELEMENTS];
    long long* original = number == 1 ? fixedOriginal : nullptr;
    long long* spiral = number == 1 ? fixedSpiral : nullptr;
    double* smoothed = number == 1 ? fixedSmooth : nullptr;

    int result = 0;
    try
    {
        std::ifstream input(argv[2]);
        if (!input)
        {
            throw std::runtime_error("cannot open input file");
        }

        std::size_t rows = 0;
        std::size_t cols = 0;
        if (!(input >> rows >> cols) || !isValidSize(rows, cols))
        {
            throw std::runtime_error("invalid matrix size");
        }
        const std::size_t count = rows * cols;
        if (number == 1 && count > MAX_FIXED_ELEMENTS)
        {
            throw std::runtime_error("matrix too large");
        }

        if (number == 2)
        {
            original = new long long[count];
            spiral = new long long[count];
            smoothed = new double[count];
        }

        if (!readMatrix(input, original, count))
        {
            throw std::runtime_error("invalid matrix data");
        }
        input >> std::ws;
        if (!input.eof())
        {
            throw std::runtime_error("invalid matrix data");
        }

        for (std::size_t i = 0; i < count; ++i)
        {
            spiral[i] = original[i];
        }
        applyBottomLeftClockwise(spiral, rows, cols);
        buildSmoothed(original, smoothed, rows, cols);

        std::ofstream output(argv[3]);
        if (!output)
        {
            throw std::runtime_error("cannot open output file");
        }
        output.precision(15);
        writeMatrix(output, spiral, rows, cols) << '\n';
        writeMatrix(output, smoothed, rows, cols) << '\n';
        if (!output)
        {
            throw std::runtime_error("writing output failed");
        }
    }
    catch (const std::bad_alloc&)
    {
        std::cerr << "Error: not enough memory\n";
        result = 2;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        result = 2;
    }

    if (number == 2)
    {
        delete[] original;
        delete[] spiral;
        delete[] smoothed;
    }
    return result;
}
