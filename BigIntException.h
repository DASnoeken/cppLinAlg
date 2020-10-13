#pragma once
#include <string>
#include <exception>
class BigIntException : public std::exception
{
public:
	BigIntException(const char* name);
	const char* getWhat();
	std::string toString();
private:
	std::string _what;
};

