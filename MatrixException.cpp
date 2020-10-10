#include "MatrixException.h"

MatrixException::MatrixException(const char* name):_what(name)
{
}

const char* MatrixException::getWhat()
{
	return this->_what.c_str();
}

std::string MatrixException::toString() {
	return "Thrown MatrixException!";
}