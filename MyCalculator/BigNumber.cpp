#include "pch.h"
#include "BigNumber.h"

///----���캯��----

//�޲����Ĺ��캯��
BigNumber::BigNumber()
{
	integer = { 0 };
	decimal = { 0 };
	int_len = 0;
	dec_len = 0;
	pos = '0';
}

//����Ϊint�Ĺ��캯��
BigNumber::BigNumber(int num)
{
	//��numת��Ϊ�ַ���
	string str;
	stringstream ss;
	ss << num;
	ss >> str;
	BigNumber temp(str);//���ַ���������ʱ�Ĵ�������
	integer = temp.integer;
	decimal = temp.decimal;
	int_len = temp.int_len;
	dec_len = temp.dec_len;
	pos = temp.pos;
}

//����Ϊdouble�Ĺ��캯��
BigNumber::BigNumber(double num)
{
	if (num == 0)//���0������
	{
		integer = { 0 };
		decimal = { 0 };
		int_len = 0;
		dec_len = 0;
		pos = '0';
	}
	else
	{
		//��numת��Ϊ�ַ���
		string str;
		stringstream ss;
		ss << setiosflags(ios::fixed);//����Ϊ����С��
		ss << setprecision(6) << num;//����6λС��
		ss >> str;
		BigNumber temp(str);//���ַ���������ʱ�Ĵ�������
		temp.clean_zero();//��������0
		integer = temp.integer;
		decimal = temp.decimal;
		int_len = temp.int_len;
		dec_len = temp.dec_len;
		pos = temp.pos;
	}
}

//����Ϊstring�Ĺ��캯��
BigNumber::BigNumber(const string &num)
{
	//��int_len��dec_len��ʼ��Ϊ0
	int_len = 0;
	dec_len = 0;
	int start;//�Ӻδ���ʼ�����ַ���num
	//��ȷ������
	if (num[0] == '-')//num�Ǹ���
	{
		pos = '-';
		start = 1;
	}
	else if (num == "0")//num��0
	{
		pos = '0';
		integer = { 0 };
		decimal = { 0 };
		int_len = 0;
		dec_len = 0;
		return;
	}
	else//num������
	{
		pos = '+';
		start = 0;
	}
	
	bool flag = false;//false��¼��������true��¼��С��
	//��start��ʼ�����ַ�����¼��ÿ������
	for (unsigned int i = start; i < num.length(); i++)
	{
		if (num[i] == '.')
		{
			flag = true;//����¼�����
			continue;
		}
		if (!flag)//¼������
		{
			integer.insert(integer.begin(), num[i] - '0');
			int_len++;
		}
		else//¼��С��
		{
			decimal.insert(decimal.end(), num[i] - '0');
			dec_len++;
		}
	}
	if (integer.size() == 1 && integer[0] == 0)
		int_len = 0;
	if (decimal.empty())
	{
		decimal.push_back(0);
	}
}

//����Ϊchar *�Ĺ��캯��
BigNumber::BigNumber(const char * num)
{
	string s(num);
	*this = BigNumber(s);
}

//----��Ա����----

//��������0�����¼��㳤�ȣ�˳������ȫ0���ķ���
void BigNumber::clean_zero()
{
	while (!integer.empty() && integer.back() == 0)
	{
		integer.pop_back();
		if (integer.empty())
			break;
	}
	while (!decimal.empty() && decimal.back() == 0)
	{
		decimal.pop_back();
		if (decimal.empty())
			break;
	}
	//���¼����������ֵĳ���
	if (integer.empty())//������������Ϊ0
	{
		integer.push_back(0);
		int_len = 0;
	}
	else
		int_len = integer.size();
	//���¼���С�����ֵĳ���
	if (decimal.empty())//����С������Ϊ0
	{
		decimal.push_back(0);
		dec_len = 0;
	}
	else
		dec_len = decimal.size();
	//������0�ķ���
	if (!int_len && !dec_len)
		pos = '0';
}

