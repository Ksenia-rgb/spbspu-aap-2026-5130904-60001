#include <iostream>

int main()
{
	long long max = -1000000000000;
	long long sub_max = -1000000000000;
	long long a = -1;
	long long ctn_min = 0;
	long long min = 100000000000;
	long long count = 0;

	while (a != 0)
	{
		std::cin >> a;

		if (std::cin.fail())
		{
			std::cerr << "Error: input is not valid sequence of integers\n";
			return 1;
		}

		if (a > max && a != 0)
		{
			sub_max = max;
			max = a;
		} else if (a >= sub_max && a < max && a != 0)
		{
			sub_max = a;
		}

		if (a < min && a != 0)
		{
			min = a;
			ctn_min = 1;
		} else if (a == min)
		{
			++ctn_min;
		}

		if (a != 0)
		{
			++count;
		}
	}

	int exitCode = 0;

	if (count < 2)
	{
		std::cerr << "Erorr: sequence too short for SUB-MAX\n";
		exitCode = 2;
	} else {
		std::cout << sub_max << '\n';
	}

	std::cout << ctn_min << '\n';
	return exitCode;
}
