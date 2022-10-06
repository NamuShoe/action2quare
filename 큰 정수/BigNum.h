#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class BigNum
{
private:
	vector<unsigned char> num;

public:
	BigNum(string& str);
	BigNum(int n);

	size_t NumSize() const;
	unsigned char& operator[](int n);
	const unsigned char& operator[](int n) const;
	friend ostream& operator<<(ostream& out, const BigNum& a);

	friend bool operator==(BigNum const& a, BigNum const& b);
	friend bool operator!=(BigNum const& a, BigNum const& b);

	BigNum& operator+=(BigNum const& b);

	template <class T>
	BigNum& operator+(const T& b)
	{
		static_assert(is_integral<T>::value,
                      "Must be integer addition unsigned integer types.");
		static BigNum c = *this;
		c += b;
		return c;
	};

	template <class T>
	BigNum& operator*=(const T& b)
	{
		static_assert(is_integral<T>::value,
			"Must be integer addition unsigned integer types.");
		uint64_t temp, rest = 0;
		for (int i = 0; i < this->NumSize(); i++)
		{
			temp = (uint64_t)((*this)[i]) * b;
			temp += rest;
			if (temp < 10)
				rest = 0;
			else
			{
				rest = temp / 10;
				temp = temp % 10;
			}
			(*this)[i] = temp;
		}

		while (rest != 0)
		{
			num.push_back(rest % 10);
			rest /= 10;
		}
		return *this;
	}

	template <class T>
	BigNum& operator*(const T& b)
	{
		static BigNum c = *this;
		c *= b;
		return c;
	};
};