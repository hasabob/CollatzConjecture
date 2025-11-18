#include "config.hpp"

cpp_int x_orig;
cpp_int x_old;
cpp_int x;
bool timeoutReached = false;
bool stopTimeout = false;
bool stopProgram = false;

mutex mtx;
condition_variable cv;

// This function writes to a file, after passing the 
// filename as a string and a value as a number
int saveFile(const char* filename, const cpp_int value)
{
	// Setup
	ofstream file(filename);
	if (!file.is_open())
	{
		cout << "ERR CREATING FILE\n";
	}

	// Save File
	file << value;
	file.close();
	return 0;
}

// This function writes to a file after taking the argument "filename"
cpp_int readFile(const char* filename)
{
	string line;
	ifstream file(filename);
	cpp_int value = 0;

	if (file)
	{
		file >> value;
		file.close();
	}
	else
	{
		cout << "Unable to open file\nCreating File\n";
		ofstream myfile(filename);
		if (!myfile.is_open())
		{
			cout << "FAILED\n";
		}
		myfile.close();
	}

	return value;
}

// This function waits for a timeout and 
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
			saveFile(Timeout, x_orig);
		}
	}
}
