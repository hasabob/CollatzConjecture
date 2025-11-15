#pragma warning(disable : 4146)

#include <chrono>
#include <condition_variable>
#include <fstream>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace boost::multiprecision;

// Variables
cpp_int Init = cpp_int("295000000000000000000000");		//Initial Variable
const char* SAVE_FILE = "collatz.log";					//Save File Name
const char* Timeout =  "collatz.timeout";				//Timeout File Name
cpp_int Reporter = cpp_int("1000000");					//Reports Every 1000000 Iterations