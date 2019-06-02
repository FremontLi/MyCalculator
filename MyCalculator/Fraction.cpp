//�������ʵ�� 
//by �컪��
#include "pch.h"
#include "Fraction.h"
#include <iterator>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <cmath>
using namespace std;

///----���캯��----

Fraction::Fraction()
{
	numerator = 0;
	denominator = 1;
}

Fraction::Fraction(int num)
{
	numerator = num;
	denominator = 1;
}

Fraction::Fraction(int a, int b)
{
	if (b == 0)
		throw "��ĸ����Ϊ0 ��";
	if (a * b == 0)
		*this = Fraction(0);
	else if (a * b > 0)
	{
		numerator = abs(a);
		denominator = abs(b);
	}
	else
	{
		numerator = -abs(a);
		denominator = abs(b);
	}
	this->simplify();//Լ�ֻ���
}

Fraction::Fraction(string s)
{
	int string_type = 0;//0��ʾ������1��ʾ��С���㣬2��ʾ�������
	for (string::iterator it = s.begin(); it != s.end(); it++)
	{
		if (*it == '.')
		{
			string_type = 1;
			break;
		}
		if (*it == '/')
		{
			string_type = 2;
			break;
		}
	}
	if (string_type == 0)//������ʽ
	{
		int num = 0;
		int start = 0;//���ĸ��±꿪ʼ����
		int pos = 1;//������Ϊ1��������Ϊ-1����ʱ���һ�¾���
		if (s[0] == '-')
		{
			start = 1;//������ʱ����������
			pos = -1;
		}
		for (size_t i = start; i < s.size(); i++)
		{
			num *= 10;
			num += s[i] - '0';
		}
		*this = Fraction(num * pos);
	}
	else if (string_type == 1)//С������ʽ
	{
		int num = 0;//����������
		int start = 0;//���ĸ��±꿪ʼ����
		int pos = 1;//������Ϊ1��������Ϊ-1����ʱ���һ�¾���
		if (s[0] == '-')
		{
			start = 1;//������ʱ����������
			pos = -1;
		}
		size_t i = start;//����ѭ����Ҫ�õ���Ҫ��סλ��
		//̫���ˣ��Ժ���д
		for (; i < s.size(); i++)//��������������
		{
			if (s[i] == '.')
				break;//break��i����������
			num *= 10;//ǰ�������*10
			num += s[i] - '0';//���ϵ�ǰ����
		}
		i++;
		Fraction fract = 0;//С��������
		Fraction base(1, 10);
		for (; i < s.size(); i++)//����С��������
		{
			fract += (s[i] - '0') * base;
			base /= 10;
		}
		*this = (Fraction(num) + fract) * pos;
	}
	else//���������ʽ
	{
		int num1 = 0;//���ӵ�����
		int start = 0;//���ĸ��±꿪ʼ����
		int pos = 1;//������Ϊ1��������Ϊ-1����ʱ���һ�¾���
		if (s[0] == '-')
		{
			start = 1;//������ʱ����������
			pos = -1;
		}
		size_t i = start;//����ѭ����Ҫ�õ���Ҫ��סλ��
		//̫���ˣ��Ժ���д
		for (; i < s.size(); i++)//������ӵ�����
		{
			if (s[i] == '/')
				break;//break��i����������
			num1 *= 10;//ǰ�������*10
			num1 += s[i] - '0';//���ϵ�ǰ����
		}
		i++;
		int num2 = 0;//��ĸ������
		for (; i < s.size(); i++)//�����ĸ������
		{
			num2 *= 10;
			num2 += s[i] - '0';
		}
		*this = Fraction(num1 * pos, num2);
	}
}

Fraction::Fraction(const char *char_s)
{
	string s(char_s);
	*this = Fraction(s);
}

Fraction::Fraction(double num)
{
	string str;//��numת��Ϊ�ַ���
	stringstream ss;
	ss << setiosflags(ios::fixed);//����Ϊ����С��
	ss << setprecision(6) << num;//����6λС��
	ss >> str;
	*this = Fraction(str);
}

///----��Ա����----

//Լ�ֻ���
Fraction Fraction::simplify()
{
	if (numerator == 0)
		return *this;
	else
	{
		int gcd_num = gcd(abs(numerator), abs(denominator));
		numerator /= gcd_num;
		denominator /= gcd_num;
		return *this;
	}
}

///----��Ԫ����----

