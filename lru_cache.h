/*
* least recently useds 
* �ο�leveldb��lru�㷨��ʹ��stl��lru�㷨��ʵ��
* 1. ʹ��list��unordered_mapʵ��lru�㷨��ʹ�ò���ɾ��Ч��Ϊo(1);
*/

#ifndef LRU_CACHE_H
#define LRU_CACHE_H
#include <assert.h>
#include <list>
#include <unordered_map>

namespace LRU
{

template<typename Key, typename Value>
class LRUCache
{
public:
	struct LRUHandle
	{
		Key key;
		Value value;
		size_t refs = 2;	 //���ü��� ��ʼΪ2 һ�����ڲ�ʹ�� һ�����ⲿ
		size_t charge;       //����
		LRUHandle(const Key& k, const Value& v, size_t c) :
			key(k),
			value(v),
			charge(c)
		{

		}
	};
protected:
	typedef std::list<LRUHandle*> CacheList;
	typedef std::unordered_map<Key, typename CacheList::iterator> CacheTable;

public:
	LRUCache() : usage_(0), capacity_(0)
	{

	}
	~LRUCache()
	{
		for (auto it : lru_)
		{
			Release(*it);
		}
	}
	LRUCache(const LRUCache&) = delete;
	LRUCache(LRUCache&&) = delete;
	LRUCache& operator=(const LRUCache&) = delete;

	void set_capacity(size_t capacity)
	{
		capacity_ = capacity;
	}

	LRUHandle* Insert(const Key& key, const Value& value, size_t charge = 1);
	LRUHandle* Lookup(const Key& key);
	void Release(LRUHandle* handle);
	void Erase(const Key& key);
	void Prune();
private:
	size_t usage_;
	size_t capacity_;
	CacheList lru_;	//list ��һ��Ԫ�����������ʹ��Ԫ�أ����һ��Ԫ��������Ԫ��
	CacheTable table_;
};

template<typename Key, typename Value>
typename LRUCache<Key, Value>::LRUHandle* 
LRUCache<Key, Value>::Insert(const Key& key, const Value& value, size_t charge /*= 1*/)
{
	LRUHandle* handle = new LRUHandle(key, value, charge);
	assert(handle != nullptr);
	typename CacheTable::iterator iter = table_.find(key);
	if (iter != table_.end())
	{
		//����ڵ��Ѿ����ڣ���ɾ��
		typename CacheList::iterator it = iter->second;
		lru_.erase(it);
		table_.erase(iter);
		Release(*it);
	}
	//�����µĽڵ�
	typename CacheList::iterator pos = lru_.insert(lru_.begin(), handle);
	if (!table_.insert(std::make_pair(key, pos)).second)
	{
		assert(false);
	}
	usage_ += charge;
	//��ǰ������Ԫ�����ȴ����趨ֵ��ɾ���ʱ��δʹ�õ�Ԫ�� ѭ����֤Ԫ�ش��ڴ�����
	while (usage_ > capacity_ && !lru_.empty())
	{
		typename CacheList::iterator iter = lru_.back();
		table_.erase(iter->key);
		lru_.pop_back();
		Release(*iter);
	}
	return handle;
}

template<typename Key, typename Value>
typename LRUCache<Key, Value>::LRUHandle* LRUCache<Key, Value>::Lookup(const Key& key)
{
	typename CacheTable::iterator iter = table_.find(key);
	if (iter == table_.end())
	{
		return nullptr;
	}
	typename CacheList::iterator it = iter->second;
	LRUHandle* handle = *(iter->second);
	
	if (it != lru_.begin())
	{
		lru_.erase(it);
		lru_.insert(lru_.begin(), handle);
	}
	++handle->refs;
	return handle;
}

template<typename Key, typename Value>
void LRUCache<Key, Value>::Release(LRUHandle* handle)
{
	assert(handle->refs > 0);
	--handle->refs;
	if (handle->refs == 0)
	{
		usage_ -= handle->charge;
		delete handle;
	}
}

template<typename Key, typename Value>
void LRUCache<Key, Value>::Erase(const Key& key)
{
	typename CacheTable::iterator iter = table_.find(key);
	if (iter != table_.end())
	{
		typename CacheList::iterator it = iter->second;
		Release(*it);
		lru_.erase(it);
		table_.erase(iter);
	}
}

template<typename Key, typename Value>
void LRUCache<Key, Value>::Prune()
{
	for (auto it : lru_)
	{
		if ((*it)->refs == 1)
		{
			auto iter = table_.find((*it)->key);
			if (iter != table_.end())
			{
				table_.erase(iter);
			}
			Release(*it);
		}
	}
}

static const int kNumShardBits = 4;
static const int kNumShards = 1 << kNumShardBits;
template<typename Key, typename Value>
class SharedLRUCache
{
public:
	typedef typename LRUCache<Key, Value>::LRUHandle LRUHandle;
	explicit SharedLRUCache(size_t capacity)
	{
		const size_t per_capacity = (capacity + kNumShards - 1) % kNumShards;
		for (size_t idx = 0; idx < kNumShards; ++idx)
		{
			shard_[idx].set_capacity(per_capacity);
		}
	}
	SharedLRUCache(const SharedLRUCache&) = delete;
	SharedLRUCache(SharedLRUCache&&) = delete;
	SharedLRUCache& operator=(const SharedLRUCache&) = delete;

	LRUHandle* Insert(const Key& key, const Value& value, size_t charge = 1)
	{
		const size_t hash = HashSlice(key);
		return shard_[Shard(hash)].Insert(key, value, charge);
	}

	LRUHandle* LookUp(const Key& key)
	{
		const size_t hash = HashSlice(key);
		return shard_[Shard(hash)].Lookup(key);
	}
	void Release(LRUHandle* handle)
	{
		const size_t hash = HashSlice(handle->key);
		shard_[Shard(hash)].Release(handle);
	}
	void Erase(const Key& key)
	{
		const size_t hash = HashSlice(key);
		shard_[Shard(hash)].Erase(key);
	}
	void Prune()
	{
		for (auto idx : shard_)
		{
			shard_[idx].Prune();
		}
	}
private:
	inline size_t HashSlice(const Key& key)
	{
		return std::hash<Key>(key);
	}
	inline size_t Shard(size_t hash)
	{
		return hash % (kNumShards);
	}
private:
	LRUCache<Key, Value> shard_[kNumShards];
};



}
#endif