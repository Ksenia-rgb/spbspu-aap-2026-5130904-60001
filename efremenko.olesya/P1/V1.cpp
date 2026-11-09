#include <iostream>

namespace efremenko
{
    int calculate_div_rem()
    {
        int prev, curr;

        if (!(std::cin >> prev))
        {
            if (std::cin.eof())
            {
                return 2;
            }
            std::cer << "Error: Input is not a valid sequence\n";
            return 1;
        }

        if (prev == 0)
        {
            return 2;
        }

        int count = 0;
        bool has_second = false;

        while (std::cin >> curr && curr != 0)
        {
            has_second = true;
            if (curr % prev == 0)
            {
                ++count;
            }
            prev = curr;
        }

        if (!has_second)
        {
            return 2;
        }

        std::cout << count << '\n';
        return 0;
    }
}

int main()
{
    return efremenko::calculate_div_rem();
}
