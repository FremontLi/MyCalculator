#pragma once
//����
#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <iomanip>
using namespace std;

static const int PRECISION = 10;//������С��λ
//static const int BASE = 100000000;

//�߾���ʵ������
class BigNumber
{
public:
	///----���캯��----

	//�޲����Ĺ��캯��
	BigNumber();
	//����Ϊint�Ĺ��캯��
	BigNumber(int num);
	//����Ϊdouble�Ĺ��캯��
	BigNumber(double num);
	//����Ϊstring�Ĺ��캯��
	BigNumber(const string &num);
	//����Ϊchar *�Ĺ��캯��
	BigNumber(const char *num);

	///----��Ա����----

	//��������0�����¼��㳤�ȣ�˳������ȫ0���ķ���
	void clean_zero();
	//����С��
	void accuracy(int precision = PRECISION);
	//����෴��
	void set_opposite();
	//�ƶ������ֵ�С����
	//direction 0Ϊ��1Ϊ�ң�place��ʾ�ƶ���λ
	void move_dot(bool direction, unsigned int place);
	//����ת���ɵ�����
	long long  get_int() const;
	//����ת���ɵ�ʵ��
	long double get_real() const;

	///----��Ԫ����----

	//���ؾ���ֵ
	friend BigNumber abs(const BigNumber &num);
	//�Ƚ��������ľ���ֵ��num1�󷵻�1��num2�󷵻�-1����ȷ���0
	friend int cmp_abs(const BigNumber &num1, const BigNumber &num2);
	//������������ֵ֮��
	friend BigNumber add_abs(const BigNumber &num1, const BigNumber &num2);
	//������������ֵ֮�����Ǹ���
	friend BigNumber minus_abs(const BigNumber &num1, const BigNumber &num2);
	//��������������
	friend BigNumber divide_exactly(const BigNumber &num1, const BigNumber &num2);
	//����������ȡ��
	friend BigNumber rem_num(const BigNumber &num1, const BigNumber &num2);
	//��������֮��
	friend BigNumber add_num(const BigNumber &num1, const BigNumber &num2);
	//��������֮��
	friend BigNumber minus_num(const BigNumber &num1, const BigNumber &num2);
	//��������֮��
	friend BigNumber multiply_num(const BigNumber &num1, const BigNumber &num2);
	//��������֮�̣�precision�Ǳ�����С��λ��
	friend BigNumber divide_num(const BigNumber &num1, const BigNumber &num2, int precision);
	//�������Ľ׳�
	friend BigNumber factorial_num(const BigNumber &num);
	//���������������ݣ�base�ǵ�����index��ָ��
	//index����Ϊ����,��index�ᱻת����long long
	friend BigNumber pow_int_index(const BigNumber &base, const BigNumber &index);
	//�������������ο���
	//degree����Ϊ����,��degree�ᱻת����int
	friend BigNumber nth_root_int(const BigNumber &radicand, const BigNumber &degree);

	///----���������----

	//��������أ������
	friend ostream& operator<< (ostream &out, const BigNumber &num);
	//��������أ�������
	friend istream& operator>> (istream &in, BigNumber &num);
	//��������أ��е�==
	friend bool operator== (const BigNumber &num1, const BigNumber &num2);
	//��������أ�������!=
	friend bool operator!= (const BigNumber &num1, const BigNumber &num2);
	//��������أ�����>
	friend bool operator> (const BigNumber &num1, const BigNumber &num2);
	//��������أ�С��<
	friend bool operator< (const BigNumber &num1, const BigNumber &num2);
	//��������أ����ڵ���>=
	friend bool operator>= (const BigNumber &num1, const BigNumber &num2);
	//��������أ�С�ڵ���<=
	friend bool operator<= (const BigNumber &num1, const BigNumber &num2);
	//��������أ����+
	friend BigNumber operator+ (const BigNumber &num1, const BigNumber &num2);
	//��������أ����-
	friend BigNumber operator- (const BigNumber &num1, const BigNumber &num2);
	//��������أ����*(����PRECISIONλС��)
	friend BigNumber operator* (const BigNumber &num1, const BigNumber &num2);
	//��������أ����/(����PRECISIONλС��)
	friend BigNumber operator/ (const BigNumber &num1, const BigNumber &num2);
	//��������أ�ȡ��%
	friend BigNumber operator% (const BigNumber &num1, const BigNumber &num2);
	//��������أ�ȡ�෴��-
	void operator- ();
	//��������أ�ǰ��++
	BigNumber& operator++ ();
	//��������أ�����++
	BigNumber operator++ (int);
	//��������أ�+=
	BigNumber& operator+= (const BigNumber &num);
	//��������أ�-=
	BigNumber& operator-= (const BigNumber &num);
	//��������أ�*=
	BigNumber& operator*= (const BigNumber &num);
	//��������أ�/= ����������������
	BigNumber& operator/= (const BigNumber &num);
	//��������أ�%=
	BigNumber& operator%= (const BigNumber &num);

private:
	vector<int> integer;//�������֣�����
	vector<int> decimal;//С�����֣�˳��
	int int_len;//����λ��
	int dec_len;//С��λ��
	char pos;//'+'��ʾ������'-'��ʾ������'0'��ʾ0
};

BigNumber divide_num(const BigNumber &num1, const BigNumber &num2, int precision = PRECISION);