//�����߼� by �컪��
#include "pch.h"
#include "LogicalExpression.h"
using namespace std;



//�����߼���ʼ
void logical_expression_start()
{
	
	string infix;//��׺���ʽ
	getline(cin, infix);
	string rpolish;//��׺���ʽ
	//��һ�κϷ���У��
	if (trans_to_rpolish(infix, rpolish) == 0)
	{
		cout << "[����]�Ƿ��ı��ʽ!\n\n";
		return;
	}
	cout << endl;
	map<char, bool> assignment;//ָ��
	init_assignment(infix, assignment);//�ñ��ʽ��assignment��ʼ��
	//�ڶ��κϷ���У��
	bool result_no_use;//û�õĽ��
	if (calcu_rpolish(rpolish, assignment, result_no_use) == 0)
	{
		cout << "[����]�Ƿ��ı��ʽ!!\n\n";
		return;
	}
	//��ֵ��
	TruthTable table;
	table.create(assignment, rpolish);
	table.print_table();
	cout << rpolish << endl;
}

//�ж��Ƿ��ǲ�����
bool is_opch(char ch)
{
	if (ch == '&' || ch == '|' || ch == '!' || ch == '>' || ch == '~')
		return true;
	else
		return false;
}

//�ж��Ƿ��������Ԫ
bool is_var(char ch)
{
	if (ch >= 'a'&&ch <= 'z' || ch >= 'A'&&ch <= 'Z')
		return true;
	else
		return false;
}

//��ָ�ɳ�ʼ��
void init_assignment(string str, map<char, bool> &assignment)
{
	for (string::iterator it = str.begin(); it != str.end(); it++)
	{
		if (is_var(*it))
		{
			if (assignment.count(*it) == 0)//assignment�в�����keyΪ��ǰ��ĸ��Ԫ��
				assignment[*it] = 0;
		}
	}
}

//��׺���ʽת��Ϊ��׺���ʽ
//����1��ʾ�ɹ�������0��ʾʧ��
Status trans_to_rpolish(string infix, string &rpolish)
{
	stack<char> opchar;//�����ջ
	rpolish.clear();
	for (string::iterator it = infix.begin(); it != infix.end(); it++)
	{
		if (is_var(*it))//�������Ԫ
		{
			rpolish.push_back(*it);//ֱ�Ӽ�����ʽ
		}
		else//�������
		{
			if (*it == '(')
				opchar.push(*it);//������ֱ����ջ
			else if (*it == '!')
				opchar.push(*it);//ǰ�������ֱ����ջ
			else if (*it == ')')//�����ţ���ͣ�س�ջ
			{
				if (opchar.empty())
					return 0;//Ҫ��ջʱջΪ�գ�ʧ��
				while (opchar.top() != '(')//ֱ�����������Ų�ֹͣ
				{
					rpolish.push_back(opchar.top());
					opchar.pop();
					if (opchar.empty())
						return 0;//֮��Ҫ��ջ����ջΪ�գ�ʧ��
				}
				opchar.pop();//�����ų�ջ������
			}
			else//��ǰ�������"�ɱȽ����ȼ�"�������
			{
				if (opchar.empty())//��ջΪ�գ��Ͳ����ˣ�ֱ����ջ
					opchar.push(*it);
				else if (opchar.top() == '(')//��ջ���������ţ��Ͳ����ˣ�ֱ����ջ
					opchar.push(*it);
				else if (opchar.top() == '!')//ջ����ǰ�������
				{
					rpolish.push_back(opchar.top());
					opchar.pop();
					opchar.push(*it);
				}
				else if (logical_priority[(*it)] >= logical_priority[(opchar.top())])//��ǰ���ȼ�>=ջ�����ȼ�
				{
					opchar.push(*it);
				}
				else//��ǰ���ȼ�<ջ�����ȼ�����ͣ�س�ջ��Ȼ���Լ���ջ
				{
					if (opchar.empty())
						return 0;//Ҫ��ջʱջΪ�գ�ʧ��
					//ֱ�����������Ų�ֹͣ������������ջ��
					while ((!opchar.empty()) && opchar.top() != '(')//�˴������˶�·������ص㣬��ֹ���ջ��ջ��Ԫ�ؽ��бȽ�
					{
						rpolish.push_back(opchar.top());
						opchar.pop();
					}
					opchar.push(*it);
				}
			}
		}
	}//������׺���ʽ����
	while (!opchar.empty())//��ջ�ﻹ������������ε����������׺���ʽ
	{
		rpolish.push_back(opchar.top());
		opchar.pop();
	}
	return 1;
}

