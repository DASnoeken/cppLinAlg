#include "BigInt.h"
#include "BigIntException.h"

#include <charconv>
#include <iostream>
#include <string>

BigInt::BigInt(const char* in)
{
	std::string_view input(in);
	if (input.at(0) == '-') {
		this->sign = -1;
		input = std::string_view(input.data() + 1);
	}
	else {
		this->sign = 1;
	}
	while (input.at(0) == '0') {
		input = std::string_view(input.data() + 1);
	}
	this->numberOfDigits = input.size();
	this->digits.reserve(this->numberOfDigits);
	for (unsigned int i = 0; i < this->numberOfDigits; i++) {
		short s;
		std::from_chars_result fsr = std::from_chars(input.data(), input.data() + 1, s);
		input = std::string_view(input.data() + 1);
		this->digits.emplace_back(s);
	}
}

BigInt::BigInt(int in)
{
	if (in < 0) {
		this->sign = -1;
		in *= -1;
	}
	else {
		this->sign = 1;
	}
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
	if (in < 0) {
		this->sign = -1;
		in *= -1;
	}
	else {
		this->sign = 1;
	}
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
	if (in < 0) {
		this->sign = -1;
		in *= -1;
	}
	else {
		this->sign = 1;
	}
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
	std::string newInput = "";
	this->sign = bi_old.getSign();
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

BigInt BigInt::operator-(const BigInt& bi)
{
	if (this->compare(bi) == 0) {
		return BigInt("0");
	}
	std::string answer;
	std::vector<short> localDigits = this->digits;
	std::vector<short> otherDigits = bi.getDigits();
	std::vector<short>::reverse_iterator riter = localDigits.rbegin();
	std::vector<short>::reverse_iterator riterOther = otherDigits.rbegin();
	short digit1, digit2, diff, newsign;
	unsigned int index;

	if (this->compare(bi) > 0) {		//case answer will be positive
		
		newsign = 1;
		while (riter != localDigits.rend() && riterOther != otherDigits.rend()) {
			digit1 = *riter;
			digit2 = *riterOther;
			if (digit1 >= digit2) {
				diff = digit1 - digit2;
				std::string sumstring = std::to_string(diff);
				answer = sumstring + answer;
				++riter; ++riterOther;
				continue;
			}
			else {
				index = riter - localDigits.rbegin() - 1;
				if (localDigits.at(index) > 0) {
					localDigits.at(index)--;
					diff = 10 + digit1 - digit2;
					std::string sumstring = std::to_string(diff);
					answer = sumstring + answer;
					++riter; ++riterOther;
					continue;
				}
				else {
					while (index >= 0 && localDigits.at(index) == 0) {
						this->setDigit(index, 9);
						index--;
					}
					localDigits.at(index)--;
					diff = 10 + digit1 - digit2;
					std::string sumstring = std::to_string(diff);
					answer = sumstring + answer;
					++riter; ++riterOther;
					continue;
				}
			}
		}
		while (riter != localDigits.rend()) {
			std::string sumstring = std::to_string(*riter);
			std::cout << sumstring << std::endl;
			answer = sumstring + answer;
			++riter;
		}
		while (riterOther != otherDigits.rend()) {
			std::string sumstring = std::to_string(*riterOther);
			answer = sumstring + answer;
			++riterOther;
		}
	}
	else {		// case answer will be negative
		newsign = -1;
		while (riter != localDigits.rend() && riterOther != otherDigits.rend()) {
			digit2 = *riter;
			digit1 = *riterOther;
			if (digit1 >= digit2) {
				diff = digit1 - digit2;
				std::string sumstring = std::to_string(diff);
				answer = sumstring + answer;
				++riter; ++riterOther;
				continue;
			}
			else {
				index = riter - localDigits.rbegin() - 1;
				if (localDigits.at(index) > 0) {
					localDigits.at(index)--;
					diff = 10 + digit1 - digit2;
					std::string sumstring = std::to_string(diff);
					answer = sumstring + answer;
					++riter; ++riterOther;
					continue;
				}
				else {
					while (index >= 0 && localDigits.at(index) == 0) {
						this->setDigit(index,9);
						index--;
					}
					localDigits.at(index)--;
					diff = 10 + digit1 - digit2;
					std::string sumstring = std::to_string(diff);
					answer = sumstring + answer;
					++riter; ++riterOther;
					continue;
				}
			}
		}
		while (riter != localDigits.rend()) {
			std::string sumstring = std::to_string(*riter);
			answer = sumstring + answer;
			++riter;
		}
		while (riterOther != otherDigits.rend()) {
			std::string sumstring = std::to_string(*riterOther);
			answer = sumstring + answer;
			++riterOther;
		}
		answer = '-' + answer;
	}

	return BigInt(answer.c_str());
}

void BigInt::setDigit(unsigned int& index, int val)
{
	if (val > 9 || val < 0) {
		BigIntException bie("Invalid digit value!");
		std::cout << bie.toString() << " " << bie.getWhat() << " At BigInt::setDigit(unsigned int& index, unsigned short& val)." << std::endl;
		throw bie;
	}
	this->digits.at(index) = val;
}

void BigInt::printNumber()
{
	if (this->sign == -1) {
		std::cout << "-";
	}
	for (unsigned int i = 0; i < this->getNumberOfDigits(); i++) {
		std::cout << this->getDigits().at(i);
	}
	std::cout << std::endl;
}

void BigInt::printNumber(const char* option)
{
	if (option == "raw") {
		if (this->sign == -1) {
			std::cout << "-";
		}
		for (unsigned int i = 0; i < this->getNumberOfDigits(); i++) {
			std::cout << this->getDigits().at(i);
		}
		std::cout << std::endl;
	}
	else if (option == "format") {
		if (this->sign == -1) {
			std::cout << "-";
		}
		std::string s = "";
		for (int i = this->getNumberOfDigits() - 1; i >= 0 ; i--) {
			s = std::to_string(this->getDigits().at(i)) + s;
			if (i % 3 == 0 && i != 0) {
				s = " " + s;
			}
		}
		std::cout << s << std::endl;
	}
}

short BigInt::compare(const BigInt& other) //returns 0 when equal, -1 when this<other and 1 when this>other
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

const short BigInt::getSign() const
{
	return this->sign;
}