//���
Fraction add_fract(Fraction fract1, Fraction fract2)
{
	int lcm_num = lcm(fract1.denominator, fract2.denominator);//��ĸ����С�����������µķ�ĸ
	int num1 = lcm_num / fract1.denominator;//fract1���½�ͬ��num1
	int num2 = lcm_num / fract2.denominator;
	int new_numerator = fract1.numerator * num1 + fract2.numerator * num2;
	return Fraction(new_numerator, lcm_num);
}
//���
Fraction minus_fract(Fraction fract1, Fraction fract2)
{
	int lcm_num = lcm(fract1.denominator, fract2.denominator);//��ĸ����С�����������µķ�ĸ
	int num1 = lcm_num / fract1.denominator;//fract1���½�ͬ��num1
	int num2 = lcm_num / fract2.denominator;
	int new_numerator = fract1.numerator * num1 - fract2.numerator * num2;
	return Fraction(new_numerator, lcm_num);
}
//���
Fraction multiply_fract(Fraction fract1, Fraction fract2)
{
	return Fraction(fract1.numerator * fract2.numerator, fract1.denominator * fract2.denominator);
}
//���
Fraction divide_fract(Fraction fract1, Fraction fract2)
{
	return Fraction(fract1.numerator * fract2.denominator, fract1.denominator * fract2.numerator);
}

///----���������----

//��������أ������
ostream& operator<< (ostream &out, const Fraction &num)
{
	if (num.denominator == 1)
		out << num.numerator;
	else if (num.numerator == 0)
		out << 0;
	else
		out << num.numerator << "/" << num.denominator;
	return out;
}
//��������أ�������
istream& operator>> (istream &in, Fraction &fract)
{
	string str;
	if (!(in >> str))
		return in;
	fract = Fraction(str);
	return in;
}
//��������أ����+
Fraction operator+(Fraction fract1, Fraction fract2)
{
	return add_fract(fract1, fract2);
}
//��������أ����-
Fraction operator-(Fraction fract1, Fraction fract2)
{
	return minus_fract(fract1, fract2);
}
//��������أ����*
Fraction operator*(Fraction fract1, Fraction fract2)
{
	return multiply_fract(fract1, fract2);
}
//��������أ����/
Fraction operator/(Fraction fract1, Fraction fract2)
{
	return divide_fract(fract1, fract2);
}
//��������أ�ȡ�෴��-
Fraction Fraction::operator-() const
{
	Fraction temp = *this;
	temp.numerator = -temp.numerator;
	return temp;
}
//��������أ�ǰ��++
Fraction & Fraction::operator++()
{
	*this = (*this) + 1;
	return *this;
}
//��������أ�����++
Fraction Fraction::operator++(int)
{
	Fraction old = *this;
	++(*this);
	return old;
}
//��������أ�+=
Fraction & Fraction::operator+=(const Fraction & fract)
{
	*this = *this + fract;
	return *this;
}
//��������أ�-=
Fraction & Fraction::operator-=(const Fraction & fract)
{
	*this = *this - fract;
	return *this;
}
//��������أ�*=
Fraction & Fraction::operator*=(const Fraction & fract)
{
	*this = (*this) * fract;
	return *this;
}
//��������أ�/=
Fraction & Fraction::operator/=(const Fraction & fract)
{
	*this = *this / fract;
	return *this;
}

//��������� ==
bool operator==(const Fraction & fract1, const Fraction & fract2)
{
	Fraction temp = fract1 - fract2;
	if (temp.numerator == 0)
		return true;
	else
		return false;
}
//��������� !=
bool operator!=(const Fraction & fract1, const Fraction & fract2)
{
	if (!(fract1 == fract2))
		return true;
	else
		return false;
}
//��������� >
bool operator>(const Fraction & fract1, const Fraction & fract2)
{
	Fraction temp = fract1 - fract2;
	if (temp.numerator > 0)
		return true;
	else
		return false;
}
//��������� >=
bool operator>=(const Fraction & fract1, const Fraction & fract2)
{
	if (fract1 > fract2 || fract1 == fract2)
		return true;
	else
		return false;
}
//��������� <
bool operator<(const Fraction & fract1, const Fraction & fract2)
{
	if (!(fract1 >= fract2))
		return true;
	else
		return false;
}
//��������� <=
bool operator<=(const Fraction & fract1, const Fraction & fract2)
{
	if (!(fract1 > fract2))
		return true;
	else
		return false;
}


///----��������----

//���������������Ҫ��֤a��b��Ϊ��
int gcd(int a, int b)
{
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

//������С��������Ҫ��֤ a��b��Ϊ��
int lcm(int a, int b)
{
	return a * b / gcd(a, b);
}