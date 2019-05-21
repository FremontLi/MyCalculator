//���Է����� by �컪��
#include "pch.h"
#include "Fraction.h"
#include "Equation.h"
using namespace std;

//���캯��,����m��n�еĶ�άvector
Equation::Equation(int m, int n)
{
	rows = m;
	cols = n;
	vec.resize(m);
	for (int i = 0; i < m; i++)
		vec[i].resize(n);
}

///----��Ա����----

///----�����б任----

//�ѵ�i�мӵ���j��
void Equation::add_i_to_j(int i, int j)
{
	for (int a = 0; a < cols; a++)
	{
		vec[j][a] = vec[j][a] + vec[i][a];
	}
}
//��i�б��k��
void Equation::row_i_multiple_k(int i, Fraction k)
{
	for (int a = 0; a < cols; a++)
	{
		vec[i][a] = vec[i][a] * k;
	}
}
//�ѵ�i�г�k�ӵ���j��
void Equation::add_ki_to_j(int i, Fraction k, int j)
{
	for (int a = 0; a < cols; a++)
	{
		vec[j][a] = vec[j][a] + k * vec[i][a];
	}
}
//������i�к͵�j��
void Equation::swap_i_j(int i, int j)
{
	for (int a = 0; a < cols; a++)
	{
		swap(vec[i][a], vec[j][a]);
	}
}


//��ӡ�������
void Equation::print_matrix() const
{
	int m = rows;
	int n = cols;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << vec[i][j] << " ";
		}
		cout << endl;
	}
}

//��ϵ������Ϊ�м򻯽�����
void Equation::trans_to_stair()
{
	//ϵ�����ÿһ��
	//now_col��ʾ��ǰ���±�
	int k = 0;
	for (int now_col = 0; now_col < cols - 1; now_col++)
	{
		if (k > rows - 1)
			break;
		if(this->col_i_k_th(now_col, k) != 0)
			k++;
	}
}
//���±��i�е��±��k��Ԫ�ػ�Ϊ1�����໯Ϊ0
//����0��ʾ����ȫ0,����1��ʾ���з�ȫ0
Status Equation::col_i_k_th(int i, int k)
{
	if (vec[k][i] == 0)//����λ��Ϊ0,�����Ի�
	{
		bool flag = false;//�Ƿ����жԻ�
		for (int a = k+1; a < rows; a++)
		{
			if (vec[a][i] != 0)
			{
				this->swap_i_j(a, k);
				flag = true;
				break;
			}
		}
		if (!flag)
			return 0;
	}//if
	this->row_i_multiple_k(k, 1 / vec[k][i]);//��Ϊ1
	for (int a = 0; a < rows; a++)
	{
		if (a != k)
		{
			this->add_ki_to_j(k, -vec[a][i], a);
		}
	}
	return 1;
}

//����
void Equation::calculate_rank()
{
	//��������������
	zeng_guang_rank = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (vec[i][j] != 0)
			{
				zeng_guang_rank++;
				break;
			}
		}
	}
	//����ϵ���������
	xi_shu_rank = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols - 1; j++)
		{
			if (vec[i][j] != 0)
			{
				xi_shu_rank++;
				break;
			}
		}
	}
}

