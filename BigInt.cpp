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
		this->digits.emplace_back(s);
	}
}

BigInt::BigInt(int in)
{
	std::string_view input(std::to_string(in).c_str());
	this->numberOfDigits = input.size();
	this->digits.reserve(this->numberOfDigits + 1);
	for (unsigned int i = 0; i < this->numberOfDigits; i++) {
		short s;
		std::from_chars_result fsr = std::from_chars(input.data(), input.data() + 1, s);
		input = std::string_view(input.data() + 1);
		this->digits.emplace_back(s);
	}
}

BigInt::BigInt(long in)
{
	std::string_view input(std::to_string(in).c_str());
	this->numberOfDigits = input.size();
	this->digits.reserve(this->numberOfDigits + 1);
	for (unsigned int i = 0; i < this->numberOfDigits; i++) {
		short s;
		std::from_chars_result fsr = std::from_chars(input.data(), input.data() + 1, s);
		input = std::string_view(input.data() + 1);
		this->digits.emplace_back(s);
	}
}

BigInt::BigInt(short in)
{
	std::string_view input(std::to_string(in).c_str());
	this->numberOfDigits = input.size();
	this->digits.reserve(this->numberOfDigits + 1);
	for (unsigned int i = 0; i < this->numberOfDigits; i++) {
		short s;
		std::from_chars_result fsr = std::from_chars(input.data(), input.data() + 1, s);
		input = std::string_view(input.data() + 1);
		this->digits.emplace_back(s);
	}
}

BigInt::BigInt(const BigInt& bi_old)
{
	std::cout << "here" << std::endl;
	std::string newInput = "";
	for (int i = 0; i < bi_old.digits.size(); i++) {
		newInput += std::to_string(bi_old.digits.at(i));
	}
	std::string_view input(newInput);
	this->numberOfDigits = input.size();
	this->digits.reserve(this->numberOfDigits + 1);
	for (unsigned int i = 0; i < this->numberOfDigits; i++) {
		short s;
		std::from_chars_result fsr = std::from_chars(input.data(), input.data() + 1, s);
		input = std::string_view(input.data() + 1);
		this->digits.emplace_back(s);
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
	this->digits.at(index) = val;
}

void BigInt::printNumber()
{
	for (unsigned int i = 0; i < this->getNumberOfDigits(); i++) {
		std::cout << this->getDigits().at(i);
	}
}

int BigInt::compare(const BigInt& other) //returns 0 when equal, -1 when this<other and 1 when this>other
{
	if (this->getDigits().size() != other.getDigits().size()) {
		if (this->getNumberOfDigits() < other.getNumberOfDigits())
			return -1;
		else if (this->getNumberOfDigits() > other.getNumberOfDigits())
			return 1;
	}
	else {
		for (int i = 0; i < this->getNumberOfDigits(); i++) {
			if (this->getDigits().at(i) < other.getDigits().at(i)) {
				return -1;
			}
			else if (this->getDigits().at(i) > other.getDigits().at(i)) {
				return 1;
			}
			else {
				continue;
			}
		}
	}
	return 0;
}

bool BigInt::equals(const BigInt& other)
{
	if (this->getDigits().size() != other.getDigits().size()) {
		return false;
	}
	for (int i = 0; i < this->getNumberOfDigits(); i++) {
		if (this->getDigits().at(i) != other.getDigits().at(i)) {
			return false;
		}
		else {
			continue;
		}
	}
	return true;
}

const unsigned int BigInt::getNumberOfDigits() const
{
	return this->numberOfDigits;
}

const std::vector<short> BigInt::getDigits() const
{
	return this->digits;
}

