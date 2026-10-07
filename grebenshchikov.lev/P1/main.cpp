#include <iostream>

int main() {
	long long max = -1000000000000;
	long long submax = -1000000000000;
	long long a = -1;

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
	}
	std::cout << submax << '\n';
	return 0;
}
