#pragma once
#include <string>
#include <exception>
class BigIntException : public std::exception
{
public:
	BigIntException(const char* name);
	const char* getWhat();
	std::string toString();
	friend std::ostream& operator<<(std::ostream& os, const BigIntException& bie);
private:
	std::string _what;
};