//��ָ�ɺͺ�׺���ʽ������ֵ��
void TruthTable::create(map<char, bool>assignment, string rpolish)
{
	int n = assignment.size();
	int num = (int)pow(2, n);//���棺�ӡ�double��ת������int�������ܶ�ʧ����
	for (int i = 0; i < num; i++)
	{
		map<char, bool> temp_assignment = assignment;//��ʱ���������汾�εľ���ָ��
		assign_assignment(temp_assignment, i);
		bool result;
		calcu_rpolish(rpolish, temp_assignment, result);//��ʱ���������������ֵ
		TruthTableRow row = { temp_assignment, result };//��ʱ������һ��
		rows.push_back(row);
		if (result)
			num_of_true++;
		else
			num_of_false++;
	}
}

//��ӡ��ֵ��
void TruthTable::print_table()
{
	//��ӡ��ͷ
	map<char, bool> row_assignment = rows[0].assignment;
	for (map<char, bool>::iterator it = row_assignment.begin(); it != row_assignment.end(); it++)
	{
		cout << it->first << " ";
	}
	cout << "Func" << endl;
	//��ӡ��ı���
	//һ��һ�еر�����ֵ��vec_itָ��TruthTableRow�͵ı���
	for (vector<TruthTableRow>::iterator vec_it = rows.begin(); vec_it != rows.end(); vec_it++)
	{
		map<char, bool> this_assignment = vec_it->assignment;//��ǰ�е�ָ��
		//������ǰ�е�ָ��
		for (map<char, bool>::iterator it = this_assignment.begin(); it != this_assignment.end(); it++)
		{
			cout << it->second << " ";
		}
		cout << vec_it->func_result;
		cout << endl;
	}
}

//��nת�ɶ���������ָ�ɵ�ÿ����Ԫ��ֵ
void assign_assignment(map<char, bool> &assignment, int n)
{
	queue<int> q;//���������ÿһλ��������
	do
	{
		q.push(n % 2);
		n /= 2;
	} while (n);
	//int q_size = q.size();
	//�������
	for (map<char, bool>::reverse_iterator it = assignment.rbegin(); it != assignment.rend(); it++)
	{
		if (q.empty())//������λ���������꣬���λ��ֵ0
		{
			it->second = 0;
		}
		else
		{
			int temp = q.front();
			q.pop();
			it->second = temp;
		}
	}
}

//�����׺���ʽ
//����1��ʾ�ɹ�������0��ʾʧ��
Status calcu_rpolish(string rpolish, map<char, bool> assignment, bool &result)
{
	stack<bool> var_stack;
	for (string::iterator it = rpolish.begin(); it != rpolish.end(); it++)
	{
		if (is_var(*it))//�������Ԫ
		{
			var_stack.push(assignment[(*it)]);
		}
		else//�������
		{
			if (*it == '!')//��Ŀ�����
			{
				if (var_stack.empty())
					return 0;
				bool temp = var_stack.top();
				var_stack.pop();
				var_stack.push(!temp);
			}
			else//˫Ŀ�����
			{
				if (var_stack.empty())
					return 0;
				bool rtemp = var_stack.top();//�Ҳ�����
				var_stack.pop();
				if (var_stack.empty())
					return 0;
				bool ltemp = var_stack.top();//�������
				var_stack.pop();
				bool result = calcu_two(ltemp, rtemp, *it);
				var_stack.push(result);
			}
		}
	}
	if (var_stack.size() != 1)
		return 0;
	result = var_stack.top();
	return 1;
}

//˫Ŀ������ļ���
bool calcu_two(bool left, bool right, char ch)
{
	if (ch == '&')
		return (right&&left);
	else if (ch == '|')
		return (right || left);
	else if (ch == '>')
	{
		if (left == true && right == false)
			return false;
		else
			return true;
	}
	else//ch=='~'
	{
		if (left == right)
			return true;
		else
			return false;
	}
}

//��ӡ����ȡ��ʽ
void TruthTable::print_CCNF()
{
	
}

//��ӡ����ȡ��ʽ
void TruthTable::print_CDNF()
{
}