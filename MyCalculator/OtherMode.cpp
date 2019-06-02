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
			cout << "������δ���" << endl;
		else if (str == "1")
			BigNumCalcu_mode();
		else if (str == "2")
			equation_mode();
		else if (str == "3")
			logical_expression_mode();
		else if (str == "4")
			calcu_matrix();
		else if (str == "5")
			cout << "����ת��δ���" << endl;
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
	cout << "С���Ա��\n�컪�� ���� ������\n\n";
}