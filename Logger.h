#pragma once
#include <fstream>
#include <string>

using std::ofstream;
using std::string;

class Logger
{
	ofstream log;
public:
	Logger(string s);
	~Logger();
	void write(double,double);
};

