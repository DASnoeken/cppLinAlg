#include "BigInt.h"
#include "BigIntException.h"

#include <charconv>
#include <iostream>
#include <array>

const BigInt BigInt::SHORT_MAX_VAL  = BigInt("32767");
const BigInt BigInt::SHORT_MIN_VAL  = BigInt("-32768");
const BigInt BigInt::USHORT_MAX_VAL = BigInt("65535");
const BigInt BigInt::INT_MAX_VAL    = BigInt("2147483647");
const BigInt BigInt::INT_MIN_VAL    = BigInt("-2147483648");
const BigInt BigInt::UINT_MAX_VAL   = BigInt("4294967295");
const BigInt BigInt::LLONG_MAX_VAL  = BigInt("9223372036854775807");
const BigInt BigInt::LLONG_MIN_VAL  = BigInt("-9223372036854775808");
const BigInt BigInt::ULLONG_MAX_VAL = BigInt("18446744073709551615");

const BigInt BigInt::ZERO = BigInt();
const BigInt BigInt::ONE  = BigInt("1");

BigInt::BigInt()	//Zero argument constructor, creates object with value 0.
{
	std::vector<short> s;
	s.push_back(0);
	this->base = 10; this->sign = 1; this->strRep = "0"; this->digits = s; this->numberOfDigits = 1;
}

BigInt::BigInt(const char* in)
{
	this->base = 10;
	std::string_view input(in);
	if (input.at(0) == '-') {
		this->sign = -1;
		input = std::string_view(input.data() + 1);
	}
	else {
		this->sign = 1;
	}
	while ((input.at(0) == '0' && input != "0") || input.at(0) == '.' || input.at(0) == ',' || input.at(0) == ' ') {
		input = std::string_view(input.data() + 1);
	}
	int count = 0;
	for (unsigned int i = 0; i < input.size(); i++) {
		while (input.at(i) == '.' || input.at(i) == ',' || input.at(i) == ' ') {
			count++;
			i++;
		}
	}
	this->strRep = input;
	this->numberOfDigits = input.size() - count;
	this->digits.reserve(this->numberOfDigits);
	for (unsigned int i = 0; i < this->numberOfDigits; i++) {
		while (input.at(0) == '.' || input.at(0) == ',' || input.at(0) == ' ') {
			input = std::string_view(input.data() + 1);
		}
		short s;
		std::from_chars_result fsr = std::from_chars(input.data(), input.data() + 1, s);
		input = std::string_view(input.data() + 1);
		this->digits.emplace_back(s);
	}
}

BigInt::BigInt(const char* in, short inbase)
{
	this->base = inbase;
	std::string_view input(in);
	if (input.at(0) == '-') {
		this->sign = -1;
		input = std::string_view(input.data() + 1);
	}
	else {
		this->sign = 1;
	}
	while ((input.at(0) == '0' && input != "0") || input.at(0) == '.' || input.at(0) == ',' || input.at(0) == ' ') {
		input = std::string_view(input.data() + 1);
	}
	int count = 0;
	for (unsigned int i = 0; i < input.size(); i++) {
		while (input.at(i) == '.' || input.at(i) == ',' || input.at(i) == ' ') {
			count++;
			i++;
		}
	}
	this->strRep = input;
	this->numberOfDigits = input.size() - count;
	this->digits.reserve(this->numberOfDigits);
	for (unsigned int i = 0; i < this->numberOfDigits; i++) {
		while (input.at(0) == '.' || input.at(0) == ',' || input.at(0) == ' ') {
			input = std::string_view(input.data() + 1);
		}
		short s;
		if (!isdigit(input.at(0))) {
			s = 10 + toupper(input.at(0)) - 'A';
			input = std::string_view(input.data() + 1);
			if (s > this->base) {
				std::string msg = "Invalid input for base! At BigInt::BigInt(const char* in, short inbase). Base = "
					+ std::to_string(this->base)
					+ ", but should be at least: " + std::to_string(s);
				BigIntException bie(msg.c_str());
				throw bie;
			}
		}
		else {
			std::from_chars_result fsr = std::from_chars(input.data(), input.data() + 1, s);
			input = std::string_view(input.data() + 1);
		}
		this->digits.emplace_back(s);
	}
}

