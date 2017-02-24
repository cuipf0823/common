/*
* common function, common algorithm
*/


#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <algorithm>
#include <string.h>
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

/**
 * 	��ά�����в��ң�ÿһ�д����ҵ�����ÿһ�д��ϵ��µ�������������������ж��Ƿ����
 * 	���ڷ��� True;
 *  1. ѡ�����Ͻ����ֱȽϣ����ڲ������֣��޳����ڵ��У������޳������У�
 * 
 */
bool MatrixFind(int* matrix, int rows, int columns, int number)
{
	bool found = false;
	if (matrix != nullptr && rows > 0 && columns > 0)
	{
		int row = 0; 
		int col = columns - 1;
		while (row < col && columns > 0)
		{
			if (matrix[row * columns + col] == number)
			{
				found = true;
				break;
			}
			else if (matrix[row * columns + col] > number)
			{
				--col;
			}
			else
			{
				++row;
			}
		}
	}
	return found;
}


/**
 *	�滻�ַ��������еĿո�Ϊ��%20����
 *  para len: Ϊ�ַ�����������
 *	˼·���ȼ����ַ����пո�ĸ�������չ�ַ��������ο����ַ�������
 */
bool ReplaceSpace(char* src, int len)
{
	if (src == nullptr || len <= 0)
	{
		return false;
	}
	int space_num = 0;
	for (int idx = 0; src[idx] != '\0'; ++idx)
	{
		if (src[idx] == ' ')
		{
			++space_num;
		}
	}
	int ex_len = strlen(src) + space_num * 2;
	if (ex_len > len)
	{
		return false;
	}
	char* rend = src + strlen(src);
	char* rend_ex = src + ex_len;
	while (rend != src && space_num > 0)
	{
		if (*rend == ' ')
		{
			*rend_ex-- = '0';
			*rend_ex-- = '2';
			*rend_ex-- = '%';
		}
		else
		{
			*rend_ex-- = *rend;
		}
		--rend;
	}
	return true;
}

void TestFunc()
{
	std::cout << Power(2.0, 4) << std::endl;
	std::cout << Power(0.0, -2) << std::endl;
	std::cout << Power(3.0, -2) << std::endl;

	const int kLength = 50;
	char array[kLength] = { "we are so happy !" };
	ReplaceSpace(array, kLength);
	std::cout << array << std::endl;
}
#endif