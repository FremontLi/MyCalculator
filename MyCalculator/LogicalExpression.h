#pragma once
#include <stack>
#include <map>
#include <vector>
using namespace std;



//��ֵ���һ��
struct TruthTableRow
{
	map<char, bool> assignment;
	bool func_result;
};

typedef vector<TruthTableRow> TruthTable;