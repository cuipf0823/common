/*
	�������������㷨ʵ��
*/
#ifndef COMMON_SORT_H
#define COMMON_SORT_H
#include <iostream>

//�����ӡ����
void PrintArr(int arr[], int len)
{
	for (int i = 0; i < len; ++i)
	{
		std::cout << arr[i] << "\t";
	}
	std::cout << std::endl;
}

//ð������ ��������Ԫ�رȽ� ʱ�临�Ӷȣ����O(n^2)	��õ������O(n)
void  BubbleSort(int* a, int len)
{
	for (int i = 0; i < len; ++i)
	{
		bool noswap = true;
		for (int j = 0; j < len - i - 1; ++j)
		{
			if (a[j] > a[j + 1])
			{
				int temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
				noswap = false;
			}
		}
		if (noswap)
		{
			break;
		}
	}
}

//ֱ�Ӳ��������㷨 ���������ǽ�һ����¼���뵽�Ѿ��ź����������У��Ӷ��ȵ�һ���µģ�Ԫ�ؼ�1������� ֪��������
//ʱ�临�Ӷȣ����O(n^2)	��õ������O(n)
void InsertSort(int* a, int len)
{
	int idx = 0;
	int temp = 0;
	for (int i = 1; i < len; ++i)
	{	
		temp = a[i];
		for (idx = i - 1; idx >= 0 && a[idx] > temp; --idx)
		{
			a[idx + 1] = a[idx];
		}
		a[idx + 1] = temp;
	}
}

//ѡ�������㷨
//ԭ��:ÿ�δ������������ҵ������С����ֵ�����ڵ�ǰ��������ͷ��������ʹ��������
//���Ӷȣ��O(0^2);
void SelectSort(int* a, int len)
{
	for (int i = 0; i < len; ++i)
	{
		int min = i;
		for (int j = i + 1; j < len; ++j)
		{
			if (a[j] < a[min])
			{
				min = j;
			}
		}
		int temp = a[i];
		a[i] = a[min];
		a[min] = temp;
	}
}

//shell����  ϣ�������ǽ����鰴��һ�������ֳɼ����������������ͨ�������̲����������������
//ʱ�临�Ӷȣ�O(nlogn) ~~ O(n^2);
void ShellSort(int* a, int len)
{
	for (int gap = len >> 1; gap > 0; gap >>= 1)
	{
		for (int i = gap; i < len; ++i)
		{
			int temp = a[i];
			int j = i - gap;
			for (; j >= 0 && a[j] > temp; j -= gap)
			{
				a[j + gap] = a[j];
			}
			a[j + gap] = temp;
		}
	}
}

//�鲢���� ��һ�������ɢ��С���飬Ȼ���С����ƴ��������֪����������
void MergeArray(int* nums, int begin, int mid, int end, int* temp)
{
	int lb = begin, rb = mid, tb = begin;
	while (lb != mid && rb != end)
	{
		if (nums[lb] < nums[rb])
		{
			temp[tb++] = nums[lb++];
		}
		else
		{
			temp[tb++] = nums[rb++];
		}
	}
	while (lb < mid)
	{
		temp[tb++] = nums[lb++];
	}
	while (rb < end)
	{
		temp[tb++] = nums[rb++];
	}

	for (int i = begin; i < end; i++)
	{
		nums[i] = temp[i];
	}
}

void MergeSort(int* nums, int begin, int end, int* temp)
{
	int mid = (begin + end) / 2;
	if (mid != begin) 
	{
		MergeSort(nums, begin, mid, temp);
		MergeSort(nums, mid, end, temp);
		MergeArray(nums, begin, mid, end, temp);
	}
}

void Swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

//�������� 	ѡ��һ����׼�����ѱ������С��Ų����� ���������ƶ����ұ� Ȼ�󲻶϶���������ִ��������� ֪����������
//ʱ�临�Ӷȣ�ƽ��ʱ�临�Ӷȣ�O(nlog2n);
void QuickSort(int* nums, int begin, int end)
{
	if (begin < end - 1)
	{
		int lb = begin, rb = end - 1;
		while (lb < rb) 
		{
			while (nums[rb] >= nums[begin] && lb < rb)
			{
				rb--;
			}
			while (nums[lb] <= nums[begin] && lb < rb)
			{
				lb++;
			}
			Swap(nums[lb], nums[rb]);
		}
		Swap(nums[begin], nums[lb]);
		QuickSort(nums, begin, lb);
		QuickSort(nums, lb + 1, end);
	}
}

void TestSort()
{
	int arr[] = { 4, 10, 23, 90, 29, 78, 100, 66 };
	int len = sizeof(arr) / sizeof(arr[0]);
// 	BubbleSort(arr, len);
// 	PrintArr(arr, len);
 	QuickSort(arr, 0, len);
 	PrintArr(arr, len);
//	ShellSort(arr, len);
}

#endif