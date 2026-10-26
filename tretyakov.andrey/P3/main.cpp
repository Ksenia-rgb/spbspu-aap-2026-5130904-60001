#include <iostream>
#include <fstream>
#include <cstddef>
#include <cstdlib>

bool solveLwrTriMtx(const int * matrix, size_t rows, size_t cols)
{
    size_t k;
    if (rows < cols)
    {
        k = rows;
    }
    else
    {
        k = cols;
    }
    if (k == 0)
    {
        return false;
    }
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < k; ++j)
        {
            if (matrix[i * cols + j] != 0)
            {
                return false;
            }
        }
    }
    return true;
}

size_t solveCntLocMax(const int * matrix, size_t rows, size_t cols)
{
    size_t count = 0;
    int currentElement = 0;
    for (size_t i = 1; i < rows - 1; ++i)
    {
        for (size_t j = 1; j < cols - 1; ++j)
        {
            currentElement = matrix[i * cols + j];
            bool isElementMax = true;
            for (int deltaI = -1; deltaI <= 1; ++deltaI)
            {
                for (int deltaJ = -1; deltaJ <= 1; ++deltaJ)
                {
                    if (deltaI == 0 && deltaJ == 0)
                    {
                        continue;
                    }
                    if (matrix[(i + deltaI) * cols + (j + deltaJ)] >= currentElement)
                    {
                        isElementMax = false;
                        break;
                    }
                }
                if (!isElementMax)
                {
                    break;
                }
            }
            if (isElementMax)
            {
                ++count;
            }
        }
    }
    return count;
}

int main(int argc, char * argv[])
{
    const size_t countElements = 10000;
    bool lowerTriangleMtx = false;
    size_t counterOfLocalMaximum = 0;
    if (argc < 4)
    {
       std::cerr << "Not enough arguments\n";
       return 1;
    }
    if (argc > 4)
    {
        std::cerr << "Too many arguments\n";
        return 1;
    }
    int num = 0;
    try
    {
        num = std::stoi(argv[1]);
        if (!(num < 3 && num > 0))
        {
            std::cerr << "First parametr is out of range\n";
            return 1;
        }
    }
    catch (const std::invalid_argument & )
    {
        std::cerr << "First parametr is not a number\n";
        return 1;
    }
    std::ifstream inFile(argv[2]);
    if (!inFile)
    {
        std::cerr << "Can't open input file\n";
        return 2;
    }
    std::ofstream outFile(argv[3]);
    if (!outFile)
    {
        std::cerr << "Can't open outFile\n";
        return 2;
    }
    size_t rows = 0;
    size_t cols = 0;
    inFile >> rows >> cols;
    if (!(inFile >> rows >> cols) || (rows < 0) || (cols < 0))
    {
        std::cerr << "Can't read matrix cols and rows or matrix doesn't exist\n";
        return 2;
    }
    if ((rows == 0 && cols != 0) || (rows !=0 && cols == 0))
    {
        std::cerr << "Matrix doesn't exist\n";
        return 2;
    }
    if (rows == 0 && cols == 0)
    {
        outFile << 0 << " " << 0;
        return 0;
    }
    if (num == 1)
    {
        if (rows > countElements / cols)
        {
            std::cerr << "Matrix is too large\n";
            return 2;
        }
        int matrix[countElements] = {};
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                if (!(inFile >> matrix[i * cols + j]))
                {
                    std::cerr << "inFile error\n";
                    return 2;
                }
            }
        }
        lowerTriangleMtx = solveLwrTriMtx(matrix, rows, cols);
        counterOfLocalMaximum = solveCntLocMax(matrix, rows, cols);
        outFile << lowerTriangleMtx << "\n";
        outFile << counterOfLocalMaximum << "\n";
    }
}
