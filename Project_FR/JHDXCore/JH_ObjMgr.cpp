#include "JH_ObjMgr.h"



	int JH_ObjMgr::CreateObject(const std::string file)
	{

	
		shared_ptr<JH_Obj> pObj = make_shared<JH_Obj>();
		if (!pObj->ReadFile(file)) { return -1;}
		
		pObj->SetID(m_ObjID++);
		m_ObjectList.emplace_back(pObj);

		return m_ObjectList.size()-1;
	}
	void JH_ObjMgr::DeleteObject(int Index)
	{
		auto iter=m_ObjectList.begin()+Index;

		if(iter!=m_ObjectList.end())
		m_ObjectList.erase(iter);
	}
	JH_Obj* JH_ObjMgr::FindObjectByIndex(int Index)
	{

		assert(m_ObjectList[Index]);
		return m_ObjectList[Index].get();


	}
	int	JH_ObjMgr::LoadData(const std::string str)
	{
		
		for (auto ObjData:m_ObjDataList)
		{
			if (ObjData.second->GetName() == str)
			{
				return ObjData.first;
			}
		}
		shared_ptr<JH_ObjData> pObj = make_shared<JH_ObjData>();

		if (pObj->ReadFile(str))
		{
			m_ID++;
			m_ObjDataList.insert(std::make_pair(m_ID, pObj));
			return m_ID;
		}
		return -1;

	}
	JH_ObjData*	JH_ObjMgr::GetDataPtr(int Index)
	{
		ObjIter Iter;
		Iter=m_ObjDataList.find(Index);
		if (Iter != m_ObjDataList.end())
		return Iter->second.get();

		return nullptr;

	}
	JH_ObjData*	JH_ObjMgr::GetDataPtr(std::string str)
	{

		for (auto ObjData : m_ObjDataList)
		{
			if (ObjData.second->GetName() == str)
			{
				return ObjData.second.get();
			}
		}
		return nullptr;
	}
	void JH_ObjMgr::SetCamera(int Index, JHCamera* Camera)
	{
		JH_Obj* Obj=FindObjectByIndex(Index);
		if (Obj != nullptr)
			Obj->SetCamera(Camera);
	}
	void JH_ObjMgr::SetCamera(JHCamera* Camera)
	{
		for (auto obj:m_ObjectList)
		{
			obj->SetCamera(Camera);
		}
	}
	void JH_ObjMgr::SetLightConstantBuffer(ID3D11Buffer* Buffer)
	{
		for (auto obj : m_ObjectList)
		{
			obj->SetLightConstantBuffer(Buffer);
		}
	}
	bool JH_ObjMgr::Frame()
	{
		m_DrawObjectList.clear();
		for (auto Obj : m_ObjectList)
		{
			 
			P_POSITION pos = Obj->GetCamera()->CheckOBBInPlane(Obj->GetColliderBox());
			if (pos != P_BACK)
				m_DrawObjectList.emplace_back(Obj);
			Obj->Frame();
		}
		return true;
	}
	bool JH_ObjMgr::Render()
	{
		for (auto Obj : m_DrawObjectList)
		{
			if (Obj->bColider)
				Obj->RenderCollider();
			Obj->Render();
		}
		return true;
	}
	JH_ObjMgr::JH_ObjMgr()
	{
	}


	JH_ObjMgr::~JH_ObjMgr()
	{
	
	}
