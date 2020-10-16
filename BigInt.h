#pragma once
#include <string_view>
#include <vector>
class BigInt
{
public:
	//Constructors
	BigInt();
	BigInt(const char* in);
	BigInt(const char* in, short inbase);
	BigInt(int in);
	BigInt(long in);
	BigInt(short in);
	BigInt(const BigInt& bi_old);
	BigInt(BigInt&& bi_other) noexcept;

	//Operators
	BigInt operator+(const BigInt& bi);
	BigInt operator-(const BigInt& bi);
	BigInt operator*(const BigInt& bi);
	BigInt operator^(const BigInt& bi);
	BigInt operator/(const BigInt& bi);
	BigInt& operator=(const BigInt& bi_other);

	//Accessors
	const unsigned int getNumberOfDigits() const;
	const std::vector<short> getDigits() const;
	const short getDigit(int index) const;
	const short getSign() const;
	const short getBase() const;
	const BigInt& get_SHORT_MAX() const;
	const BigInt& get_SHORT_MIN() const;
	const BigInt& get_USHORT_MAX() const;
	const BigInt& get_INT_MAX() const;
	const BigInt& get_INT_MIN() const;
	const BigInt& get_UINT_MAX() const;
	const BigInt& get_LLONG_MAX() const;
	const BigInt& get_LLONG_MIN() const;
	const BigInt& get_ULLONG_MAX() const;

	//Modifiers
	void setDigit(unsigned int& index, short val);
	void setSign(short sign);

	//Converters
	short to_SHORT() const;
	unsigned short to_USHORT() const;
	long long to_LLONG() const;
	int to_INT() const;
	unsigned int to_UINT() const;
	unsigned long long to_ULLONG() const;
	std::string toString() const;

	//Other functions
	void printNumber() const;
	void printNumber(const char* option) const;
	void printDigits() const;
	const short compare(const BigInt& other) const;
	bool equals(const BigInt& other) const;
	const BigInt concatZeros(int z);

	//Friends
	friend std::ostream& operator <<(std::ostream& os, const BigInt& bi);

private:
	short sign;
	unsigned int numberOfDigits;
	std::vector<short> digits;
	short base;
	std::string strRep;

	//constants
	static const BigInt SHORT_MAX_VAL;
	static const BigInt SHORT_MIN_VAL;
	static const BigInt USHORT_MAX_VAL;
	static const BigInt INT_MAX_VAL;
	static const BigInt INT_MIN_VAL;
	static const BigInt UINT_MAX_VAL;
	static const BigInt LLONG_MAX_VAL;
	static const BigInt LLONG_MIN_VAL;
	static const BigInt ULLONG_MAX_VAL;
	static const BigInt ZERO;
	static const BigInt ONE;
};