//����С��
void BigNumber::accuracy(int precision /*= PRECISION*/)
{
	if (precision >= dec_len)
		return;
	else
	{
		if (decimal[precision] >= 5)
		{
			if (precision != 0)
				decimal[precision - 1]++;
			else //precision == 0
				integer[0]++;
		}
		decimal.erase(decimal.begin() + precision, decimal.end());
		
		for (int i = decimal.size() - 1; i >= 0; i--)//����С������
		{
			if (decimal[i] >= 10)
			{
				decimal[i] -= 10;
				if (i != 0)
					decimal[i - 1]++;
				else //i == 0
					integer[0]++;
			}
			else
				break;
		}//for
		
		for (int i = 0; i < int_len; i++)//����������ע���λ���������ܶ�һλ
		{
			if (integer[i] >= 10)
			{
				integer[i] -= 10;
				if (i != int_len - 1)
					integer[i + 1]++;
				else //i == int_len - 1
				{
					integer.push_back(1);
					int_len++;
				}
			}
			else
				break;
		}
		this->clean_zero();
	}//else
}

//����෴��
void BigNumber::set_opposite()
{
	if (pos == '+')
		pos = '-';
	else if (pos == '-')
		pos = '+';
}

//�ƶ������ֵ�С����
//direction 0Ϊ��1Ϊ�ң�place��ʾ�ƶ���λ
void BigNumber::move_dot(bool direction, unsigned int place)
{
	vector<int> temp_int;//��ʱ����������
	vector<int> temp_dec;//��ʱ��С������
	//������
	if (place == 0)
		return;
	//����
	if (direction == 0)
	{
		if (place < integer.size())//�ƶ����������ֲ�Ϊ0��С���������貹��
		{
			//������������
			temp_int.insert(temp_int.end(), integer.begin() + place, integer.end());
			//����С������
			for (int i = place - 1; i >= 0; i--)
			{
				temp_dec.push_back(integer[i]);
			}
			temp_dec.insert(temp_dec.end(), decimal.begin(), decimal.end());
		}
		else//�ƶ�����������Ϊ0��С�����ֿ�����Ҫ��0
		{
			//������������
			temp_int.push_back(0);
			//����С������
			temp_dec.insert(temp_dec.end(), place - integer.size(), 0);
			temp_dec.insert(temp_dec.end(), integer.rbegin(), integer.rend());
			temp_dec.insert(temp_dec.end(), decimal.begin(), decimal.end());
		}
	}
	//����
	else
	{
		if (place < decimal.size())//�ƶ���С�����ֲ�Ϊ0�������������貹��
		{
			//����С������
			temp_dec.insert(temp_dec.end(), decimal.begin() + place, decimal.end());
			//������������
			for (int i = place - 1; i >= 0; i--)
			{
				temp_int.push_back(decimal[i]);
			}
			temp_int.insert(temp_int.end(), integer.begin(), integer.end());
		}
		else//�ƶ���С������Ϊ0���������ֿ�����Ҫ��0
		{
			//����С������
			temp_dec.push_back(0);
			//������������
			temp_int.insert(temp_int.end(), place - decimal.size(), 0);
			temp_int.insert(temp_int.end(), decimal.rbegin(), decimal.rend());
			temp_int.insert(temp_int.end(), integer.begin(), integer.end());
		}
	}
	//��ֵ
	integer = temp_int;
	decimal = temp_dec;
	this->clean_zero();//���0�����¼��㳤��
}

//����ת���ɵ�����
long long BigNumber::get_int() const
{
	if (int_len == 0)
		return 0;
	else
	{
		int result = 0;
		int base = 1;
		for (int i = 0; i < int_len; i++)
		{
			result += integer[i] * base;
			base *= 10;
		}
		if (pos == '-')
			result = -result;
		return result;
	}
}

//����ת���ɵ�ʵ��
long double BigNumber::get_real() const
{
	if (this->pos == '0')
		return 0;
	else
	{
		long double result = abs(this->get_int());
		long double base = 0.1;
		for (int i = 0; i < dec_len; i++)
		{
			result += decimal[i] * base;
			base /= 10;
		}
		if (pos == '-')
			result = -result;
		return result;
	}
}

///----��Ԫ����----

//���ؾ���ֵ
BigNumber abs(const BigNumber & num)
{
	BigNumber result = num;
	if (result.pos == '-')
		result.pos = '+';
	return result;
}

