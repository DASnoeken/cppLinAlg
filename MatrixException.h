#pragma once
#include <string>
#include <exception>
class MatrixException: public std::exception
{
public:
	MatrixException(const char* name);
	const char* getWhat();
	std::string toString();

	friend std::ostream& operator<<(std::ostream& os, const MatrixException& me);
private:
	std::string _what;
};

