/*
*  ��¼һЩ���õ��㷨
*/
#ifndef COMMON_ALGORITHM_H
#define COMMON_ALGORITHM_H
#include <string>
#include <iostream>

namespace alg
{


void Swap(char* a, char* b)
{
	char temp = *a;
	*a = *b;
	*b = temp;
}

/*
*  �����ַ��� ��ӡ�ַ�����ȫ����
*  ����: adc ���ӡ˳��Ϊ abc acb bac bca cba cab
*/
void Permutation(char* str, char* begin)
{
	if (*begin == '\0')
	{
		std::cout << str << std::endl;
	}
	else
	{
		for (char* ch = begin; *ch != '\0'; ++ch)
		{
			if (*ch != *begin)
			{
				Swap(ch, begin);
			}
			Permutation(str, begin + 1);
			if (*ch != *begin)
			{
				Swap(ch, begin);
			}
		}
	}
}
void Permutation(char* str)
{
	if (str == nullptr)
	{
		return;
	}
	Permutation(str, str);
}

/*
*  �����г��ִ�������һ�������
*  �㷨: �����۰뷽������ʵ��,������ʹ������һ�ַ�ʽ:
*  ��������һ�����ֳ��ֵĴ����������������ֳ��ִ����ĺͻ�Ҫ��,�������鱣������ֵ:
*  1. �����е�һ������;
*  2. һ���Ǵ���
*  ����ʱ:����ͱ�������һ��,���� + 1;��ͬ�Ļ� -1;����Ϊ0ʱ��,������������,�Ҵ���=1
*  ���Ľ��:һ���ǰѴ�������Ϊ1ʱ��Ӧ������
*  ʱ�临�Ӷ�: o(n)
*/
int MoreThanHalfNum(int* nums, int length)
{
	if (nums == nullptr || length <= 0)
	{
		return 0;
	}
	int temp_num = nums[0];
	int times = 1;
	for (int idx = 1; idx < length; ++idx)
	{
		if (temp_num == nums[idx])
		{
			++times;
		}
		else
		{
			if (times == 0)
			{
				temp_num = nums[idx];
				times = 1;
			}
			else
			{
				--times;
			}
		}
	}
	return temp_num;
}

#include <set>
multiset<int, greater<int> >
void Test_Agl()
{
	const char* str = "abcc";
	char* ch = new char[strlen(str) + 1];
	strcpy(ch, str);
	//���������Ǵ��,�㴫��ָ���ǳ�������
	//Permutation(const_cast<char*>(str));
	Permutation(ch);
	delete[] ch;

	int arrs[] = { 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2 };
	int length = sizeof(arrs) / sizeof(arrs[0]);
	std::cout << MoreThanHalfNum(arrs, length) << std::endl;
}


}
#endif