//��η�������⣬��ans���������
//����0��ʾֻ��0�⣬����1��ʾ��������
Status Equation::solve_homo(VectorGroup &ans) const
{
	//ϵ������ȵ���ϵ�����������ֻ��0��
	if (xi_shu_rank == cols - 1)
	{
		ans.resize(1);//����һ���������Ŀռ�
		ans[0].resize(cols - 1, 0);//����������cols - 1����Ԫ
		return 0;
	}
	//��������
	else
	{
		//���ɱ�Ԫ�ĸ���
		int free = cols - 1 - xi_shu_rank;
		//���������н������ĸ���
		ans.resize(free);
		for (int i = 0; i < free; i++)
			ans[i].resize(cols - 1);//����������cols - 1����Ԫ

		//��¼˭��Լ����Ԫ��˭�����ɱ�Ԫ
		//0��ʾ���ɱ�Ԫ��1��ʾԼ����Ԫ
		vector<bool> record;
		record.resize(cols - 1, 0);//����ռ䲢��ʼ��Ϊ0
		//ÿ�е�һ����0Ԫ���ڵ��ж�Ӧ����Լ����Ԫ
		for (int i = 0; i < xi_shu_rank; i++)
		{
			for (int j = 0; j < cols - 1; j++)
			{
				if (vec[i][j] != 0)
				{
					record[j] = 1;
					break;
				}
			}
		}

		map<int, int> record2;//��¼�����ɱ�Ԫ�ǵڼ������ɱ�Ԫ����0��ʼ������
		int n = 0;//�ڼ������ɱ�Ԫ
		for (int i = 0; i < cols - 1; i++)
		{
			if (record[i] == 0)
			{
				record2[i] = n;
				n++;
			}
		}


		//��a�֣���0��ʼ���������±�Ϊa�Ľ�����
		//��a�����Ͱѵ�a�����ɱ�Ԫָ��Ϊ1���������ɱ�Ԫָ��Ϊ0
		for (int a = 0; a < free; a++)
		{
			//���±��i����Ԫ
			for (int i = 0; i < cols - 1; i++)
			{
				//�±��i�ı�Ԫ�����ɱ�Ԫ
				if (record[i] == 0)
				{
					//�����ɱ�Ԫȡ1��ȡ0
					if (record2[i] == a)
						ans[a][i] = 1;
					else
						ans[a][i] = 0;
				}
				else//�±��i�ı�Ԫ��Լ����Ԫ
				{
					//Ѱ���±��i�з�0Ԫ��ֵΪ1�����ڵ��к�
					int at_row = 0;//�����к�
					for (int r = 0; r < rows; r++)
					{
						if (vec[r][i] != 0)
						{
							at_row = r;
							break;
						}
					}
					Fraction temp = vec[at_row][cols - 1];
					//�±�at_row�е��±��j����Ԫ
					for (int j = i; j < cols - 1; j++)
					{
						//�ñ�Ԫ�����ɱ�Ԫ�����ڴ�������б�ָ��Ϊ1
						if (record[j] == 0 && record2[j] == a)
							temp -= vec[at_row][j];
					}
					ans[a][i] = temp;
				}
			}
		}
		return 1;
	}
}

//����η�������⣬��ans���������
//����-1��ʾ�޽⣬����0��ʾ��Ψһ�⣬����1��ʾ��������
Status Equation::solve_inhomo(vector<elem> &ans_te, VectorGroup &ans_tong) const
{
	//ϵ��������������������Ȳ���ȣ��޽�
	if (xi_shu_rank != zeng_guang_rank)
		return -1;
	//ϵ������ȵ���ϵ�������������Ψһ��
	if (xi_shu_rank == cols - 1)
	{
		//ans.resize(1);//����һ���������Ŀռ�
		for (int i = 0; i < cols - 1; i++)////����������cols - 1����Ԫ
		{
			ans_te.push_back(vec[i][cols - 1]);
		}
		return 0;
	}
	//��������
	else
	{
		Equation dao_chu_zu = *this;//������
		for (int i = 0; i < rows; i++)
			dao_chu_zu.vec[i][rows] = 0;
		dao_chu_zu.solve_homo(ans_tong);

		//������������ֲ����

		//���ɱ�Ԫ�ĸ���
		int free = cols - 1 - xi_shu_rank;
		ans_te.resize(cols - 1);//����������cols - 1����Ԫ

		//��¼˭��Լ����Ԫ��˭�����ɱ�Ԫ
		//0��ʾ���ɱ�Ԫ��1��ʾԼ����Ԫ
		vector<bool> record;
		record.resize(cols - 1, 0);//����ռ䲢��ʼ��Ϊ0
		//ÿ�е�һ����0Ԫ���ڵ��ж�Ӧ����Լ����Ԫ
		for (int i = 0; i < xi_shu_rank; i++)
		{
			for (int j = 0; j < cols - 1; j++)
			{
				if (vec[i][j] != 0)
				{
					record[j] = 1;
					break;
				}
			}
		}

		//���±��i����Ԫ
		for (int i = 0; i < cols - 1; i++)
		{
			//�±��i�ı�Ԫ�����ɱ�Ԫ
			if (record[i] == 0)
			{
				ans_te[i] = 0;
			}
			else//�±��i�ı�Ԫ��Լ����Ԫ
			{
				//Ѱ���±��i�з�0Ԫ��ֵΪ1�����ڵ��к�
				int at_row = 0;//�����к�
				for (int r = 0; r < rows; r++)
				{
					if (vec[r][i] != 0)
					{
						at_row = r;
						break;
					}
				}
				Fraction temp = vec[at_row][cols - 1];
				ans_te[i] = temp;
			}
		}
		return 1;
	}
}

