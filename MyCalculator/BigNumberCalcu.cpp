//�򵥵Ĵ������� by �컪��
#include "pch.h"
#include "BigNumberCalcu.h"
using namespace std;

void BigNumCalcu_mode()
{
	while (true)
	{
		cout << "--------------------------------------------" << endl;
		cout << "[ָ���б�]�����Ӧ�����ּ�������Ӧ�����㣬����quit�˳���������ģʽ������cls����\n";
		cout << "0-�ӷ�\t1-����\t2-�˷�\t3-����" << endl;
		cout << "4-��\t5-����\t6-�׳�" << endl;
		cout << ">>>";
		string str;
		cin >> str;
		if (str == "0")
			BigNum_add();
		else if (str == "1")
			BigNum_minus();
		else if (str == "2")
			BigNum_multiply();
		else if (str == "3")
			BigNum_divide();
		else if (str == "4")
			BigNum_pow();
		else if (str == "5")
			BigNum_root();
		else if (str == "6")
			BigNum_fact();
		else if (str == "cls")
			system("cls");
		else if (str == "quit")
			return;
		else
		{
			cout << "[����]�޷�ʶ���ָ��\n\n";
		}
	}
}

void BigNum_add()
{
	clock_t start_t, end_t;
	double total_t;
	cout << "�����һ��������" << endl;
	string num1;
	cin >> num1;
	cout << "����ڶ���������" << endl;
	string num2;
	cin >> num2;
	cout << "�����С���" << endl;
	start_t = clock();//��ʼ��ʱ
	BigNumber result = BigNumber(num1) + BigNumber(num2);
	end_t = clock();//������ʱ
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;//ת������
	cout << "�����" << endl << result << endl;
	cout << "��ʱ��" << total_t << "��" << endl << endl;
}

void BigNum_minus()
{
	clock_t start_t, end_t;
	double total_t;
	cout << "���뱻������" << endl;
	string num1;
	cin >> num1;
	cout << "���������" << endl;
	string num2;
	cin >> num2;
	cout << "�����С���" << endl;
	start_t = clock();//��ʼ��ʱ
	BigNumber result = BigNumber(num1) - BigNumber(num2);
	end_t = clock();//������ʱ
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;//ת������
	cout << "�����" << endl << result << endl;
	cout << "��ʱ��" << total_t << "��" << endl << endl;
}

void BigNum_multiply()
{
	clock_t start_t, end_t;
	double total_t;
	cout << "�����һ��������" << endl;
	string num1;
	cin >> num1;
	cout << "����ڶ���������" << endl;
	string num2;
	cin >> num2;
	cout << "�����С���" << endl;
	start_t = clock();//��ʼ��ʱ
	BigNumber result = multiply_num(BigNumber(num1), BigNumber(num2));
	end_t = clock();//������ʱ
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;//ת������
	cout << "�����" << endl << result << endl;
	cout << "��ʱ��" << total_t << "��" << endl << endl;
}

void BigNum_divide()
{
	clock_t start_t, end_t;
	double total_t;
	cout << "���뱻������" << endl;
	string num1;
	cin >> num1;
	cout << "���������" << endl;
	string num2;
	cin >> num2;
	cout << "�����С���" << endl;
	start_t = clock();//��ʼ��ʱ
	BigNumber result = divide_num(BigNumber(num1), BigNumber(num2));
	end_t = clock();//������ʱ
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;//ת������
	cout << "���(����10λС��)��" << endl << result << endl;
	cout << "��ʱ��" << total_t << "��" << endl << endl;
}

void BigNum_fact()
{
	clock_t start_t, end_t;
	double total_t;
	cout << "����Ҫ���׳����������" << endl;
	string num;
	cin >> num;
	BigNumber bnum(num);
	if (bnum <= 0)
	{
		cout << "[����]ֻ���������������׳�\n\n";
		return;
	}
	cout << "�����С���" << endl;
	start_t = clock();//��ʼ��ʱ
	BigNumber result = factorial_num(bnum);
	end_t = clock();//������ʱ
	if (result == 0)
	{
		cout << "[����]ֻ���������������׳�\n\n";
		return;
	}
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;//ת������
	cout << "�����" << endl << result << endl;
	cout << "��ʱ��" << total_t << "��" << endl << endl;
}

void BigNum_pow()
{
	clock_t start_t, end_t;
	double total_t;
	cout << "���������" << endl;
	string num1;
	cin >> num1;
	cout << "����ָ��(ֻ֧������)��" << endl;
	string num2;
	cin >> num2;
	BigNumber bnum1(num1);
	BigNumber bnum2(num2);
	cout << "�����С���" << endl;
	start_t = clock();//��ʼ��ʱ
	BigNumber result = pow_int_index(bnum1, bnum2);
	end_t = clock();//������ʱ
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;//ת������
	cout << "���(����10λС��)��" << endl << result << endl;
	cout << "��ʱ��" << total_t << "��" << endl << endl;
}

void BigNum_root()
{
	clock_t start_t, end_t;
	double total_t;
	cout << "���뱻������(ֻ֧������)��" << endl;
	string num1;
	cin >> num1;
	cout << "���뿪���Ĵ���(ֻ֧��������)��" << endl;
	string num2;
	cin >> num2;
	BigNumber bnum1(num1);
	BigNumber bnum2(num2);
	if (bnum1 <= 0 || bnum2 <= 0)
	{
		cout << "[����]����������\n\n";
		return;
	}
	cout << "�����С���" << endl;
	start_t = clock();//��ʼ��ʱ
	BigNumber result = nth_root_int(bnum1, bnum2);
	end_t = clock();//������ʱ
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;//ת������
	cout << "���(����6λС��)��" << endl << result << endl;
	cout << "��ʱ��" << total_t << "��" << endl << endl;
}