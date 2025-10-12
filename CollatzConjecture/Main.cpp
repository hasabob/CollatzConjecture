#include <iostream>

int main()
{
	unsigned long long x_orig = 2;								/*295000000000000000000000*/
	if (x_orig % 2 == 0)					// Prevents Collatz sequence from being even
	{
		x_orig++;
	}
	unsigned long long x_old = x_orig;
	int i = 0;
	while (true)
	{
		unsigned long long x = x_old;
		if (i % 100000 == 0)
		{
			std::cout << x << "\n";
		}
		while (x > x_old - 1)				// Stops x value dropping below tested numbers
		{
			if (x % 2 == 0)
			{
				x = x / 2;
				//std::cout << "x = " << x << " (even)\n";
			}
			else							// Checks if  x is negative, then collatz-ifies it
			{
				x = (3 * x) + 1;
				//std::cout << "x = " << x << "(odd)\n";
			}
		}
		x_old += 2;							// Sequences Collatz sequence
		i++;
		//std::cout << "=========DONE=========\n";
	}
}