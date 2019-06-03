//��������� ͷ�ļ�
//by ����
#pragma once

#include "Fraction.h"
typedef Fraction MElem;

//���ﶨ�����ࣺ���� ����������������
class Tableau {
public:
	Tableau(int newa, int newb);//�������캯��
	~Tableau();					  //������������					  
	Tableau(const Tableau &t);//�������ƹ��캯��

	int setTableau();//������ʼ�������е�Ԫ�صĺ���
	void getTableau() const;//�����Ծ�����ʽ�������ĺ���
	int geta() const;//���ؾ��������
	int getb() const;//���ؾ��������
	Tableau& operator= (const Tableau &t);//����=�������ʵ�����

	//���±��i�мӵ���j��
	void add_i_to_j(int i, int j);
	//�±��i�б��k��
	void row_i_multiple_k(int i, MElem k);
	//���±��i�г�k�ӵ���j��
	void add_ki_to_j(int i, MElem k, int j);
	//�����±��i�к͵�j��
	void swap_i_j(int i, int j);

	///----���ݳ�Ա----

	MElem **sz;//��ά����
private:
	int a;//����
	int b;//����

};

//����ļӷ�
void add();
//����ļ���
void subtract();
//��������ʽ�����ؼ�����
MElem calculateDet(int n, MElem** d);
//���ü�������ʽ�ĺ���
void getDet();
//����t�����ת�þ���
Tableau return_trans(const Tableau &t);
//������������û�������󲢵��ú���return_trans�����о����ת��
void getTransposition();
//����˷�
Tableau mul();
//���û�������󣬲���������
void getinverse();
//��t��Ϊ��λ�󣬵�λ��e�ͱ��������
//���뱣֤t�ǿ�����
void trans_to_I(Tableau &t, Tableau &e);
//��t�����±��i�е��±��k��Ԫ�ػ�Ϊ1������Ԫ�ػ�Ϊ0
 //��e������ͬ���ı任
 //���뱣֤t�ǿ�����
void col_i_k_th(int i, int k, Tableau &t, Tableau &e);
//���첢����һ��n�׵�λ��
Tableau create_I(int n);
//���þ�������ĺ���
void calcu_matrix();