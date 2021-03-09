#pragma once
#include"JH_Obj.h"
#include"JH_MapObj.h"

	class JH_ObjMgr :public Singleton<JH_ObjMgr>
	{
		friend class Singleton<JH_ObjMgr>;
		using ObjIter = std::map<int, std::shared_ptr<JH_ObjData>>::iterator;
	private:
		std::map<int, std::shared_ptr<JH_ObjData>>	m_ObjDataList;
		std::vector<std::shared_ptr<JH_Obj>>		m_ObjectList;
		std::vector<shared_ptr<JH_Obj>>				m_DrawObjectList;

		int m_ObjID = 0;
		int m_ID=0;

	public:
		void		AddObject(std::shared_ptr<JH_Obj> Obj);
		int			CreateObject(const std::string file);
		void		DeleteObject(int Index);
		JH_Obj*		FindObjectByIndex(int Index);
		int			LoadData(const std::string);
		JH_ObjData*	GetDataPtr(int Index);
		JH_Obj*		GetPtr(int Index) { return m_ObjectList[Index].get(); }
		void		SetCamera(int Index, JHCamera* Camera);
	public:
		bool Frame();
		bool Render();
	public:
		JH_ObjMgr();
		virtual ~JH_ObjMgr();
	};

#define I_ObjMgr JH_ObjMgr::GetInstance()
