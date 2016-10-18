#include "pool_memory.h" 

char* PoolMemoryBase::start_free_ = nullptr;
char* PoolMemoryBase::end_free_ = nullptr;
size_t PoolMemoryBase::heap_size_ = 0;
PoolMemoryBase::Obj* volatile PoolMemoryBase::free_list_[kFreeListSize] = { 0 };


PoolMemoryBase::Obj* volatile* PoolMemoryBase::GetFreeList(size_t bytes)
{
	size_t idx = (bytes + kAlign - 1) / (kAlign - 1);
	return free_list_ + idx;
}

void* PoolMemoryBase::ReFill(size_t n)
{
	int nobjs = 20;
	char* chunk = AllocateChunk(n, nobjs);
	//�������һ�����飬ֱ�ӷ���������ߣ�free_list���½��
	if (nobjs == 1)
	{
		return chunk;
	}

	Obj* result = nullptr;
	Obj* current_obj = nullptr;
	Obj* next_obj = nullptr;
	Obj* volatile* free_list = nullptr;
	free_list = GetFreeList(n);
	result = reinterpret_cast<Obj*>(chunk);
	//���²���free_list��free_list���ڵ㴮������
	*free_list = next_obj = reinterpret_cast<Obj*>(chunk + n);
	for (int idx = 1;; ++idx)
	{
		current_obj = next_obj;
		next_obj = reinterpret_cast<Obj*>(next_obj + n);
		if (nobjs - 1 == idx)
		{
			current_obj->free_list_link = nullptr;
			break;
		}
		else
		{
			current_obj->free_list_link = next_obj;
		}
	}
	return result;
}

char* PoolMemoryBase::AllocateChunk(size_t n, int& nobjs)
{
	char* result = nullptr;
	size_t total_bytes = nobjs * n;
	size_t left_bytes = end_free_ - start_free_;
	
	if (left_bytes > total_bytes)
	{
		//�ڴ�����㹻�Ŀռ�����������
		result = start_free_;
		start_free_ += total_bytes;
		return result;

	}
	else if (left_bytes >= n)
	{
		//�ڴ��ʣ�¿ռ䲻������ȫ�������������㹻��Ӧһ�����ϵ�����
		nobjs = left_bytes / n;
		total_bytes = nobjs * n;
		result = start_free_;
		start_free_ += total_bytes;
		return result;
	}
	else
	{
		//�ڴ����һ������Ĵ�С���޷��ṩ
		size_t bytes_to_get = 2 * total_bytes + RoundUp(heap_size_ >> 4);
		if (left_bytes > 0)
		{
			Obj* volatile* free_list = GetFreeList(left_bytes);
			(reinterpret_cast<Obj*>(start_free_))->free_list_link = *free_list;
			*free_list = reinterpret_cast<Obj*>(start_free_);
		}
		start_free_ = static_cast<char*>(::operator new(bytes_to_get));
		if (start_free_ == nullptr)
		{
			//heap �ռ䲻�㣬newʧ�� ����free_list ���ͷų�����δ�õ�����
			size_t i = n;
			for (; i <= kMaxBytes; i += kAlign)
			{
				Obj* volatile* free_list = GetFreeList(i);
				Obj* p = *free_list;
				if (p != nullptr)
				{
					*free_list = p->free_list_link;
					start_free_ = reinterpret_cast<char*>(p);
					end_free_ = start_free_ + i;
					return AllocateChunk(n, nobjs);
				}
			}
			
		}
		end_free_ = start_free_ + bytes_to_get;
		heap_size_ = bytes_to_get;
		return AllocateChunk(n, nobjs);
	}
}





