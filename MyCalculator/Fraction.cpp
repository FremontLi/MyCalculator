#include "pch.h"
#include "Fraction.h"

///----���캯��----

Fraction::Fraction()
{
	numerator = 0;
	denominator = 0;
}

Fraction::Fraction(int num)
{
	numerator = num;
	denominator = 1;
}

Fraction::Fraction(int a, int b)
{
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
	this->simplify();
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
	int num;
	if (!(in >> num))
		return in;
	fract = Fraction(num);
	return in;
}

Fraction operator+(Fraction fract1, Fraction fract2)
{
	return add_fract(fract1, fract2);
}

Fraction operator-(Fraction fract1, Fraction fract2)
{
	return minus_fract(fract1, fract2);
}

Fraction operator*(Fraction fract1, Fraction fract2)
{
	return multiply_fract(fract1, fract2);
}

Fraction operator/(Fraction fract1, Fraction fract2)
{
	return divide_fract(fract1, fract2);
}

void Fraction::operator-()
{
	numerator = -numerator;
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