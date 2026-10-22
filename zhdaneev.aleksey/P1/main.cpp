#include <iostream>

namespace zhdaneev
{
    int charact();
}

int zhdaneev::charact()
{
    int num = 0;
    std::cin >> num;

    if (!std::cin)
    {
        std::cerr << "Invalid input\n";
        return 1;
    }

    if (num == 0)
    {
        std::cerr << "Empty sequence\n";
        return 2;
    }

    int inc_seq = 0;
    int evn_cnt = 0;
    int even_run = 0;
    int prev = num;

    if (num % 2 == 0)
    {
        even_run = 1;
        evn_cnt = 1;
    }

    while (true)
    {
        std::cin >> num;
        if (!std::cin)
        {
            std::cerr << "Invalid input\n";
            return 1;
        }

        if (num == 0)
        {
            break;
        }

        if (num > prev)
        {
            inc_seq++;
        }

        if (num % 2 == 0)
        {
            even_run++;
            if (even_run > evn_cnt)
            {
                evn_cnt = even_run;
            }
        }
        else
        {
            even_run = 0;
        }

        prev = num;
    }

    std::cout << evn_cnt << "\n";
    std::cout << inc_seq << "\n";
    return 0;
}

int main()
{
    return zhdaneev::charact();
}