BigInt::BigInt(int inp)
{
	this->base = 10;
	if (inp < 0) {
		this->sign = -1;
		inp *= -1;
	}
	else {
		this->sign = 1;
	}
	std::string s = std::to_string(inp);
	char const* pchar = s.c_str();
	std::string_view input(pchar);
	while ((input.at(0) == '0' && input != "0") || input.at(0) == '.' || input.at(0) == ',' || input.at(0) == ' ') {
		input = std::string_view(input.data() + 1);
	}
	int count = 0;
	for (unsigned int i = 0; i < input.size(); i++) {
		while (input.at(i) == '.' || input.at(i) == ',' || input.at(i) == ' ') {
			count++;
			i++;
		}
	}
	this->strRep = input;
	this->numberOfDigits = input.size() - count;
	this->digits.reserve(this->numberOfDigits);
	for (unsigned int i = 0; i < this->numberOfDigits; i++) {
		while (input.at(0) == '.' || input.at(0) == ',' || input.at(0) == ' ') {
			input = std::string_view(input.data() + 1);
		}
		short s;
		std::from_chars_result fsr = std::from_chars(input.data(), input.data() + 1, s);
		input = std::string_view(input.data() + 1);
		this->digits.emplace_back(s);
	}
}

BigInt::BigInt(long inp)
{
	this->base = 10;
	if (inp < 0) {
		this->sign = -1;
		inp *= -1;
	}
	else {
		this->sign = 1;
	}
	std::string s = std::to_string(inp);
	char const* pchar = s.c_str();
	std::string_view input(pchar);
	while ((input.at(0) == '0' && input != "0") || input.at(0) == '.' || input.at(0) == ',' || input.at(0) == ' ') {
		input = std::string_view(input.data() + 1);
	}
	int count = 0;
	for (unsigned int i = 0; i < input.size(); i++) {
		while (input.at(i) == '.' || input.at(i) == ',' || input.at(i) == ' ') {
			count++;
			i++;
		}
	}
	this->strRep = input;
	this->numberOfDigits = input.size() - count;
	this->digits.reserve(this->numberOfDigits);
	for (unsigned int i = 0; i < this->numberOfDigits; i++) {
		while (input.at(0) == '.' || input.at(0) == ',' || input.at(0) == ' ') {
			input = std::string_view(input.data() + 1);
		}
		short s;
		std::from_chars_result fsr = std::from_chars(input.data(), input.data() + 1, s);
		input = std::string_view(input.data() + 1);
		this->digits.emplace_back(s);
	}
}

BigInt::BigInt(short inp)
{
	this->base = 10;
	if (inp < 0) {
		this->sign = -1;
		inp *= -1;
	}
	else {
		this->sign = 1;
	}
	std::string s = std::to_string(inp);
	char const* pchar = s.c_str();
	std::string_view input(pchar);
	while ((input.at(0) == '0' && input != "0") || input.at(0) == '.' || input.at(0) == ',' || input.at(0) == ' ') {
		input = std::string_view(input.data() + 1);
	}
	int count = 0;
	for (unsigned int i = 0; i < input.size(); i++) {
		while (input.at(i) == '.' || input.at(i) == ',' || input.at(i) == ' ') {
			count++;
			i++;
		}
	}
	this->strRep = input;
	this->numberOfDigits = input.size() - count;
	this->digits.reserve(this->numberOfDigits);
	for (unsigned int i = 0; i < this->numberOfDigits; i++) {
		while (input.at(0) == '.' || input.at(0) == ',' || input.at(0) == ' ') {
			input = std::string_view(input.data() + 1);
		}
		short s;
		std::from_chars_result fsr = std::from_chars(input.data(), input.data() + 1, s);
		input = std::string_view(input.data() + 1);
		this->digits.emplace_back(s);
	}
}

BigInt::BigInt(const BigInt& bi_old)
{
	//std::cout << "\033[1;31mCopy constructor\033[0m" << std::endl;
	this->base = bi_old.getBase();
	this->sign = bi_old.getSign();
	this->strRep = bi_old.toString();
	std::string_view input(this->strRep);
	this->numberOfDigits = bi_old.getNumberOfDigits();
	this->digits.reserve(this->numberOfDigits + 1);
	for (unsigned int i = 0; i < this->numberOfDigits; i++) {
		short s;
		if (!isdigit(input.at(0))) {
			s = 10 + toupper(input.at(0)) - 'A';
			input = std::string_view(input.data() + 1);
			if (s > this->base) {
				std::string msg = "Invalid input for base! At BigInt::BigInt(const char* in, short inbase). Base = "
					+ std::to_string(this->base)
					+ ", but should be at least: " + std::to_string(s);
				BigIntException bie(msg.c_str());
				throw bie;
			}
		}
		else {
			std::from_chars_result fsr = std::from_chars(input.data(), input.data() + 1, s);
			input = std::string_view(input.data() + 1);
		}
		this->digits.emplace_back(s);
	}
}

