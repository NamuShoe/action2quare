#include "BigNum.h"

BigNum::BigNum(string& str)
{
	for (size_t i = str.length(); i > 0; i--)
	{
		char a = str[i - 1] - '0';
		if (9 >= a && a >= 0)
			num.push_back(a);
	}
}

BigNum::BigNum(int n)
{
	if (n < 0)
		n = -n;
	int temp = n;
	do
	{
		num.push_back(temp % 10);
		temp /= 10;
	} while (temp != 0);
}

size_t BigNum::NumSize() const
{
	return num.size();
}

unsigned char& BigNum::operator[](int n)
{
	return this->num[n];
}

const unsigned char& BigNum::operator[](int n) const
{
		return this->num[n];
}

ostream& operator<<(ostream& out, const BigNum& a) {
	for (size_t i = a.NumSize(); i > 0; i--)
		out << (int)a[i - 1];
	return out;
}

bool operator==(BigNum const& a, BigNum const& b)
{
	if (a.NumSize() != b.NumSize())
		return false;

	for (int i = 0; i < a.num.size(); i++)
		if (a[i] != b[i])
			return false;

	return true;
}

bool operator!=(BigNum const& a, BigNum const& b)
{
	return !(a == b);
}

BigNum& BigNum::operator+=(BigNum const& b)
{
	const size_t MAX = max(this->NumSize(), b.NumSize());
	int temp = 0;

	for (int i = 0; i < MAX || temp != 0; i++)
	{
		if (i < this->NumSize())
			temp += (*this)[i];
		if (i < b.NumSize())
			temp += b[i];

		if (i < this->NumSize())
			(*this)[i] = temp % 10;
		else
			this->num.push_back(temp % 10);
		temp /= 10;
	}

	return *this;
}