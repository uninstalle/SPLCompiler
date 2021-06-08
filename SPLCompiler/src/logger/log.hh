#pragma once
#include <fstream>
#include <string>

class Logger
{
	std::ofstream out;

public:
	Logger(const std::string& logPath) : out(std::ofstream(logPath)) {}
	Logger(const Logger& logger) = delete;
	Logger(Logger&& logger) = delete;
	Logger& operator=(const Logger& logger) = delete;
	Logger& operator=(Logger&& logger) = delete;
	
	Logger& print(const std::string& text)
	{
		out << text;
		return *this;
	}
	Logger& print(const char* text)
	{
		out << text;
		return *this;
	}
	Logger& println(const std::string& text)
	{
		out << text << std::endl;
		return *this;
	}
	Logger& println(const char* text)
	{
		out << text << std::endl;
		return *this;
	}
	Logger& println()
	{
		out << std::endl;
		return *this;
	}
	~Logger()
	{
		out.close();
	}
};

extern Logger LexLogger;
extern Logger YaccLogger;
extern Logger CodeGenLogger;