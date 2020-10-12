#include "BigInt.h"
#include <charconv>
#include <iostream>

BigInt::BigInt(const char* in)
{
	std::string_view input(in);
	this->numberOfDigits = input.size();
	this->digits.reserve(this->numberOfDigits + 1);
	for (unsigned int i = 0; i < this->numberOfDigits; i++) {
		short s;
		std::from_chars_result fsr = std::from_chars(input.data(), input.data() + 1, s);
		input = std::string_view(input.data() + 1);
		this->digits.push_back(s);
	}
}

BigInt BigInt::operator+(const BigInt& bi)		//not implemented yet
{
	return BigInt("0");
}

BigInt BigInt::operator-(const BigInt& bi)		//not implemented yet
{
	return BigInt("0");
}

void BigInt::setDigit(unsigned int& index, unsigned short& val)
{

}

void BigInt::printNumber()
{
	for (unsigned int i = 0; i < this->getNumberOfDigits(); i++) {
		std::cout << this->getDigits().at(i);
	}
	std::cout << std::endl;
}

const unsigned int BigInt::getNumberOfDigits() const
{
	return this->numberOfDigits;
}

const std::vector<short> BigInt::getDigits() const
{
	return this->digits;
}

