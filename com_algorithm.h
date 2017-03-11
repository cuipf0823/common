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

void Test_Agl()
{
	const char* str = "abcc";
	char* ch = new char[strlen(str) + 1];
	strcpy(ch, str);
	//���������Ǵ��,�㿴���㴫��ָ���ǳ�������
	//Permutation(const_cast<char*>(str));
	Permutation(ch);
	delete[] ch;
}


}
#endif