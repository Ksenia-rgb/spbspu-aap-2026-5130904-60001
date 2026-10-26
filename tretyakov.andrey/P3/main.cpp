#include <iostream>
#include <fstream>
#include <cstddef>
#include <cstdlib>
#include <cstring>


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
}
