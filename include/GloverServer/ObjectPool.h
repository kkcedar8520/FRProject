#pragma once


//_aligned_mallco 가상 메모리까지 정렬해서 할당해준다.
//MEMORY_ALLOCATION

#include"Lock.h"

template<class T> 
class ObjectPool
{
public:
	enum 
	{
		POOL_MAX_SIZE = 2048,
		POOL_MASK_SIZE=POOL_MAX_SIZE-1,
	};
public:
	static bool Init()
	{
		for (int i = 0; i < POOL_MAX_SIZE; i++)
		{
			m_ObjectPool[i] = _aligned_malloc(sizeof(T), MEMORY_ALLOCATION_ALIGNMENT); //MEMORY_ALLOCATION_ALIGNMENT 메모리를 조정할당해라
		}
		m_TailPos = POOL_MAX_SIZE;
		return true;
	}
	static bool Release()
	{
		for (int  i = 0; i < POOL_MAX_SIZE; i++)
		{
			void* pValue = InterlockedExchangePointer(&m_ObjectPool[i], nullptr);
			if (pValue != nullptr)
			{
				_aligned_free(pValue);
			}
		}
	}

	void* operator new(size_t size)
	{
		long long pos = InterlockedIncrement64(&m_HeadPos) - 1;
		void* pObj = InterlockedExchangePointer(&m_ObjectPool[pos&POOL_MASK_SIZE], nullptr);
		if (pObj!=nullptr)
		{
			return pObj;
		}
		else
		{
			return _aligned_malloc(sizeof(size), MEMORY_ALLOCATION_ALIGNMENT);
		}
	}
	void operator delete(void*pObj)
	{
		long long pos = InterlockedIncrement64(&m_TailPos) - 1;
		void* pPoolObj = InterlockedExchangePointer(&m_ObjectPool[pos&POOL_MASK_SIZE], pObj);
		if (pPoolObj!=nullptr)
		{
			_aligned_free(pPoolObj);
		}
	}

private:
	static void* volatile m_ObjectPool[POOL_MAX_SIZE];
	static long long volatile m_HeadPos;
	static long long volatile m_TailPos;
};

template<class T>
void* volatile ObjectPool<T>::m_ObjectPool[POOL_MAX_SIZE]=NULL;
template<class T>
static long long volatile m_HeadPos=0;
template<class T>
static long long volatile m_TailPos= 0;