BigInt::BigInt(BigInt&& bi_other) noexcept
{
	//std::cout << "\033[1;32mMove Constructor\033[0m" << std::endl;
	this->base = bi_other.getBase();
	this->sign = bi_other.getSign();
	this->digits = bi_other.getDigits();
	this->numberOfDigits = bi_other.getNumberOfDigits();
	this->strRep = bi_other.toString();
	bi_other.digits.clear();
	bi_other.numberOfDigits = 0;
	bi_other.strRep.clear();
	bi_other.base = 0;
	bi_other.sign = 0;
}

BigInt BigInt::operator+(const BigInt& bi)
{
	int newsign = 1;
	if (this->getSign() < 0 && bi.getSign() > 0) {
		BigInt tmp = *this;
		tmp.setSign(1);
		return BigInt((BigInt&&)(BigInt(bi) - tmp));
	}
	else if (this->getSign() > 0 && bi.getSign() < 0) {
		BigInt tmp = bi;
		tmp.setSign(1);
		return BigInt((BigInt&&)(*this - tmp));
	}
	else if (this->getSign() < 0 && bi.getSign() < 0) {
		newsign = -1;
	}
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
		carry = 0;								//Reset carry after using
		std::string sumstring;
		if (sum < 10) {
			sumstring = std::to_string(sum);
		}
		else if(this->base > 10) {
			char asciichar = (char)(sum - 10 + 'A');
			if (sum > this->base) {
				asciichar -= this->base;
				if (sum > this->base + 9) {
					sumstring = asciichar;
					sumstring = "1" + sumstring;
				}
				else {
					sumstring = "1" + std::to_string(sum - this->base);
				}
			}
			else {
				sumstring = asciichar;
			}
		}
		else {
			sumstring = std::to_string(sum);
		}
		if (sum < this->base) {
			answer = sumstring + answer;
		}
		else {
			std::string_view sv(sumstring);
			carry = sv.at(0) - '0'; //1
			answer = sv.at(1) + answer;
		}
		++riter;
		++riterOther;
	}
	while (riter != this->digits.rend()) {		//leftover numbers
		if (carry != 0) {
			*riter += carry;
			carry = 0;
		}
		std::string sumstring = std::to_string(*riter);
		answer = sumstring + answer;
		++riter;
	}
	while (riterOther != otherDigits.rend()) {
		if (carry != 0) {
			*riterOther += carry;
			carry = 0;
		}
		std::string sumstring = std::to_string(*riterOther);
		answer = sumstring + answer;
		++riterOther;
	}
	if (carry != 0) {
		answer = std::to_string(carry) + answer;
	}
	BigInt ans(answer.c_str(), this->base);
	ans.setSign(newsign);
	return ans;
}

