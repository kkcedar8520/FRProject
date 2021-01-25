
#include"HNode.h"

//void Lookup_Node();

template<class T>
class HLinkedList
{
public:

	H_Node<T>*	m_phead;
	H_Node<T>*	m_ptail;
	int icount;
public:
	void FrontInsert(T* pdata);
	void AllDel();
	void DelLink(H_Node<T>* pDelNode);
	void AddLink(T*pdata);
	T* FindData(int index);
public:
	HLinkedList();
	~HLinkedList();
};


template <class T>
void HLinkedList<T>::AllDel()
{
	while (m_phead == nullptr)
	{
		H_Node<T>* pCur = m_phead;
		m_phead = m_phead->m_pNext;
		delete pCur;
	}
}
template <class T>
void HLinkedList<T>::DelLink(H_Node<T>* pDelNode)
{
	H_Node<T>* pCur = pDelNode->m_pPrev;
	pCur->m_pNext = pDelNode->m_pNext;
	delete pDelNode;
}
template<class T>
void HLinkedList<T>::AddLink(T*pdata)
{
	H_Node<T>*pNode = new H_Node<T>();
	pNode->m_pdata = pdata;

	if (m_phead == nullptr)
	{
		m_phead = pNode;
		m_ptail = pNode;
	}
	else
	{
		m_ptail->m_pNext = pNode;
		pNode->m_pPrev = m_ptail;
		m_ptail = pNode;
	}

}
template<class T>
T* HLinkedList<T>::FindData(int index)
{
	H_Node<T>*pCur = m_phead;

	while (pCur !=nullptr)
	{
		if (pCur->m_pdata->GetIndex() == index)
		{
			T*pdata = pCur->m_pdata;
			return pdata;
		}
		pCur = pCur->m_pNext;
	}
	return nullptr;
}
//template<class T>
////void Linkedlist<T>::FrontInsert(T* pdata)
////{
////	T_Node<T>*pNode = new T_Node<T>();
////	pNode->m_pdata = pdata;
////
////}
template<class T>
HLinkedList<T>::HLinkedList()
{
	m_phead = nullptr;
	m_ptail = nullptr;
	icount = 0;
}

template<class T>
HLinkedList<T>::~HLinkedList()
{

}
//template<class T>
//void Lookup_Node(T_Node<T>*m_phead)
//{
//	T_Node<T>*pCur = m_phead;
//
//	while (pCur != NULL)
//	{
//		if (pCur->m_pdata->GetIndex() == index)
//		{
//			T*pdata = pCur->m_pdata;
//			return pdata;
//		}
//		pCur = pCur->m_pNext;
//	}
//	return NULL;
//}