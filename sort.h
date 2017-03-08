/*
*	�������������㷨ʵ��
*	���������㷨ʵ��
*   �������㷨
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
//���Ӷȣ��O(n^2);
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
		if (i != min)
		{
			int temp = a[i];
			a[i] = a[min];
			a[min] = temp;
		}
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
	int low = begin;
	int high = mid; 
	int temp_idx = begin;
	while (low != mid && high != end)
	{
		if (nums[low] < nums[high])
		{
			temp[temp_idx++] = nums[low++];
		}
		else
		{
			temp[temp_idx++] = nums[high++];
		}
	}
	while (low < mid)
	{
		temp[temp_idx++] = nums[low++];
	}
	while (high < end)
	{
		temp[temp_idx++] = nums[high++];
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

//�������� 	ѡ��һ����׼�����ѱ������С��Ų����� ���������ƶ����ұ� Ȼ�󲻶϶���������ִ��������� ֱ����������
//ʱ�临�Ӷȣ�ƽ��ʱ�临�Ӷȣ�O(nlog2n);
int Partition(int* nums, int low, int high);
void QuickSort(int* nums, int begin, int end)
{
	if (begin < end)
	{
		int key = Partition(nums, begin, end);
		if (key - 1 > 0)
		{
			QuickSort(nums, begin, key - 1);
		}
		if (key + 1 < end)
		{
			QuickSort(nums, key + 1, end);
		}
	}
}
/*
*	��һ�˿�������
*/
int Partition(int* nums, int low, int high)
{
	if (nums == nullptr || low >= high)
    {
        //input invaild
        return -1;
    }

    int guard = nums[low];
    while (low < high)
    {
        while (low < high && nums[high] >= guard)
        {
            --high;
        }
        if (low < high)
        {
            nums[low] = nums[high];
            ++low;
        }
        while (low < high && nums[low] < guard)
        {
            ++low;
        }
        if (low < high)
        {
            nums[high] = nums[low];
            --high;
        }
    }
	nums[low] = guard;
	return low;
}


/*
* �����ڶ�����������ʵ�ֵ����ѣ� �����ѣ�������
*/
/*
* ������
* ������heap[begin, end]����heap[begin]Ϊ������ȫ��������
* �ҷֱ���heap[2*begin] �� [2*begin + 1]Ϊ������������Ϊ����ѣ�
* ����heap[begin]ʹ����ϴ����;
*/
void AdjustHeap(int* heap, int begin, int end)
{
	if (heap == nullptr || begin >= end)
	{
		return;
	}
	int root_value = heap[begin];
	int root = begin;
	int child = root * 2;
	bool finish = false;
	while (child <= end && !finish)
	{
		if (child < end && heap[child] < heap[child + 1])
		{
			++child;
		}
		if (root_value >= heap[child])
		{
			finish = true;
		}
		else
		{
			heap[root] = heap[child];
			root = child;
			child = root * 2;
		}
	}
	heap[root] = root_value;
	//PrintArr(heap, end + 1);
}

/*
* ������
*/
void CreateHeap(int* heap, int length)
{
	if (heap == nullptr || length == 0)
	{
		return;
	}
	//��length / 2����¼��ʼ����ɸѡ����
	for (int index = length / 2; index >= 0; --index)
	{
		AdjustHeap(heap, index, length - 1);
	}
}

/*
*	������ ʱ�临�Ӷ�: ƽ����������O(log2n)
*/
void SortHeap(int* heap, int length)
{
	int mid = length / 2;
	for (int index = length - 1; index >= 1; --index)
	{
		//���ڵ��β�ڵ㽻��
		int temp = heap[0];
		heap[0] = heap[index];
		heap[index] = temp;
		AdjustHeap(heap, 0, index - 1);
	}
}

void TestSort()
{
	int arr[] = { 4, 10, 23, 90, 29, 78, 100, 66 };
	int arr1[] = { 90, 29, 78, 100, 66, 4, 10, 23};
	int len = sizeof(arr) / sizeof(arr[0]);
// 	BubbleSort(arr, len);
// 	PrintArr(arr, len);
	ShellSort(arr, len);
	ShellSort(arr1, len);
//  PrintArr(arr, len);
// 	PrintArr(arr1, len);
	const int kLen = 8;
	int temp[kLen] = { 0 };
	MergeSort(arr, 0, len, temp);
	PrintArr(arr, len);
	PrintArr(temp, kLen);
//	ShellSort(arr, len);

	//�����
	int heap[kLen] = { 48, 62, 35, 77, 55, 14, 35, 98 };
	CreateHeap(heap, kLen);
	PrintArr(heap, kLen);
	SortHeap(heap, kLen);
	PrintArr(heap, kLen);

}


