#pragma once
#include <string_view>
#include <vector>
class BigInt
{
public:
	BigInt(const char* in);
	BigInt operator+(const BigInt& bi);
	BigInt operator-(const BigInt& bi);
	void setDigit(unsigned int& index, unsigned short& val);
	void printNumber();

	const unsigned int getNumberOfDigits() const;
	const std::vector<short> getDigits() const;
private:
	unsigned int numberOfDigits;
	std::vector<short> digits;
};

