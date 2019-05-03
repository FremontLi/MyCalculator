#pragma once
//���Է�����
#include <vector>
#include "Fraction.h"
#include <algorithm>
#include <map>

typedef Fraction elem;//�����Ԫ��
typedef int Status;//����״̬
typedef vector<vector<elem>> VectorGroup;//������
enum EquationType
{	homo, //���
	inhomo//�����
};//�����������

struct Equation
{
	//���캯��,����m��n�еĶ�άvector
	Equation(int m, int n);
	
	///----��Ա����----

	///----�����б任----

	//���±��i�мӵ��±��j��
	void add_i_to_j(int i, int j);
	//�±��i�б��k��
	void row_i_multiple_k(int i, Fraction k);
	//���±��i�г�k�ӵ��±��j��
	void add_ki_to_j(int i, Fraction k, int j);
	//�����±��i�к��±��j��
	void swap_i_j(int i, int j);

	//��ӡ�������
	void print_matrix() const;
	//��Ϊ�м򻯽�����
	void trans_to_stair();
	//���±��i�е��±��k��Ԫ�ػ�Ϊ1�����໯Ϊ0
	//����0��ʾ����ȫ0,����1��ʾ���з�ȫ0
	Status col_i_k_th(int i, int k);
	//����
	void calculate_rank();

	//��η�������⣬��ans���������
	//����0��ʾֻ��0�⣬����1��ʾ��������
	Status solve_homo(VectorGroup &ans) const;
	//����η�������⣬��ans���������
	//����-1��ʾ�޽⣬����0��ʾ��Ψһ�⣬����1��ʾ��������
	Status solve_inhomo(vector<elem> &ans_te, VectorGroup &ans_tong) const;
	void solve();
	///----���ݳ�Ա----

	//�������,��̬��ά����
	vector<vector<elem>> vec;
	int rows;//������������
	int cols;//������������
	EquationType type;//�����������
	int xi_shu_rank;//ϵ���������
	int zeng_guang_rank;//����������
};

//�����������
Equation scan_matrix(int m, int n);