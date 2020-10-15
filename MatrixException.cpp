#include "MatrixException.h"

MatrixException::MatrixException(const char* name):_what(name)
{
}

const char* MatrixException::getWhat() const
{
	return this->_what.c_str();
}

std::string MatrixException::toString() {
	return "Thrown MatrixException!";
}

std::ostream& operator<<(std::ostream& os, const MatrixException& me)
{
	return(os << "\033[1;31mERROR![0m");
}
