#include <iostream>

int main() {
	long long max = -1000000000000;
	long long submax = -1000000000000;
	long long a = -1;
	long long ctn_min = 0;
	long long min = 100000000000;

	while (a != 0)
	{
		std::cin >> a;
		if (a > max && a != 0)
		{
			submax = max;
			max = a;
		} else if (a >= submax && a < max && a != 0)
		{
			submax = a;
		}

		if (a < min && a != 0)
		{
			min = a;
			ctn_min = 1;
		} else if (a == min)
		{
			++ctn_min;
		}
	}

	std::cout << submax << '\n';
	std::cout << ctn_min << '\n';
	return 0;
}
