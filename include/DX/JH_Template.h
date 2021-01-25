#pragma once
#include"JH_DXStd.h"
namespace HTemplate {


	template<typename Child> class HTemplateMap
	{
	public:
		typedef unordered_map <int, Child*>		TemplateMap;		//Map은 순서를 저장하여 돌리는 트리지만 unordered_Map은 순서를 저장하지않는다
		typedef typename TemplateMap::iterator	TemplateMapItor;	//그래서 객체 숫자가 많아지면 많아질수록 속도차이가 많이남 시간복잡도 O(logN) O(N)
		TemplateMapItor							HItor;
		TemplateMap								HMap;
		int										m_iCurIndex;
	public:
		virtual	bool	Init();
		virtual bool	Frame();
		virtual bool	Render();
		//해당 템플릿객체 전부삭제
		virtual bool	Release();

		virtual Child* const Getptr(int index);// 객체 인덱스로 객체를 리턴받음
		virtual Child* const Getptr(const TCHAR* szName);

		virtual int		GetID(Child*);//객체의 인덱스를 리턴받음
		virtual int		GetID(const TCHAR* szName);//객체의 이름으로 인덱스를 리턴받음

		virtual int		Count();//전체 저장된 객체의 갯수
		virtual bool	Delete(int Index);//해당 인덱스 객체 삭제
		virtual bool	Delete(Child* pPoint)//해당 포인터 객체 삭제
	
	};


	template<typename Child>
	bool	HTemplateMap<Child>::Init()
	{
		m_iCurIndex = 0;
		HMap.clear();
		return true;
	}
	template<typename Child>
	bool	HTemplateMap<Child>::Frame()
	{

		for (TemplateMapItor itor = HMap.begin(); TemplateMapItor !=HMap.end(); itor++)
		{
			Child* pPoint = (Child*)(*itor).second;
			if (pPoint)
				pPoint->Frame();
		}
		return true;
	}
	template<typename Child>
	bool	HTemplateMap<Child>::Render()
	{

		for (TemplateMapItor itor = HMap.begin(); TemplateMapItor !=HMap.end(); itor++)
		{
			Child* pPoint = (Child*)(*itor).second;
			if (pPoint)
				pPoint->Render();
		}
		return true;
	}

	template<typename Child>
	bool	HTemplateMap<Child>::Release()
	{

		for (TemplateMapItor itor = HMap.begin(); TemplateMapItor != HMap.end(); itor++)
		{
			Child* pPoint = (Child*)(*itor).second;
			if (pPoint)
				pPoint->Release()
			else
				return false;
			delete pPoint;
		}
		HMap.clear();
		m_iCurIndex = 0;

		return true;
	}

	template<typename Child>
	Child* const HTemplateMap<Child>::Getptr(int index)
	{
		TemplateMapItor itor = HMap.find(index);
		if (itor == HMap.end())return NULL;
		Child *pPoint = (*itor).second;
		return pPoint;
	 }
	
	template < class Child >
	Child* const HTemplateMap< Child >::Getptr(const TCHAR* szName)
	{
		for (TemplateMapItor itor = TMap.begin(); itor != TMap.end(); itor++)
		{
			Child *pPoint = (Child *)(*itor).second;
			if (!_tcsicmp(pPoint->m_szName.c_str(), szName))
			{
				return pPoint;
			}
		}
		return NULL;
	}
	template < class Child >
	int HTemplateMap< Child >::GetID(Child* pChild)
	{
		int iIndex = -1;
		for (TemplateMapItor itor = TMap.begin(); itor != TMap.end(); itor++)
		{
			Child *pPoint = (Child *)(*itor).second;
			if (pChild == pPoint)
			{
				iIndex = (*itor).first;
				break;
			}
		}
		return iIndex;
	}
	
	template < class Child >
	int HTemplateMap< Child >::GetID(const TCHAR* szName)
	{
		int iIndex = -1;
		for (TemplateMapItor itor = TMap.begin(); itor != TMap.end(); itor++)
		{
			Child *pPoint = (Child *)(*itor).second;
			if (!_tcsicmp(pPoint->m_szName.c_str(), szName))
			{
				iIndex = (*itor).first;
				break;
			}
		}
		return iIndex;
	}

	template < class Child >
	bool HTemplateMap< Child >::Delete(int iIndex)
	{
		Child* const pPoint = GetPtr(iIndex);
		if (pPoint)
		{
			pPoint->Release();
			TMap.erase(iIndex);
		}
		return true;
	}
	template < class Child >
	bool HTemplateMap< Child >::Delete(Child *pPoint)
	{
		if (pPoint)
		{
			pPoint->Release();
			TMap.erase(GetID(pPoint));
		}
		return true;
	}
}