//�Ƚ��������ľ���ֵ��num1�󷵻�1��num2�󷵻�-1����ȷ���0
int cmp_abs(const BigNumber &num1, const BigNumber &num2)
{
	//�Ƚ�����λ������
	if (num1.int_len > num2.int_len)
		return 1;
	else if (num1.int_len < num2.int_len)
		return -1;
	else
	{
		//�Ӹ�λ����λ�Ƚ���������
		for (int i = num1.int_len - 1; i >= 0; i--)
		{
			if (num1.integer[i] > num2.integer[i])
				return 1;
			if (num1.integer[i] < num2.integer[i])
				return -1;
		}
		
		//��ʼ�Ƚ�С������
		//С��λ�����ȿ��ܲ�һ����Ҫ��0��һ����
		BigNumber num11 = num1;
		BigNumber num22 = num2;
		
		//ͨ����0�����������һ����
		//���ǵ�0������������size()��������
		int max_dec_len = max(num11.decimal.size(), num22.decimal.size());//С��Ӧ��������ô��
		num11.decimal.insert(num11.decimal.end(), max_dec_len - num11.decimal.size(), 0);
		num22.decimal.insert(num22.decimal.end(), max_dec_len - num22.decimal.size(), 0);
		//��ʼ�Ƚ�С������
		for (int i = 0; i < max_dec_len; i++)
		{
			if (num11.decimal[i] > num22.decimal[i])
				return 1;
			if (num11.decimal[i] < num22.decimal[i])
				return -1;
		}
		//��ȣ�����0
		return 0;
	}
}

//������������ֵ֮��
BigNumber add_abs(const BigNumber &num1, const BigNumber &num2)
{
	BigNumber num11 = num1;//num11����Ϊ����ֵ
	BigNumber num22 = num2;
	//ͨ����0�����������һ����
	//���ǵ�0������������size()��������
	int max_int_len = max(num11.integer.size(), num22.integer.size());//����Ӧ��������ô��
	int max_dec_len = max(num11.decimal.size(), num22.decimal.size());//С��Ӧ��������ô��
	//num11��Ϊ���Ҫ������һλ�Է��н�λ
	num11.integer.insert(num11.integer.end(), max_int_len - num11.integer.size() + 1, 0);
	num11.decimal.insert(num11.decimal.end(), max_dec_len - num11.decimal.size(), 0);
	num22.integer.insert(num22.integer.end(), max_int_len - num22.integer.size(), 0);
	num22.decimal.insert(num22.decimal.end(), max_dec_len - num22.decimal.size(), 0);

	//С���������
	for (int i = max_dec_len - 1; i >= 0; i--)
	{
		num11.decimal[i] += num22.decimal[i];
		if (num11.decimal[i] >= 10)//�����λ
		{
			num11.decimal[i] -= 10;
			if (i != 0)
				num11.decimal[i - 1]++;//��λ��ǰһλС��
			else
				num11.integer[0]++;//��λ����һλ����
		}
	}
	//�����������
	for (int i = 0; i < max_int_len; i++)
	{
		num11.integer[i] += num22.integer[i];
		if (num11.integer[i] >= 10)//�����λ
		{
			num11.integer[i] -= 10;
			num11.integer[i + 1]++;//��λ����һλ����
		}
	}
	num11.clean_zero();//��������0��������ȫ0���ķ���
	//��������
	if (num11 == BigNumber("0"))
		num11.pos = '0';
	else
		num11.pos = '+';
	return num11;
}

//������������ֵ֮�����Ǹ���
BigNumber minus_abs(const BigNumber & num1, const BigNumber & num2)
{
	BigNumber num11 = num1;//num11����Ϊ����ֵ
	BigNumber num22 = num2;
	if (cmp_abs(num11, num22) == -1)
		swap(num11, num22);//��֤������ֵ��num11-num22����
	//ͨ����0�����������һ����
	//���ǵ�0������������size()��������
	int max_int_len = max(num11.integer.size(), num22.integer.size());//����Ӧ��������ô��
	int max_dec_len = max(num11.decimal.size(), num22.decimal.size());//С��Ӧ��������ô��
	
	num11.integer.insert(num11.integer.end(), max_int_len - num11.integer.size(), 0);
	num11.decimal.insert(num11.decimal.end(), max_dec_len - num11.decimal.size(), 0);
	num22.integer.insert(num22.integer.end(), max_int_len - num22.integer.size(), 0);
	num22.decimal.insert(num22.decimal.end(), max_dec_len - num22.decimal.size(), 0);

	for (int i = max_dec_len - 1; i >= 0; i--)
	{
		num11.decimal[i] -= num22.decimal[i];
		if (num11.decimal[i] < 0)//�����λ�����������
		{
			num11.decimal[i] += 10;
			if (i != 0)
				num11.decimal[i - 1]--;//ǰһλС����λ
			else
				num11.integer[0]--;//��һλ������λ
		}
	}
	//�����������
	for (int i = 0; i < max_int_len; i++)
	{
		num11.integer[i] -= num22.integer[i];
		if (num11.integer[i] < 0)//�����λ�����������
		{
			num11.integer[i] += 10;
			num11.integer[i + 1]--;//ǰһλ������λ
		}
	}
	num11.clean_zero();//��������0��������ȫ0���ķ���
	//��������
	if (num11 == BigNumber("0"))
		num11.pos = '0';
	else
		num11.pos = '+';
	return num11;
}

