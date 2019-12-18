#include "Logger.h"



Logger::Logger(string s)
{
	log = ofstream(s);
}


Logger::~Logger()
{
	log.close();
}



void Logger::write(double x, double y) {
	log << "(" << x << ";" << y << ")\n";
}