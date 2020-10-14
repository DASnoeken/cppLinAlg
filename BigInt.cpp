#include "BigInt.h"
#include "BigIntException.h"

#include <charconv>
#include <iostream>
#include <string>
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

BigInt::BigInt(int inp)
{
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
	std::string newInput = "";
	this->sign = bi_old.getSign();
	for (unsigned int i = 0; i < bi_old.digits.size(); i++) {
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
	int newsign = 1;
	if (this->getSign() < 0 && bi.getSign() > 0) {
		return BigInt(bi) - *this;
	}
	else if (this->getSign() > 0 && bi.getSign() < 0) {
		return *this - BigInt(bi);
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
	while (riter != this->digits.rend()) {		//leftover numbers
		std::string sumstring = std::to_string(*riter);
		answer = sumstring + answer;
		++riter;
	}
	while (riterOther != otherDigits.rend()) {
		std::string sumstring = std::to_string(*riterOther);
		answer = sumstring + answer;
		++riterOther;
	}
	BigInt ans = answer.c_str();
	ans.setSign(newsign);
	return ans;
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
				index = localDigits.size() - (riter - localDigits.rbegin()) - 2;
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
						localDigits.at(index) = 9;
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

BigInt BigInt::operator*(const BigInt& bi)
{
	if (bi.equals(BigInt("0")) || this->equals(BigInt("0"))) {	//first some special simple cases
		return BigInt("0");
	}
	if (bi.equals(BigInt("1"))) {
		return *this;
	}
	else if (this->equals(BigInt("1"))) {
		return bi;
	}
	int newSign;
	if (this->sign == bi.getSign()) {
		newSign = 1;
	}
	else {
		newSign = -1;
	}
	BigInt answer("0");
	std::vector<short> otherDigits = bi.getDigits();
	std::vector<short>::reverse_iterator riter = this->digits.rbegin();
	std::vector<short>::reverse_iterator riterOther = otherDigits.rbegin();
	std::vector<BigInt> nums; nums.reserve(this->getNumberOfDigits() * bi.getNumberOfDigits());
	short digit1, digit2, product;
	std::string finNum;
	while (riter != digits.rend()) {
		riterOther = otherDigits.rbegin();
		while (riterOther != otherDigits.rend()) {
			digit1 = *riter;
			digit2 = *riterOther;
			product = digit1 * digit2;
			finNum += std::to_string(product);
			nums.emplace_back(BigInt(finNum.c_str()).concatZeros((
				riterOther - otherDigits.rbegin()) + (riter - digits.rbegin())
			));
			++riterOther;
			finNum = "";
		}
		++riter;
	}
	for (auto bi : nums) {
		bi.printNumber();
		answer = answer + bi;
	}
	return answer;
}

BigInt BigInt::operator^(const BigInt& bi)
{
	BigInt ans("1");
	for (BigInt i("0"); i.compare(bi)<0; i = i + 1) {
		ans = ans * *this;
	}
	return ans;
}

BigInt BigInt::operator/(const BigInt& bi)
{
	if (bi.equals(0)) {
		BigIntException bie("Division by 0!");
		std::cout << bie << " " << bie.getWhat() << " At BigInt::operator/(const BigInt& bi)" << std::endl;
		throw bie;
	}
	else if (this->equals(0)) {
		return 0;
	}
	else if (bi.equals(1)) {
		return *this;
	}
	else if (bi.equals(*this)) {
		return 1;
	}
	BigInt numerator = *this;
	BigInt denominator = bi;
	BigInt remainder = 0;
	BigInt ans = 0;
	if (numerator.compare(denominator) > 0) {
		while (numerator.compare(denominator) >= 0) {
			numerator = numerator - denominator;
			ans = ans + 1;
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

void BigInt::setDigit(unsigned int& index, short val)
{
	if (val > 9 || val < 0) {
		BigIntException bie("Invalid digit value!");
		std::cout << bie << " " << bie.getWhat() << " At BigInt::setDigit(unsigned int& index, unsigned short& val)." << std::endl;
		throw bie;
	}
	this->digits.at(index) = val;
}

void BigInt::setSign(short sign)
{
	this->sign = sign;
}

short BigInt::to_SHORT()
{
	if (this->compare(SHORT_MAX_VAL) == 1 || this->compare(SHORT_MIN_VAL) == -1) {
		BigIntException bie("Number out of bounds for SHORT!");
		std::cout << bie << " " << bie.getWhat() << " Minimum value = " << this->get_SHORT_MIN()
			<< "\nMax allowed value = " << this->get_SHORT_MAX()
			<< "\nYou entered: " << *this << ".\n At BigInt::to_SHORT()." << std::endl;
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

unsigned short BigInt::to_USHORT()
{
	if (this->getSign() < 0 || this->compare(USHORT_MAX_VAL) == 1) {
		BigIntException bie("Number out of bounds for USHORT!");
		std::cout << bie << " " << bie.getWhat() << "\nMax allowed value = " << this->get_SHORT_MAX()
			<< "\nYou entered: " << *this << ".\n At BigInt::to_USHORT()." << std::endl;
		throw bie;
	}
	unsigned short ans = 0;
	unsigned short tens = 1;
	for (int i = this->getNumberOfDigits() - 1; i >= 0; --i) {
		ans += ((unsigned short) this->getDigit(i) * tens);
		tens *= 10;
	}
	return ans;
}

long long BigInt::to_LLONG()
{
	if (this->compare(LLONG_MAX_VAL) == 1 || this->compare(LLONG_MIN_VAL) == -1) {
		BigIntException bie("Number out of bounds for LLONG!");
		std::cout << bie << " " << bie.getWhat() << " Minimum value = " << this->get_LLONG_MIN() 
			<< "\nMax allowed value = " << this->get_LLONG_MAX() 
			<< "\nYou entered: " << *this << ".\n At BigInt::to_LLONG()." << std::endl;
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

int BigInt::to_INT()
{
	if (this->compare(INT_MAX_VAL) == 1 || this->compare(INT_MIN_VAL) == -1) {
		BigIntException bie("Number out of bounds for INT!");
		std::cout << bie << " " << bie.getWhat() << " Minimum value = " << this->get_INT_MIN()
			<< " Max allowed value = " << this->get_INT_MAX() << "\nYou entered: " << *this
			<< ".\n At BigInt::to_INT()." << std::endl;
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

unsigned int BigInt::to_UINT()
{
	if (this->getSign() < 0 || this->compare(UINT_MAX_VAL) == 1) {
		BigIntException bie("Number out of bounds for UINT!");
		std::cout << bie << " " << bie.getWhat() << " Minimum value = 0"
			<< " Max allowed value = " << this->get_UINT_MAX() << "\nYou entered: " << *this
			<< ".\n At BigInt::to_UINT()." << std::endl;
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

unsigned long long BigInt::to_ULLONG()
{
	if (this->getSign() < 0 || this->compare(ULLONG_MAX_VAL) == 1) {
		BigIntException bie("Number out of bounds for ULLONG!");
		std::cout << bie << " " << bie.getWhat() << " Minimum value = 0"
			<< " Max allowed value = " << this->get_ULLONG_MAX() << "\nYou entered: " << *this
			<< ".\n At BigInt::to_ULLONG()." << std::endl;
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

void BigInt::printNumber() const
{
	if (this->sign == -1) {
		std::cout << "-";
	}
	for (unsigned int i = 0; i < this->getNumberOfDigits(); i++) {
		std::cout << this->getDigits().at(i);
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
		for (int i = this->getNumberOfDigits() - 1; i >= 0 ; i--) {
			s = std::to_string(this->getDigits().at(i)) + s;
			if (i % 3 == 0 && i != 0) {
				s = " " + s;
			}
		}
		std::cout << s << std::endl;
	}
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

const BigInt BigInt::get_SHORT_MAX() const
{
	return SHORT_MAX_VAL;
}

const BigInt BigInt::get_SHORT_MIN() const
{
	return SHORT_MIN_VAL;
}

const BigInt BigInt::get_USHORT_MAX() const
{
	return USHORT_MAX_VAL;
}

const BigInt BigInt::get_INT_MAX() const
{
	return INT_MAX_VAL;
}

const BigInt BigInt::get_INT_MIN() const
{
	return INT_MIN_VAL;
}

const BigInt BigInt::get_UINT_MAX() const
{
	return UINT_MAX_VAL;
}

const BigInt BigInt::get_LLONG_MAX() const
{
	return LLONG_MAX_VAL;
}

const BigInt BigInt::get_LLONG_MIN() const
{
	return LLONG_MIN_VAL;
}

const BigInt BigInt::get_ULLONG_MAX() const
{
	return ULLONG_MAX_VAL;
}

std::ostream& operator <<(std::ostream& os, const BigInt& bi) {
	if (bi.getSign() == -1) {
		os << "-";
	}
	for (unsigned int i = 0; i < bi.getNumberOfDigits(); i++) {
		os << bi.getDigits().at(i);
	}
	return os;
}