//��Ⲣ��ӡ
void Equation::solve()
{
	this->trans_to_stair();
	this->calculate_rank();
	if (this->type == homo)//���
	{
		VectorGroup ans;
		if(this->solve_homo(ans) == 1)//��������
		{
			cout << "����η�������������" << endl;
			cout << "����һ��ͨ��Ϊ��" << endl;
			cout << "X = ";
			int size = ans.size();//�������ĸ���
			int num = ans[0].size();//һ����������Ԫ�صĸ���
			for (int i = 0; i < size; i++)
			{
				cout << "k" << i + 1 << "(";
				for (int j = 0; j < num; j++)
				{
					cout << ans[i][j];
					if (j < num - 1)
						cout << ", ";
				}
				cout << ")";
				if (i < size - 1)
					cout << " + ";
			}
			cout << endl;
		}
		else//ֻ�����
		{
			cout << "����η�����ֻ�����" << endl;
			cout << "X = (";
			for (size_t i = 0; i < ans[0].size(); i++)
			{
				cout << "0";
				if (i < ans[0].size() - 1)
					cout << ", ";
			}
			cout << ")" << endl;
		}
	}
	else//�����
	{
		vector<elem> ans_te;
		VectorGroup ans_tong;
		int status = this->solve_inhomo(ans_te, ans_tong);
		if (status == -1)
			cout << "�÷���η������޽�" << endl;
		else if (status == 0)
		{
			cout << "�÷���η�������Ψһ��" << endl;
			cout << "X = (";
			int num = ans_te.size();
			for (int i = 0; i < num; i++)
			{
				cout << ans_te[i];
				if (i < num - 1)
					cout << ", ";
			}
			cout << ")" << endl;
		}
		else
		{
			cout << "�÷���η�������������" << endl;
			cout << "����һ��ͨ��Ϊ��" << endl;
			cout << "X = (";
			int num = ans_te.size();//�ؽ�Ľ�����Ԫ�ظ���
			for (int i = 0; i < num; i++)
			{
				cout << ans_te[i];
				if (i < num - 1)
					cout << ", ";
			}
			cout << ") + ";
			int size = ans_tong.size();//�����������Ľ���������
			int num2 = ans_tong[0].size();//�����������Ԫ�ظ���
			for (int i = 0; i < size; i++)
			{
				cout << "k" << i + 1 << "(";
				for (int j = 0; j < num2; j++)
				{
					cout << ans_tong[i][j];
					if (j < num2 - 1)
						cout << ", ";
				}
				cout << ")";
				if (i < size - 1)
					cout << " + ";
			}
			cout << endl;
		}
	}
}

///----��������----

//�����������
Equation scan_matrix(int m, int n)
{
	Equation e(m, n);//�������
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			cin >> e.vec[i][j];
	}
	for(int i = 0; i < m; i++)
	{
		if (e.vec[i][n - 1] != 0)
		{
			e.type = inhomo;//�����
			return e;
		}
	}
	e.type = homo;//���
	return e;
}

//����������Է�����ģʽ
void equation_mode()
{
	while (true)
	{
		cout << "--------------------------------------------" << endl;
		cout << "[ָ���б�]����start���ɿ�ʼ������quit�˳�������Է�����ģʽ������cls����" << endl;
		cout << ">>>";
		string str;
		cin >> str;
		if (str == "start")
		{
			cout << endl;
			equation_start();
		}
		else if (str == "quit")
		{
			cout << "[ϵͳ��ʾ]���˳�������Է�����ģʽ" << endl << endl;
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

//��ʼ������Է�����
void equation_start()
{
	int m, n;
	cout << "�����뷽������������������������" << endl;
	cin >> m >> n;
	cout << "�����뷽������������" << endl;
	Equation e = scan_matrix(m, n);//��ȡ������������e
	cout << endl;
	e.solve();//��Ⲣ��ӡ���
	cout << endl;
	while (true)//����������ز���
	{
		cout << "[ָ���б�]����ok�����������,����printm��ӡ�任�����м򻯽�����" << endl;
		cout << ">>>";
		string str;
		cin >> str;
		if (str == "ok")
		{
			cout << "[ϵͳ��ʾ]����������" << endl;
			return;
		}
		else if (str == "printm")
		{
			cout << "�м򻯽�����" << endl;
			e.print_matrix();
			cout << "[ϵͳ��ʾ]����������" << endl;
			return;
		}
		else
		{
			cout << "[����]�޷�ʶ���ָ��\n" << endl;
		}
	}
}