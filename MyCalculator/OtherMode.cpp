#include "pch.h"
#include "OtherMode.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include "BigNumberCalcu.h"
#include "Equation.h"
#include "LogicalExpression.h"
#include "Theme.h"
#include "Matrix.h"
#include "NumberTrans.h"
#include "MathCalculator.h"
using namespace std;

//ģʽ�л�
void switch_mode()
{
	while (true)
	{
		cout << "--------------------------------------------" << endl;
		cout << "���๦�ܼ�������" << endl;
		cout << "[ָ���б�]����ָ�������Ӧ����\n\n";
		cout << "0-������ 1-�������� 2-�����Է�����\n\n3-�����߼����� 4-��������� 5-���ơ�����ת��\n\n6-�л�������ɫ 7-��������\n\ncls-���� quit-�˳�����\n\n";
		cout << ">>>";
		string str;
		cin >> str;
		if (str == "0")
			use_mathCalcuMode();
		else if (str == "1")
			BigNumCalcu_mode();
		else if (str == "2")
			equation_mode();
		else if (str == "3")
			logical_expression_mode();
		else if (str == "4")
			calcu_matrix();
		else if (str == "5")
			my_trans_func();
		else if (str == "6")
			theme_mode();
		else if (str == "7")
			about_mode();
		else if (str == "cls")
			system("cls");
		else if (str == "quit")
			return;
		else
			cout << "[����]�޷�ʶ���ָ��\n\n";
	}
}

void about_mode()
{
	cout << "--------------------------------------------" << endl;
	cout << "С��������\\u4f18\\u79c0 \n";
	cout << "С���Ա��\n�鳤���컪�� ��Ա������ ������\n\n";
}

void use_mathCalcuMode()
{
	while (true)
	{
		cout << "--------------------------------------------" << endl;
		cout << "[ָ���б�]����start���ɿ�ʼ������quit�˳�������ģʽ������cls����" << endl;
		cout << ">>>";
		string str;
		cin >> str;
		if (str == "start")
		{
			cout << endl;
			mathCalcuMode();
		}
		else if (str == "quit")
		{
			cout << "[ϵͳ��ʾ]���˳������߼�ģʽ" << endl << endl;
			return;
		}
		else if (str == "cls")
		{
			system("cls");
		}
		else
		{
			cout << "[����]�޷�ʶ���ָ��" << endl;
		}
		cout << endl;
	}
}