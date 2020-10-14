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
	BigInt operator^(const BigInt& bi);
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
	const BigInt get_INT_MIN() const;
	const BigInt get_UINT_MAX() const;
	const BigInt get_LLONG_MAX() const;
	const BigInt get_LLONG_MIN() const;
	const BigInt get_ULLONG_MAX() const;

	friend std::ostream& operator <<(std::ostream& os, const BigInt& bi);
private:
	short sign;
	unsigned int numberOfDigits;
	std::vector<short> digits;
	static const BigInt INT_MAX_VAL;
	static const BigInt INT_MIN_VAL;
	static const BigInt UINT_MAX_VAL;
	static const BigInt LLONG_MAX_VAL;
	static const BigInt LLONG_MIN_VAL;
	static const BigInt ULLONG_MAX_VAL;
};

