//�������ʽ��ֵ
//by ������
#pragma once
#include<string>
#include <queue>
struct cell {
	cell(double d)		//����Ϊdouble�Ĺ��캯��
	{
		num = d;
		type = false;
	}

	cell(char c)		//����Ϊchar�Ĺ��캯��
	{
		ch = c;
		type = true;
	}
	//���ݳ�Ա
	bool type;			//��־cell��װ������������ǲ�������true��ʾ�������
	char ch;
	double num;
};
//�ж��ַ����ͺ���������trueΪ���ţ�����falseΪ����
bool type(char a);
//stringת��Ϊdouble
double trans_string_to_double(std::string s);
//stringת��Ϊdouble
double trans_string_to_double(const char *char_s);
//��ȡtheta����Ӧ������
int getIndex(char theta);
//�ж�theta1��theta2֮������ȼ��ĺ���
char getPriority(char theta1, char theta2);
//��׳�
int fac(int x);
//���������ʽ���У������ú���
void output(std::queue<cell> q);
//�����������ʽ����ģʽ
void mathCalcuMode();
