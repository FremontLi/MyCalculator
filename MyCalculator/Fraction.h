#pragma once
//������ ͷ�ļ� 
//by �컪��
#include <string>

class Fraction
{
public:
	///----���캯��----

	Fraction();
	Fraction(int num);
	Fraction(int a, int b);
	Fraction(std::string s);
	Fraction(const char *char_s);
	Fraction(double num);

	///----��Ա����----

	//Լ�ֻ���
	Fraction simplify();

	///----��Ԫ����----

	friend Fraction add_fract(Fraction fract1, Fraction fract2);
	friend Fraction minus_fract(Fraction fract1, Fraction fract2);
	friend Fraction multiply_fract(Fraction fract1, Fraction fract2);
	friend Fraction divide_fract(Fraction fract1, Fraction fract2);

	///----���������----

	friend std::ostream& operator<< (std::ostream &out, const Fraction &num);
	friend std::istream& operator>> (std::istream &in, Fraction &num);
	friend Fraction operator+ (Fraction fract1, Fraction fract2);
	friend Fraction operator- (Fraction fract1, Fraction fract2);
	friend Fraction operator* (Fraction fract1, Fraction fract2);
	friend Fraction operator/ (Fraction fract1, Fraction fract2);
	Fraction operator- () const;
	Fraction& operator++ ();
	Fraction operator++ (int);
	Fraction& operator+= (const Fraction &fract);
	Fraction& operator-= (const Fraction &fract);
	Fraction& operator*= (const Fraction &fract);
	Fraction& operator/= (const Fraction &fract);
	friend bool operator== (const Fraction &fract1, const Fraction &fract2);
	friend bool operator!= (const Fraction &fract1, const Fraction &fract2);
	friend bool operator> (const Fraction &fract1, const Fraction &fract2);
	friend bool operator>= (const Fraction &fract1, const Fraction &fract2);
	friend bool operator< (const Fraction &fract1, const Fraction &fract2);
	friend bool operator<= (const Fraction &fract1, const Fraction &fract2);


private:
	int numerator;//����
	int denominator;//��ĸ
};

///----��������----

//�������������Ҫ��֤a��b��Ϊ�Ǹ�
int gcd(int a, int b);
//������С��������Ҫ��֤ a��b��Ϊ��
int lcm(int a, int b);

Fraction add_fract(Fraction fract1, Fraction fract2);
Fraction minus_fract(Fraction fract1, Fraction fract2);
Fraction multiply_fract(Fraction fract1, Fraction fract2);
Fraction divide_fract(Fraction fract1, Fraction fract2);

std::ostream& operator<< (std::ostream &out, const Fraction &num);
std::istream& operator>> (std::istream &in, Fraction &num);
Fraction operator+ (Fraction fract1, Fraction fract2);
Fraction operator- (Fraction fract1, Fraction fract2);
Fraction operator* (Fraction fract1, Fraction fract2);
Fraction operator/ (Fraction fract1, Fraction fract2);

bool operator== (const Fraction &fract1, const Fraction &fract2);
bool operator!= (const Fraction &fract1, const Fraction &fract2);
bool operator> (const Fraction &fract1, const Fraction &fract2);
bool operator>= (const Fraction &fract1, const Fraction &fract2);
bool operator< (const Fraction &fract1, const Fraction &fract2);
bool operator<= (const Fraction &fract1, const Fraction &fract2);