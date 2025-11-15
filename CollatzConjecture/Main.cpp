#include "Include/functions.hpp"

int main()
{
	cpp_int savedValue = readFile(SAVE_FILE);
	cout << "Reading " << readFile(SAVE_FILE) << " from " << SAVE_FILE << "\n";
	cout << savedValue << "\n";
	if (savedValue != 0)
	{
		x_orig = readFile(SAVE_FILE);
	}
	else
	{
		x_orig = Init;
	}
	if (x_orig % 2 == 0)								// Prevents Collatz sequence from being even
	{
		x_orig++;
	}
	cpp_int x_old = x_orig;
	int i = 0;

	thread watcher(timeoutWatcher, 5);

	while (true)
	{
		cpp_int x = x_old;

		{
			lock_guard<mutex> lock(mtx);
			stopTimeout = false;
			timeoutReached = false;
		}
		cv.notify_all();

		if (i % Reporter == 0)
		{
			cout << x << "\n";
			saveFile(SAVE_FILE, x_old);
		}
		
		while (x > x_old - 1 && !timeoutReached)		// Stops x value dropping below tested and checks if x takes too long to compute
		{
			if (x % 2 == 0) x = x / 2;
			else x = (3 * x) + 1;						// Checks if  x is negative, then collatz-ifies it
		}

		if (!timeoutReached)
		{
			{
				lock_guard <mutex> lock(mtx);
				stopTimeout = true;
			}
			cv.notify_all();
		}

		x_old += 2;										// Sequences Collatz sequence
		i++;
	}
	stopProgram = true;
	cv.notify_all();
	watcher.join();
}