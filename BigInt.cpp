#include "BigInt.h"
#include <charconv>
#include <iostream>
#include <string>

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

BigInt BigInt::operator+(const BigInt& bi)
{
	std::string answer;
	std::vector<short> otherDigits = bi.getDigits();
	std::vector<short>::reverse_iterator riter = this->digits.rbegin();
	std::vector<short>::reverse_iterator riterOther = otherDigits.rbegin();
	short digit1, digit2, sum, carry;
	carry = 0;
	while (riter != this->digits.rend() && riterOther != otherDigits.rend()) {
		digit1 = *riter;
		digit2 = *riterOther;
		sum = digit1 + digit2 + carry;
		std::string sumstring = std::to_string(sum);
		if (sum < 10) {
			answer = sumstring + answer;
			carry = 0;
		}
		else {
			std::string_view sv(sumstring);
			carry = 1;
			answer = sv.at(1) + answer;
		}
		++riter;
		++riterOther;
	}
	return BigInt(answer.c_str());
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
}

const unsigned int BigInt::getNumberOfDigits() const
{
	return this->numberOfDigits;
}

const std::vector<short> BigInt::getDigits() const
{
	return this->digits;
}

