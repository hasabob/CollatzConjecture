#include <iostream>
#include <fstream>
#include <string>
using namespace std;

unsigned long long x_orig;
unsigned long long x_old;
unsigned long long x;

int saveFile(const char* filename, const unsigned long long data)
{
	// Setup
	ofstream file;

	// Save File
	file.open(filename);
	file << data;
	file.close();
	return 0;
}

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
			saveFile(SAVE_FILE, x_old);
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