//��������������
BigNumber divide_exactly(const BigNumber & num1, const BigNumber & num2)
{
	if (num1 == 0)
		return BigNumber(0);
	else if (num2 == 0)//�Ƿ����ʽ
		return BigNumber();
	else
	{
		BigNumber num11 = num1;
		BigNumber num22 = num2;
		if (num11 < 0)
			num11.set_opposite();//��֤num11Ϊ����
		if (num22 < 0)
			num22.set_opposite();//��֤num22Ϊ����
		BigNumber num22_init = num22;//��סԭ����num22
		vector<BigNumber> times_array;//��¼ÿ�������˶��ٴ�
		int i = 0;//��������
		//������ʼ
		while (num11 >= num22)//����
		{
			num11 = num11 - num22;
			num22.move_dot(1, 1);//��10
			times_array.push_back(1);
			i++;
		}
		while (num11 >= num22_init)//��С���������������
		{
			if (num11 >= num22)//����
			{
				num11 = num11 - num22;
				times_array[i] = times_array[i] + 1;
			}
			else //������
			{
				num22.move_dot(0, 1);//����
				i--;
			}
		}
		BigNumber result(0);//���
		for (unsigned int i = 0; i < times_array.size(); i++)
		{
			BigNumber temp(1);//��ʱ����
			temp.move_dot(1, i);
			result = result + temp * times_array[i];
		}
		//ȷ������
		if (result == 0)//�������Ľ����0
			result.pos = '0';
		else if (num1.pos == num2.pos)//����ͬ��
			result.pos = '+';
		else//�������
			result.pos = '-';
		return result;
	}
}

//����������ȡ��
BigNumber rem_num(const BigNumber & num1, const BigNumber & num2)
{
	return (num1 - multiply_num(divide_exactly(num1, num2), num2));
}

//��������֮��
BigNumber add_num(const BigNumber & num1, const BigNumber & num2)
{
	//����ͬ��
	if (num1.pos == num2.pos)
	{
		if (num1.pos == '0')
			return BigNumber("0");
		else if (num1.pos == '+')
		{
			BigNumber result = add_abs(num1, num2);
			result.pos = '+';
			return result;
		}
		else//num1.pos == '-'
		{
			BigNumber result = add_abs(num1, num2);
			result.pos = '-';
			return result;
		}
	}
	//�������������һ����0
	else if (num1.pos == '0' && num2.pos != 0)
		return num2;
	else if (num1.pos != '0' && num2.pos == 0)
		return num1;
	//һ��һ��
	else
	{
		BigNumber result = minus_abs(num1, num2);
		//ȷ������ķ���
		if (result == BigNumber(0))
			result.pos = '0';
		else
			result.pos = (cmp_abs(num1, num2) == 1) ? num1.pos : num2.pos;
		return result;
	}
}

//��������֮��
BigNumber minus_num(const BigNumber & num1, const BigNumber & num2)
{
	//����ͬ��
	if (num1.pos == num2.pos)
	{
		BigNumber result = minus_abs(num1, num2);
		if (num1 > num2)
			result.pos = '+';
		else if (num1 < num2)
			result.pos = '-';
		else
			result.pos = '0';
		return result;
	}
	//ǰ��Ϊ0
	else if (num1.pos == '0')
	{
		BigNumber result = num2;
		result.set_opposite();
		return result;
	}
	//����Ϊ0
	else if (num2.pos == '0')
	{
		return num1;
	}
	//һ��һ��
	else
	{
		BigNumber result = add_abs(num1, num2);
		result.pos = num1.pos;
		return result;
	}
}

