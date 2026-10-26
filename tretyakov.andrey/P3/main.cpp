#include <iostream>
#include <fstream>
#include <cstddef>
#include <cstdlib>


int main(int argc, char * argv[])
{
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
        std::cerr << "Can't read matrix cols and rows\n";
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
}
