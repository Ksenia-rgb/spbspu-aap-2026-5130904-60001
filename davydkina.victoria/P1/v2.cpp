#include <iostream>

int main()
{
    int max;
    int curr;
    int c = 0;

    std::cin >> curr;

    if (curr == 0)
    {
        std::cerr << "error: the sequence is empty\n";
        return 2;
    }

    max = curr;
    c = 1;

    while (std::cin >> curr)
    {
        if (curr == 0)
        {
            break;
        }
        else if (curr == max)
        {
            c++;
        }
    }
    if (!std::cin.eof() && std::cin.fail())
    {
        std::cerr << "error: the input is not a sequence\n";
        return 1;
    }

    std::cout << c << '\n';
    return 0;
}
