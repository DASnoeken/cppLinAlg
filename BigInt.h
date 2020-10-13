#pragma once
#include <string_view>
#include <vector>
class BigInt
{
public:
	BigInt(const char* in);
	BigInt(int in);
	BigInt(long in);
	BigInt(short in);
	BigInt(const BigInt& bi_old);
	BigInt operator+(const BigInt& bi);
	BigInt operator-(const BigInt& bi);
	void setDigit(unsigned int& index, int val);
	void printNumber();
	void printNumber(const char* option);
	short compare(const BigInt& other);
	bool equals(const BigInt& other);

	const unsigned int getNumberOfDigits() const;
	const std::vector<short> getDigits() const;
	const short getSign() const;
private:
	short sign;
	unsigned int numberOfDigits;
	std::vector<short> digits;
};

