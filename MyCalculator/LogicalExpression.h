//�����߼�ͷ�ļ� by �컪��
#pragma once
#include <iostream>
#include <stack>
#include <string>
#include <map>
#include <vector>
#include <iterator>
#include <queue>
#include <cmath>

using namespace std;

//��������״̬����
typedef int Status;
//��������ȼ�
static map<char, int> logical_priority = { {'~', 1},{'>', 2},{'|',3},{'&',4},{'!',5} };

//��ֵ���һ��
struct TruthTableRow
{
	map<char, bool> assignment;//��ÿ����Ԫ�ľ���ָ��
	bool func_result;//���еĽ��
};
//��ֵ��
struct TruthTable
{
	//���캯������num_of_true��num_of_false��ʼ��Ϊ0
	TruthTable()
	{
		num_of_true = 0;
		num_of_false = 0;
	}

	//----��Ա����----

	//��ָ�ɺͺ�׺���ʽ������ֵ��
	void create(map<char, bool>assignment, string rpolish);
	//��ӡ��ֵ��
	void print_table();
	//��ӡ����ȡ��ʽ
	void print_CCNF();
	//��ӡ����ȡ��ʽ
	void print_CDNF();

	//----���ݳ�Ա----

	vector<TruthTableRow> rows;//һ��
	int num_of_true;//���Ϊ�������
	int num_of_false;//���Ϊ�ٵ�����
};

//�����߼�ģʽ
void logical_expression_mode();
//�����߼���ʼ
void logical_expression_start();

//�ж��Ƿ��ǲ�����
bool is_opch(char ch);
//�ж��Ƿ��������Ԫ
bool is_var(char ch);

//��ָ�ɳ�ʼ��
void init_assignment(string str, map<char, bool> &assignment);
//��׺���ʽת��Ϊ��׺���ʽ
//����1��ʾ�ɹ�������0��ʾʧ��
Status trans_to_rpolish(string infix, string &rpolish);
//��nת�ɶ���������ָ�ɵ�ÿ����Ԫ��ֵ
void assign_assignment(map<char, bool> &assignment, int n);
//�����׺���ʽ
//����1��ʾ�ɹ�������0��ʾʧ��
Status calcu_rpolish(string rpolish, map<char, bool> assignment, bool &result);
//˫Ŀ������ļ���
bool calcu_two(bool left, bool right, char ch);