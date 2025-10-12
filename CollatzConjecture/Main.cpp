#include <iostream>

int main()
{
	unsigned int x_orig = 2;								/*295000000000000000000000*/
	unsigned int x_old = x_orig;
	while (true)
	{
		unsigned int x = x_old;
		std::cout << x << std::endl;
		if (x % 2 != 0)							// Stops x value from dropping below tested numbers by stopping all even values
		{
			while (x > x_old - 1)				// Stops x value dropping below tested numbers
			{
				if (x % 2 == 0)
				{
					x = x / 2;
				}
				else							// Checks if x is negative, then collatz-ifies it
				{
					x = (3 * x) + 1;
				}
			}
		}
		x_old += 1;								// Sequences Collatz Process
	}
}