/*
* common function, common algorithm
*/


#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <algorithm>
using namespace std;

//��ת�ַ������� �磺��12345����ת�ɡ�54321��
void reverse_by_swap(char* str, int n)
{
	char* begin = str;
	char* end = str + n - 1;
	while (begin < end)
	{
		char tmp = *begin;
		*begin = *end;
		*end = tmp;
		++begin;
		--end;
	}
}


//ʹ�����ķ�ʽ����	Ч�ʵ�
void reverse_by_xor(char* str, int n)
{
	char* begin = str;
	char* end = str + n - 1;
	while (begin < end)
	{
		*begin ^= *end;
		*end ^= *begin;
		*begin ^= *end;
		++begin;
		--end;
	}
}

//ʹ��stl�㷨
void reverse_by_std(char* str, int n)
{
	std::reverse(str, str + n);
}

/*
�ж϶��������ڶ��ϻ���ջ��
ԭ���ֲ�����onstack���ڳ����ջ��������ջ�Ľṹ��������չ�������ڵ͵�ַ�����Ҷѵ�ַ����ջ��ַ��������os��
	  ��Ȼ�޷���ϸ���־�̬���ݺͶ����ݣ����߶��᷵��True
*/
bool OnHeap(const char* address)
{
	char onstack;
	return address < &onstack;
}



/*
* ����ֵ�������η�
* ע�⣻1. double��float�жϺ�0��ȵķ�ʽ��
*      2. ע�⿼��baseΪ0�������
*      3. ע�⿼��exponentΪ���������
*/
double PowerWithUnsignedExponent(double base, int exponent)
{
	double result = 1.0;
	for (int idx = 0; idx < exponent; ++idx)
	{
		result *= base;
	}
	return result;
}

/*
* ��ֵ�����η����Ż���ʽ
*/
double PowerUnsignedExpOptimize(double base, int exponent)
{
	if (exponent == 0)
	{
		return 1.0;
	}
	if (exponent == 1)
	{
		return base;
	}
	double result = PowerWithUnsignedExponent(base, exponent >> 1);
	result *= result;
	if (exponent & 0x1 == 1)
	{
		result *= base;
	}
	return result;
}

double Power(double base, int exponent)
{
	if ((base - 0.00 > -0.00000001) && (base - 0.00 < 0.0000001))
	{
		return base;
	}
	if (exponent >= 0)
	{
		return PowerWithUnsignedExponent(base, exponent);
	}
	else
	{
		unsigned int abs_exponent = static_cast<unsigned int>(-exponent);
		return 1.0 / PowerWithUnsignedExponent(base, abs_exponent);
	}
}


//����
void TestFunc()
{
	std::cout << Power(2.0, 4) << std::endl;
	std::cout << Power(0.0, -2) << std::endl;
	std::cout << Power(3.0, -2) << std::endl;

}
#endif