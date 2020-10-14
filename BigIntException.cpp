#include "BigIntException.h"

BigIntException::BigIntException(const char* name):_what(name)
{
}

const char* BigIntException::getWhat()
{
	return this->_what.c_str();
}

std::string BigIntException::toString()
{
	return "Thrown BigIntException!";
}

std::ostream& operator<<(std::ostream& os, const BigIntException& bie)
{
	return (os << "\033[1;31mERROR![0m");
}
