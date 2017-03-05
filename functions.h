/*
* common function, common algorithm
*/


#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <algorithm>
#include <string.h>
#include <stack>
#include <assert.h>


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

/**
�ж϶��������ڶ��ϻ���ջ��
ԭ���ֲ�����onstack���ڳ����ջ��������ջ�Ľṹ��������չ�������ڵ͵�ַ�����Ҷѵ�ַ����ջ��ַ��������os��
	  ��Ȼ�޷���ϸ���־�̬���ݺͶ����ݣ����߶��᷵��True
*/
bool OnHeap(const char* address)
{
	char onstack;
	return address < &onstack;
}



/**
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
	if ((exponent & 0x1) == 1)
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
	size_t ex_len = strlen(src) + space_num * 2;
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

/**
 * ʵ�ְ���MIN������ջ ����ȡջ����СԪ�� ʱ�临�Ӷ�ΪO(1);
 * ˼·������STL�е�stackʵ�֣�stack����pop��pushʱ�临�ӶȾ�Ϊo(1);
 *      �������ʹ��һ��ջ����ʵ�ָù��ܣ���Ҫһ��ר�����ڱ�����Сֵ�ĸ���ջ
 */
template <typename T>
class MinStack
{
public:
    MinStack()
    {

    }
    ~MinStack()
    {

    }
    void Pop();
    void Push(const T& value);
    const T& Min() const ;

private:
    std::stack<T> stack_;
    std::stack<T> min_stack_;
};

template <typename T>
void MinStack<T>::Pop()
{
    assert(stack_.size() > 0 && min_stack_.size() > 0);
    stack_.pop();
    min_stack_.pop();
}

template <typename T>
void MinStack<T>::Push(const T &value)
{
    stack_.push(value);
    if (min_stack_.size() == 0 || min_stack_.top() > value)
    {
        min_stack_.push(value);
    }
    else
    {
        min_stack_.push(min_stack_.top());
    }
}

template <typename T>
const T& MinStack<T>::Min() const
{
    assert(min_stack_.size() > 0 && stack_.size() > 0);
    return min_stack_.top();
}

/**
 * �����������ջ˳���жϳ�ջ˳���Ƿ�����
 */
bool IsPopOrder(const int* push, const int* pop, int length)
{
    if (push == nullptr || pop == nullptr || length == 0)
    {
        return false;
    }
    bool ret = true;
    std::stack<int> temp;
    while (pop != nullptr)
    {
        if (temp.size() > 0 && *pop == temp.top())
        {
            ++pop;
            temp.pop();
            continue;
        }
        if (push == nullptr)
        {
            ret = false;
            break;
        }
        while (push != nullptr)
        {
            temp.push(*push);
            push++;
            if (*pop == temp.top())
            {

                break;
            }
        }
    }
    return ret;
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

    std::stack<int> test;
    test.push(1111);
    std::cout << test.top() << std::endl;
    int push[] = { 1, 2, 3, 4, 5 };
    int pop[] = { 4, 5, 3, 2, 1 };
    bool ret = IsPopOrder(push, pop, 5);
    std::cout << ret  << std::endl;
}
#endif