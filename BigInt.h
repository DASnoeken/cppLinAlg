#pragma once
#include <string_view>
#include <vector>
class BigInt
{
public:
	//Constructors
	BigInt(const char* in);
	BigInt(int in);
	BigInt(long in);
	BigInt(short in);
	BigInt(const BigInt& bi_old);

	//Operators
	BigInt operator+(const BigInt& bi);
	BigInt operator-(const BigInt& bi);
	BigInt operator*(const BigInt& bi);
	BigInt operator^(const BigInt& bi);
	BigInt operator/(const BigInt& bi);

	//Accessors
	const unsigned int getNumberOfDigits() const;
	const std::vector<short> getDigits() const;
	const short getDigit(int index) const;
	const short getSign() const;
	const BigInt get_INT_MAX() const;
	const BigInt get_INT_MIN() const;
	const BigInt get_UINT_MAX() const;
	const BigInt get_LLONG_MAX() const;
	const BigInt get_LLONG_MIN() const;
	const BigInt get_ULLONG_MAX() const;

	//Modifiers
	void setDigit(unsigned int& index, short val);

	//Converters
	long long to_LLONG();
	int to_INT();

	//Other functions
	void printNumber() const;
	void printNumber(const char* option) const;
	const short compare(const BigInt& other) const;
	bool equals(const BigInt& other) const;
	const BigInt concatZeros(int z);

	//Friends
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

