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
	BigInt operator*(const BigInt& bi);
	void setDigit(unsigned int& index, int val);
	void printNumber() const;
	void printNumber(const char* option) const;
	const short compare(const BigInt& other) const;
	bool equals(const BigInt& other) const;
	const BigInt concatZeros(int z);

	const unsigned int getNumberOfDigits() const;
	const std::vector<short> getDigits() const;
	const short getSign() const;
	const BigInt get_INT_MAX() const;
private:
	short sign;
	unsigned int numberOfDigits;
	static const BigInt INT_MAX_VAL;
	std::vector<short> digits;
};