//��������֮��
BigNumber multiply_num(const BigNumber & num1, const BigNumber & num2)
{
	BigNumber num11 = num1;//�����������ʱ����
	BigNumber num22 = num2;//�����������ʱ����
	//С�������Ʊ������
	num11.move_dot(1, num11.dec_len);
	num22.move_dot(1, num22.dec_len);
	
	if (num11 == 0 || num22 == 0)//����һ������Ϊ0
		return BigNumber(0);
	else //һ�����
	{
		BigNumber result(0);
		//��resultԤ���㹻�Ŀռ�
		result.integer.insert(result.integer.end(), num11.int_len + num22.int_len - 1, 0);
		//��ʼ��ʽ�˷�
		//i��Ӧnum22��j��Ӧnum11��k��Ӧresult
		for (int i = 0; i < num22.int_len; i++)
		{
			int k = i;
			for (int j = 0; j < num11.int_len; j++)
			{
				result.integer[k] += num22.integer[i] * num11.integer[j];
				if (result.integer[k] >= 10)//�����λ
				{
					result.integer[k + 1] += result.integer[k] / 10;
					result.integer[k] %= 10;
				}
				k++;
			}
		}
		result.clean_zero();//���0�����㳤��
		result.move_dot(0, num1.dec_len + num2.dec_len);//С�������ƻ�ȥ
		//ȷ������
		if (num11.pos != num22.pos)
			result.pos = '-';
		else
			result.pos = '+';
		return result;
	}//else
}

//��������֮�̣�precision�Ǳ�����С��λ��
BigNumber divide_num(const BigNumber & num1, const BigNumber & num2, int precision)
{
	BigNumber num11 = num1;//�����������ʱ����
	BigNumber num22 = num2;//�����������ʱ����
	num22.move_dot(1, num2.dec_len);//��num22�������
	num11.move_dot(1, num2.dec_len + precision + 1);
	BigNumber result = divide_exactly(num11, num22);
	result.move_dot(0, precision + 1);//��ʱresult��С��λ��Ϊprecision + 1
	result.accuracy(precision);
	return result;
}

//�������Ľ׳�
BigNumber factorial_num(const BigNumber &num)
{
	if (num == 0)
		return BigNumber(0);
	else if (num.dec_len != 0)//�Ƿ��Ĳ���
		return BigNumber();
	else
	{
		BigNumber result(1);//������
		for (int i = 2; i <= num; i++)
		{
			result = result * i;
		}
		return result;
	}	
}

//���������������ݣ�base�ǵ�����index��ָ��
//index����Ϊ����
BigNumber pow_int_index(const BigNumber &base, const BigNumber &index)
{
	if (base.pos == '0')
		return BigNumber(0);
	if (index.pos == '0')
		return BigNumber(1);
	else if (index.pos == '-')
	{
		BigNumber index2 = index;
		index2.pos = '+';
		return (1 / pow_int_index(base, index2));
	}
	else
	{
		BigNumber result("1");
		BigNumber base2 = base;
		long long index2 = index.get_int();
		while (index2 != 0)
		{
			if (index2 & 1)//index2Ϊ����
				result = result * base2;
			base2 = base2 * base2;
			index2 = index2 / 2;
		}
		return result;
	}
}

//�������������ο���
//degree����Ϊ����,��degree�ᱻת����int
BigNumber nth_root_int(const BigNumber & radicand, const BigNumber & degree)
{
	BigNumber small(1);
	small.move_dot(0, 7);//���10�������2��1000�η�
	BigNumber radicand2 = radicand;//�����������ʱ����
	int degree2 = degree.get_int();//�����������ʱ����
	BigNumber x0, x1;
	x0 = radicand2 / 2;//ȡradicand2 / 2��Ϊradicand2�ĳ�ֵ
	x1 = x0 - x0 * (1 - radicand2 * pow_int_index(x0, -degree2)) / degree2;
	do 
	{
		x0 = x1;
		x1 = x0 - x0 * (1 - radicand2 * pow_int_index(x0, -degree2)) / degree2;
	} while (abs(x0 - x1) >= small);
	x0.accuracy(6);
	return x0;
}

///----���������----

//��������أ������
ostream & operator<<(ostream & out, const BigNumber & num)
{
	string s;//��ʱ�ַ���s
	if (num.pos == '0')
	{
		s = "0";
		out << s;
		return out;
	}
	if (num.pos == '-')
		s.insert(s.end(), '-');
	//������������
	for (int i = num.int_len - 1; i >= 0; i--)
	{
		s.insert(s.end(), num.integer[i] + '0');
	}
	//��ʹ��������Ϊ0ҲҪ���һ��0
	if (num.int_len == 0)
		s.insert(s.end(), '0');
	//��С������
	if (num.dec_len > 0)
	{
		s.insert(s.end(), '.');//С����
		//С������˳��
		for (int i = 0; i < num.dec_len; i++)
			s.insert(s.end(), num.decimal[i] + '0');
	}
	out << s;
	return out;
}