BigInt BigInt::operator-(const BigInt& bi)
{
	if (this->compare(bi) == 0) {
		return ZERO;
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
				index = localDigits.size() - (riter - localDigits.rbegin()) - 2;
				if (localDigits.at(index) > 0) {
					localDigits.at(index)--;
					diff = this->base + digit1 - digit2;
					std::string sumstring = std::to_string(diff);
					answer = sumstring + answer;
					++riter; ++riterOther;
					continue;
				}
				else {
					while (index >= 0 && localDigits.at(index) == 0) {
						localDigits.at(index) = this->base - 1;
						index--;
					}
					localDigits.at(index)--;
					diff = this->base + digit1 - digit2;
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
				index = localDigits.size() - (riter - localDigits.rbegin()) - 2;
				if (localDigits.at(index) > 0) {
					localDigits.at(index)--;
					diff = this->base + digit1 - digit2;
					std::string sumstring = std::to_string(diff);
					answer = sumstring + answer;
					++riter; ++riterOther;
					continue;
				}
				else {
					while (index >= 0 && localDigits.at(index) == 0) {
						this->setDigit(index, this->base - 1);
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

BigInt BigInt::operator*(const BigInt& bi)
{
	if (bi.equals(ZERO) || this->equals(ZERO)) {	//first some special simple cases
		return ZERO;
	}
	if (bi.equals(ONE)) {
		return *this;
	}
	else if (this->equals(ONE)) {
		return bi;
	}
	int newSign;
	if (this->sign == bi.getSign()) {
		newSign = 1;
	}
	else {
		newSign = -1;
	}
	BigInt answer;
	std::vector<short> otherDigits = bi.getDigits();
	std::vector<short>::reverse_iterator riter = this->digits.rbegin();
	std::vector<short>::reverse_iterator riterOther = otherDigits.rbegin();
	std::vector<BigInt> nums(this->getNumberOfDigits() * bi.getNumberOfDigits());
	short digit1, digit2, product;
	int counter = 0;
	std::string finNum;
	while (riter != digits.rend()) {
		riterOther = otherDigits.rbegin();
		while (riterOther != otherDigits.rend()) {
			digit1 = *riter;
			digit2 = *riterOther;
			product = digit1 * digit2;
			finNum += std::to_string(product);
			BigInt backplacer = (BigInt&&) BigInt(finNum.c_str()).concatZeros((
				riterOther - otherDigits.rbegin()) + (riter - digits.rbegin()));
			nums.at(counter) = backplacer;
			++riterOther;
			finNum = "";
			++counter;
		}
		++riter;
	}
	for (unsigned int i = 0; i < nums.size(); ++i) {
		answer = BigInt((BigInt&&)(answer + nums.at(i)));
	}
	return answer;
}

BigInt BigInt::operator^(const BigInt& bi)
{
	BigInt ans(ONE);
	for (unsigned long long i = 0; i < bi.to_ULLONG(); i = i + 1) {
		ans = ans * *this;
	}
	return ans;
}

BigInt BigInt::operator/(const BigInt& bi)
{
	if (bi.equals(0)) {
		BigIntException bie("Division by 0! At BigInt::operator/(const BigInt& bi)");
		throw bie;
	}
	else if (this->equals(ZERO)) {
		return ZERO;
	}
	else if (bi.equals(ONE)) {
		return *this;
	}
	else if (bi.equals(*this)) {
		return ONE;
	}
	BigInt numerator = *this;
	BigInt denominator = bi;
	BigInt remainder = ZERO;
	BigInt ans = ZERO;
	if (numerator.compare(denominator) > 0) {
		while (numerator.compare(denominator) >= 0) {
			numerator = numerator - denominator;
			ans = ans + ONE;
		}
		remainder = numerator;
	}
	else if (numerator.compare(denominator) < 0) {
		ans = 0;
		remainder = numerator;
	}
	if (!remainder.equals(0)) {
		std::cout << "Operation: " << *this << "/" << denominator << " gave a remainder of " << remainder << std::endl;
	}
	return ans;
}

BigInt& BigInt::operator=(const BigInt& bi_other)
{
	this->base = bi_other.getBase();
	this->sign = bi_other.getSign();
	this->digits = bi_other.getDigits();
	this->numberOfDigits = bi_other.getNumberOfDigits();
	this->strRep = bi_other.toString();
	return *this;
}

bool BigInt::operator<(const BigInt& bi)
{
	if (this->compare(bi) < 0) {
		return true;
	}
	else {
		return false;
	}
}

bool BigInt::operator>(const BigInt& bi)
{
	if (this->compare(bi) > 0) {
		return true;
	}
	else {
		return false;
	}
}

bool BigInt::operator==(const BigInt& bi)
{
	if (this->compare(bi) == 0) {
		return true;
	}
	else {
		return false;
	}
}

void BigInt::setDigit(unsigned int& index, short val)
{
	if (val > this->base - 1 || val < 0) {
		BigIntException bie("Invalid digit value! At BigInt::setDigit(unsigned int& index, unsigned short& val).");
		throw bie;
	}
	this->digits.at(index) = val;
}

void BigInt::setSign(short sign)
{
	this->sign = sign;
}

short BigInt::to_SHORT() const
{
	if (this->compare(SHORT_MAX_VAL) == 1 || this->compare(SHORT_MIN_VAL) == -1) {
		std::string msg = std::string("Number out of bounds for SHORT! Minimum value = -32768\nMax allowed value = 32767\nYou entered: ")
			+ this->toString()
			+ std::string(".\n At BigInt::to_SHORT().");
		BigIntException bie(msg.c_str());
		throw bie;
	}
	short ans = 0;
	short tens = 1;
	for (int i = this->getNumberOfDigits() - 1; i >= 0; --i) {
		ans += (this->getDigit(i) * tens);
		tens *= 10;
	}
	return ans;
}

unsigned short BigInt::to_USHORT() const
{
	if (this->getSign() < 0 || this->compare(USHORT_MAX_VAL) == 1) {
		std::string msg = std::string("Number out of bounds for USHORT! Minimum value = 0\nMax allowed value = 65535\nYou entered: ")
			+ this->toString()
			+ std::string(".\n At BigInt::to_USHORT().");
		BigIntException bie(msg.c_str());
		throw bie;
	}
	unsigned short ans = 0;
	unsigned short tens = 1;
	for (int i = this->getNumberOfDigits() - 1; i >= 0; --i) {
		ans += ((unsigned short)this->getDigit(i) * tens);
		tens *= 10;
	}
	return ans;
}

long long BigInt::to_LLONG() const
{
	if (this->compare(LLONG_MAX_VAL) == 1 || this->compare(LLONG_MIN_VAL) == -1) {
		std::string msg = std::string("Number out of bounds for LLONG! Minimum value = " + LLONG_MIN_VAL.toString() + "\nMax allowed value = " + LLONG_MAX_VAL.toString() + "\nYou entered: ")
			+ this->toString()
			+ std::string(".\n At BigInt::to_LLONG().");
		BigIntException bie(msg.c_str());
		throw bie;
	}
	long long ans = 0;
	long long tens = 1;
	for (int i = this->getNumberOfDigits() - 1; i >= 0; --i) {
		ans += ((long long)this->getDigit(i) * tens);
		tens *= 10ll;
	}
	return ans;
}

int BigInt::to_INT() const
{
	if (this->compare(INT_MAX_VAL) == 1 || this->compare(INT_MIN_VAL) == -1) {
		std::string msg = std::string("Number out of bounds for INT! Minimum value = " + INT_MIN_VAL.toString() + "\nMax allowed value = " + INT_MAX_VAL.toString() + "\nYou entered: ")
			+ this->toString()
			+ std::string(".\n At BigInt::to_INT().");
		BigIntException bie(msg.c_str());
		throw bie;
	}
	int ans = 0;
	int tens = 1;
	for (int i = this->getNumberOfDigits() - 1; i >= 0; --i) {
		ans += ((int)this->getDigit(i) * tens);
		tens *= 10;
	}
	return ans;
}

unsigned int BigInt::to_UINT() const
{
	if (this->getSign() < 0 || this->compare(UINT_MAX_VAL) == 1) {
		std::string msg = std::string("Number out of bounds for UINT! Minimum value = 0\nMax allowed value = " + UINT_MAX_VAL.toString() + "\nYou entered: ")
			+ this->toString()
			+ std::string(".\n At BigInt::to_UINT().");
		BigIntException bie(msg.c_str());
		throw bie;
	}
	unsigned int ans = 0;
	unsigned int tens = 1;
	for (int i = this->getNumberOfDigits() - 1; i >= 0; --i) {
		ans += ((int)this->getDigit(i) * tens);
		tens *= 10;
	}
	return ans;
}

unsigned long long BigInt::to_ULLONG() const
{
	if (this->getSign() < 0 || this->compare(ULLONG_MAX_VAL) == 1) {
		std::string msg = std::string("Number out of bounds for ULLONG! Minimum value = 0\nMax allowed value = " + ULLONG_MAX_VAL.toString() + "\nYou entered: ")
			+ this->toString()
			+ std::string(".\n At BigInt::to_ULLONG().");
		BigIntException bie(msg.c_str());
		throw bie;
	}
	unsigned long long ans = 0;
	unsigned long long tens = 1;
	for (int i = this->getNumberOfDigits() - 1; i >= 0; --i) {
		ans += ((long long)this->getDigit(i) * tens);
		tens *= 10ll;
	}
	return ans;
}

std::string BigInt::toString() const
{
	return this->strRep;
}

BigInt BigInt::factorial(const BigInt& bi)
{
	BigInt bif = ONE;
	for (BigInt i = bi; i.compare(ONE) == 1; i = i - 1) {
		bif = bif * i;
		//std::cout << "bif = " << bif << " -- i = " << i << std::endl;
	}
	//std::cout << "\033[1;31mWARNING! DEBUG!\033[0m" << std::endl;
	return bif;
}

void BigInt::printNumber() const
{
	if (this->sign == -1) {
		std::cout << "-";
	}
	if (this->base < 10) {
		for (unsigned int i = 0; i < this->getNumberOfDigits(); i++) {
			std::cout << this->getDigit(i);
		}
	}
	else {
		for (unsigned int i = 0; i < this->getNumberOfDigits(); i++) {
			if (this->getDigit(i) < 10) {
				std::cout << this->getDigit(i);
			}
			else {
				char put = this->getDigit(i) - 10 + 'A';
				std::cout << (put);
			}
		}
	}
	std::cout << std::endl;
}

void BigInt::printNumber(const char* option) const
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
		for (int i = this->getNumberOfDigits() - 1; i >= 0; i--) {
			s = std::to_string(this->getDigits().at(i)) + s;
			if (i % 3 == 0 && i != 0) {
				s = " " + s;
			}
		}
		std::cout << s << std::endl;
	}
}

void BigInt::printDigits() const
{
	for (auto a : this->digits) {
		std::cout << a << " ";
	}
	std::cout << std::endl;
}

const short BigInt::compare(const BigInt& other) const //returns 0 when equal, -1 when this<other and 1 when this>other
{
	if (this->getSign() > other.getSign()) {
		return 1;
	}
	else if (this->getSign() < other.getSign()) {
		return -1;
	}
	if (this->getDigits().size() != other.getDigits().size()) {
		if (this->getNumberOfDigits() < other.getNumberOfDigits())
			return -1;
		else if (this->getNumberOfDigits() > other.getNumberOfDigits())
			return 1;
	}
	else {
		for (unsigned int i = 0; i < this->getNumberOfDigits(); i++) {
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

bool BigInt::equals(const BigInt& other) const
{
	if (this->getSign() != other.getSign()) {
		return false;
	}
	if (this->getDigits().size() != other.getDigits().size()) {
		return false;
	}
	for (unsigned int i = 0; i < this->getNumberOfDigits(); i++) {
		if (this->getDigits().at(i) != other.getDigits().at(i)) {
			return false;
		}
		else {
			continue;
		}
	}
	return true;
}

const BigInt BigInt::concatZeros(int z)
{
	std::string ans;
	ans.reserve(this->numberOfDigits + z);
	for (auto s : this->digits) {
		ans += std::to_string(s);
	}
	for (int i = 0; i < z; i++) {
		ans += "0";
	}
	return BigInt(ans.c_str());
}

const unsigned int BigInt::getNumberOfDigits() const
{
	return this->numberOfDigits;
}

const std::vector<short> BigInt::getDigits() const
{
	return this->digits;
}

const short BigInt::getDigit(int index) const
{
	return this->getDigits().at(index);
}

const short BigInt::getSign() const
{
	return this->sign;
}

const short BigInt::getBase() const
{
	return this->base;
}

const BigInt& BigInt::get_SHORT_MAX() const
{
	return SHORT_MAX_VAL;
}

const BigInt& BigInt::get_SHORT_MIN() const
{
	return SHORT_MIN_VAL;
}

const BigInt& BigInt::get_USHORT_MAX() const
{
	return USHORT_MAX_VAL;
}

const BigInt& BigInt::get_INT_MAX() const
{
	return INT_MAX_VAL;
}

const BigInt& BigInt::get_INT_MIN() const
{
	return INT_MIN_VAL;
}

const BigInt& BigInt::get_UINT_MAX() const
{
	return UINT_MAX_VAL;
}

const BigInt& BigInt::get_LLONG_MAX() const
{
	return LLONG_MAX_VAL;
}

const BigInt& BigInt::get_LLONG_MIN() const
{
	return LLONG_MIN_VAL;
}

const BigInt& BigInt::get_ULLONG_MAX() const
{
	return ULLONG_MAX_VAL;
}

std::ostream& operator <<(std::ostream& os, const BigInt& bi) {
	if (bi.getSign() == -1) {
		os << "-";
	}
	if (bi.getBase() <= 10) {
		for (unsigned int i = 0; i < bi.getNumberOfDigits(); i++) {
			os << bi.getDigits().at(i);
		}
	}
	else {
		for (unsigned int i = 0; i < bi.getNumberOfDigits(); i++) {
			if (bi.getDigits().at(i) < 10) {
				os << bi.getDigits().at(i);
			}
			else {
				char put = bi.getDigits().at(i) - 10 + 'A';
				os << (put);
			}
		}
	}
	return os;
}