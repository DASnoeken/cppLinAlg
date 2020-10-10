#pragma once
#include <string>
#include <exception>
class MatrixException: public std::exception
{
public:
	MatrixException(const char* name);
	const char* getWhat();
	std::string toString();
private:
	std::string _what;
};

