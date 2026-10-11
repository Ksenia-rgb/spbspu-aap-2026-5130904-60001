#include <iostream>

namespace efremenko
{
    int calculate_evn_cnt()
    {
	int curr;
	int current_even = 0;
	int max_even = 0;

	while (std::cin >> curr && curr != 0)
	{
	    if (curr % 2 == 0)
	    {
		++current_even;
		if (current_even > max_even)
		{
		    max_even = current_even;
		}
	    }

	    else
	    {
		current_even = 0;
	    }
	}

	if (std::cin.fail() && !std::cin.eof())
	{
	    std::cerr << "Error: Input is not a valid sequence\n"
	    return 1;
	}

	std::cout << max_even << '\n';
	return 0;
    }
}

int main()
{
    return efremenko::calculate_evn_cnt();
}