//��������أ�������
istream & operator>>(istream & in, BigNumber & num)
{
	string s;//��ʱ�ַ���s
	if (!(in >> s))
		return in;
	num = BigNumber(s);
	return in;
}

//��������أ��е�==
bool operator==(const BigNumber & num1, const BigNumber & num2)
{
	if (num1.pos == num2.pos && cmp_abs(num1, num2) == 0)
		return true;
	else
		return false;
}
//��������أ�������!=
bool operator!=(const BigNumber & num1, const BigNumber & num2)
{
	if (num1 == num2)
		return false;
	else
		return true;
}
//��������أ�����>
bool operator>(const BigNumber & num1, const BigNumber & num2)
{
	//�������
	if (num1.pos == '+' && num2.pos == '0')
		return true;
	else if (num1.pos == '+' && num2.pos == '-')
		return true;
	else if (num1.pos == '0' && num2.pos == '-')
		return true;
	else if (num1.pos == '-' && num2.pos == '0')
		return false;
	else if (num1.pos == '-' && num2.pos == '+')
		return false;
	else if (num1.pos == '0' && num2.pos == '+')
		return false;
	//����ͬ��
	else
	{
		if (num1.pos == '+')
		{
			if (cmp_abs(num1, num2) == 1)
				return true;
			else
				return false;
		}
		else if (num1.pos == '-')
		{
			if (cmp_abs(num1, num2) == -1)
				return true;
			else
				return false;
		}
		else//��Ϊ0
			return false;
	}
}
//��������أ�С��<
bool operator<(const BigNumber & num1, const BigNumber & num2)
{
	if (!(num1 >= num2))
		return true;
	else
		return false;
}
//��������أ����ڵ���>=
bool operator>=(const BigNumber & num1, const BigNumber & num2)
{
	if (num1 > num2 || num1 == num2)
		return true;
	else
		return false;
}
//��������أ�С�ڵ���<=
bool operator<=(const BigNumber & num1, const BigNumber & num2)
{
	if (!(num1 > num2))
		return true;
	else
		return false;
}

//��������أ����+
BigNumber operator+(const BigNumber & num1, const BigNumber & num2)
{
	return add_num(num1, num2);
}

//��������أ����-
BigNumber operator-(const BigNumber & num1, const BigNumber & num2)
{
	return minus_num(num1, num2);
}

//��������أ����*(����PRECISIONλС��)
BigNumber operator*(const BigNumber & num1, const BigNumber & num2)
{
	BigNumber result = multiply_num(num1, num2);
	result.accuracy(PRECISION);
	return result;
}

//��������أ����/(����PRECISIONλС��)
BigNumber operator/(const BigNumber & num1, const BigNumber & num2)
{
	return divide_num(num1, num2, PRECISION);
}

//��������أ�ȡ��%
BigNumber operator%(const BigNumber & num1, const BigNumber & num2)
{
	return rem_num(num1, num2);
}

//��������أ�ȡ�෴��-
BigNumber BigNumber::operator-() const
{
	BigNumber temp = *this;
	temp.set_opposite();
	return temp;
}

//��������أ�ǰ��++
BigNumber& BigNumber::operator++()
{
	*this = (*this) + 1;
	return *this;
}
//��������أ�����++
BigNumber BigNumber::operator++(int)
{
	BigNumber old = *this;
	++(*this);
	return old;
}

//��������أ�+=
BigNumber & BigNumber::operator+=(const BigNumber & num)
{
	*this = *this + num;
	return *this;
}
//��������أ�-=
BigNumber & BigNumber::operator-=(const BigNumber & num)
{
	*this = *this - num;
	return *this;
}
//��������أ�*=
BigNumber & BigNumber::operator*=(const BigNumber & num)
{
	*this = *this * num;
	return *this;
}
//��������أ�/= ����������������
BigNumber & BigNumber::operator/=(const BigNumber & num)
{
	*this = *this / num;
	return *this;
}
//��������أ�%=
BigNumber & BigNumber::operator%=(const BigNumber & num)
{
	*this = *this % num;
	return *this;
}