/*
 * *************************************************************
 */

//���������㷨

/*
 * 1. ˳������㷨  ������ң��������Բ��� �����е�һ�˿�ʼһ�α���
 * ʱ�临�Ӷȣ�O(n)
 */

int SequenceSearch(int arr[], int length, int value)
{
	int index = 0;
	for (int idx = 0; idx < length; ++idx)
	{
		if (arr[idx] == value)
		{
			return idx;
		}
	}
	return -1;
}

/*
 * 2. ���ֲ����㷨���۰���ң�
 * ˼�룺���ݸ�����ֵ�����е�ֵ�Աȣ���� �ҵ������� �����β������������У�
 * ע�⣺1. ���ֲ��ҵ����б���Ϊ�������У����������Ļ���������
 * 		 2. ���ڲ���ɾ��Ƶ���Ķ��У�ά��������гɱ��ϸߣ�������ʹ�ã�
 * ʱ�临�Ӷȣ���ǣ�O(log2(n + 1)); ƽ����O(log2n)
 */

int BinarySearch(int arr[], int length, int value)
{
	int mid = 0;
	int low = 0;
	int high = length - 1;
	while (low < high)
	{
		mid = (low + high) / 2;
		if (arr[mid] == value)
		{
			return mid;
		}
		else if (arr[mid] < value)
		{
			low = mid + 1;
		}
		else
		{
			high = mid - 1;
		}
	}
	return -1;
}

int BinarySearchRe(int arr[], int low, int high, int value)
{
	if (low < high)
	{
		return -1;
	}

	int mid = (low + high) / 2;
	if (arr[mid] == value)
	{
		return mid;
	}
	else if (arr[mid] < value)
	{
		return BinarySearchRe(arr, mid + 1, high, value);
	}
	else
	{
		return BinarySearchRe(arr,  low,  mid - 1, value);
	}
}

/*
*	3. ��ֵ�����㷨
*   ˼�룺���ڶ��ֲ����㷨�����ݲ��ҵ��������еĴ��λ�ã������ҵ��޸�Ϊ����Ӧ�ģ���߲���Ч�ʣ�
*	ע: ���ڱ��ϴ󣬶���Ԫ�طֲ��ȽϾ��ȵı���˵�����㷨ƽ�����ܱȶ��ֲ���Ҫ�úܶ࣬��֮����һ������
*	ʱ�临�Ӷȣ����ҳɹ�����ʧ�ܵ�ʱ�临�ӶȾ�ΪO(log2(log2n))
*/
int InsertionSearch(int arr[], int length, int value)
{
	int mid = 0;
	int low = 0;
	int high = length - 1;
	while (low < high)
	{
		mid = low + (value - arr[low]) / (arr[high] - arr[low])*(high - low);
		if (arr[mid] == value)
		{
			return mid;
		}
		else if (arr[mid] < value)
		{
			low = mid + 1;
		}
		else
		{
			high = mid - 1;
		}
	}
	return -1;
}

void TestSearch()
{
	int arr[] = { 4, 10, 23, 29, 78, 100, 166 };
	int len = sizeof(arr) / sizeof(arr[0]);
	std::cout << SequenceSearch(arr, len, 29) << std::endl;
	std::cout << BinarySearch(arr, len, 29) << std::endl;
	std::cout << BinarySearchRe(arr, 0, len - 1, 299) << std::endl;
	std::cout << InsertionSearch(arr, len, 29) << std::endl;
}


/**
 *	쳲���������ļ��������ʽ
 *  Ч�ʵ�
 */
long long FabonnacciRe(uint32_t n)
{
	if (n <= 1)
	{
		return n;
	}
	return FabonnacciRe(n - 1) + FabonnacciRe(n - 2);
}

long long Fabonnacci(uint32_t n)
{
	if (n <= 1)
	{
		return n;
	}
	long long fib_minus_one = 1;
	long long fib_minus_two = 2;
	long long fib_n = 0;
	for (int index = 2; index <= n; ++index)
	{
		fib_n = fib_minus_one + fib_minus_two;
		fib_minus_two = fib_minus_one;
		fib_minus_one = fib_n;
	}
	return fib_n;
}

#endif