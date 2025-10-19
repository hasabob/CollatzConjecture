#pragma warning(disable : 4146)

#include <chrono>
#include <condition_variable>
#include <fstream>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
using namespace std;

unsigned long long x_orig;
unsigned long long x_old;
unsigned long long x;
bool timeoutReached = false;
bool stopTimeout = false;
bool stopProgram = false;

mutex mtx;
condition_variable cv;

// This function writes to a file, after passing the 
// filename as a string and a value as a number
int saveFile(const char* filename, const unsigned long long value)
{
	// Setup
	ofstream file(filename);

	// Save File
	file << value;
	file.close();
	return 0;
}

// This function writes to a file after taking the argument "filename"
unsigned long long readFile(const char* filename)
{
	string line;
	ifstream myfile(filename);
	unsigned long long value = 0;

	if (myfile)
	{
		myfile >> value;
		myfile.close();
	}
	else
	{
		cout << "Unable to open file";
	}

	return value;
}

// This functtion waits for a timeout and 
// then writes to a file for later testing
int handleTimeout(int seconds, bool& timeoutReached, bool& stopTimeout)
{
	unique_lock<mutex> lock(mtx);
	if (cv.wait_for(lock, chrono::seconds(seconds), [&] { return stopTimeout;  }))
	{
		return 0;
	}
	timeoutReached = true;
	saveFile("collatz.timeout", x_orig);
	return 0;

	/*for (int i = 0; i < minutes * 10; i++)
	{
		if (stopTimeout) return 0;
		this_thread::sleep_for(chrono::milliseconds(100));
	}
	timeoutReached = true;
	saveFile("collatz.timeout", x_orig);
	return 0;*/
}

void timeoutWatcher(int seconds)
{
	unique_lock<mutex> lock(mtx);
	while (!stopProgram)
	{
		if (cv.wait_for(lock, chrono::seconds(seconds), [&] {return stopTimeout; }))
		{
			stopTimeout = false;
		}
		else
		{
			timeoutReached = true;
			saveFile("collatz.timeout", x_orig);
		}
	}
}

int main()
{
	const char* SAVE_FILE = "collatz.log";
	unsigned long long savedValue = readFile(SAVE_FILE);
	cout << "Reading " << readFile(SAVE_FILE) << " from " << SAVE_FILE << "\n";
	cout << savedValue << "\n";
	if (savedValue != 0)
	{
		x_orig = readFile(SAVE_FILE);
	}
	else
	{
		x_orig = 3;							/*295000000000000000000000*/
	}
	if (x_orig % 2 == 0)								// Prevents Collatz sequence from being even
	{
		x_orig++;
	}
	unsigned long long x_old = x_orig;
	int i = 0;

	thread watcher(timeoutWatcher, 5);

	while (true)
	{
		unsigned long long x = x_old;

		{
			lock_guard<mutex> lock(mtx);
			stopTimeout = false;
			timeoutReached = false;
		}
		cv.notify_all();

		if (i % 1000000 == 0)
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