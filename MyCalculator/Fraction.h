#pragma once
//����
#include <iostream>
#include <cmath>
using namespace std;

class Fraction
{
public:
	///----���캯��----

	Fraction();
	Fraction(int num);
	Fraction(int a, int b);

	///----��Ա����----

	//Լ�ֻ���
	Fraction simplify();

	///----��Ԫ����----

	friend Fraction add_fract(Fraction fract1, Fraction fract2);
	friend Fraction minus_fract(Fraction fract1, Fraction fract2);
	friend Fraction multiply_fract(Fraction fract1, Fraction fract2);
	friend Fraction divide_fract(Fraction fract1, Fraction fract2);

	///----���������----

	//��������أ������
	friend ostream& operator<< (ostream &out, const Fraction &num);
	//��������أ�������
	friend istream& operator>> (istream &in, Fraction &num);
	friend Fraction operator+ (Fraction fract1, Fraction fract2);
	friend Fraction operator- (Fraction fract1, Fraction fract2);
	friend Fraction operator* (Fraction fract1, Fraction fract2);
	friend Fraction operator/ (Fraction fract1, Fraction fract2);
	void operator- ();

private:
	int numerator;//����
	int denominator;//��ĸ
};

///----��������----

//�������������Ҫ��֤a��b��Ϊ�Ǹ�
int gcd(int a, int b);
//������С��������Ҫ��֤ a��b��Ϊ��
int lcm(int a, int b);