//�л������ʵ�� by �컪��
#include "pch.h"
#include "Theme.h"
using namespace std;

void theme_mode()
{
	while (true)
	{
		cout << "[ָ���б�]������Ӧ��ָ����л����⣬����quit�˳������л�ģʽ\n\n";
		cout << "----------��ɫ����----------\n\n";
		cout << "0 = ��ɫ\t1 = ��ɫ\n";
		cout << "2 = ��ɫ\t3 = ��ɫ\n";
		cout << "4 = ��ɫ\t5 = ��ɫ\n";
		cout << endl;
		cout << "----------��ɫ����----------\n\n";
		cout << "a = ��ɫ\tb = ��ɫ\n";
		cout << "c = �Ұ�ɫ\n";
		cout << endl << ">>>";
		string str;
		cin >> str;
		if (str == "0")
		{
			system("color f1");
			cout << "[ϵͳ��ʾ]�����л��ɹ�\n\n";
			return;
		}
		else if (str == "1")
		{
			system("color f2");
			cout << "[ϵͳ��ʾ]�����л��ɹ�\n\n";
			return;
		}
		else if (str == "2")
		{
			system("color f5");
			cout << "[ϵͳ��ʾ]�����л��ɹ�\n\n";
			return;
		}
		else if (str == "3")
		{
			system("color f6");
			cout << "[ϵͳ��ʾ]�����л��ɹ�\n\n";
			return;
		}
		else if (str == "4")
		{
			system("color f4");
			cout << "[ϵͳ��ʾ]�����л��ɹ�\n\n";
			return;
		}
		else if (str == "5")
		{
			system("color f0");
			cout << "[ϵͳ��ʾ]�����л��ɹ�\n\n";
			return;
		}
		else if (str == "a")
		{
			system("color 0f");
			cout << "[ϵͳ��ʾ]�����л��ɹ�\n\n";
			return;
		}
		else if (str == "b")
		{
			system("color 8f");
			cout << "[ϵͳ��ʾ]�����л��ɹ�\n\n";
			return;
		}
		else if (str == "c")
		{
			system("color 70");
			cout << "[ϵͳ��ʾ]�����л��ɹ�\n\n";
			return;
		}
		else if (str == "quit")
		{
			cout << "[ϵͳ��ʾ]���˳������л�ģʽ\n\n";
			return;
		}
		else
		{
			cout << "[����]�޷�ʶ���ָ��\n\n";
		}
	}
}