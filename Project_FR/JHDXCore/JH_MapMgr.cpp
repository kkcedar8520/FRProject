#pragma once
#include "JH_MapMgr.h"
#include"JH_ObjMgr.h"
#include"JH_ObjMgr.h"






	JH_MapMgr::JH_MapMgr()
	{
		m_ObjID = 0;
	}


	JH_MapMgr::~JH_MapMgr()
	{
	}

	TCHAR* JH_MapMgr::FixupName(T_STR name)
	{
		memset(m_tmpBuffer, 0, sizeof(TCHAR)*MAX_PATH);

		TCHAR* cPtr;
		_tcscpy(m_tmpBuffer, name.c_str());
		cPtr = m_tmpBuffer;

		while (*cPtr)
		{
			if (*cPtr == '"')		*cPtr = SINGLE_QUOTE;
			else if (*cPtr == ' ' || *cPtr <= CTL_CHARS)
				*cPtr = _T('_');
			cPtr++;
		}
		return m_tmpBuffer;
	}
	void JH_MapMgr::Set(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, JHCamera* pCamera, JH_Select* select)
	{
		m_pd3dDevice = pDevice;
		m_pContext = pContext;
		m_pCamera = pCamera;
		m_pSelect = select;
	}

bool JH_MapMgr::SaveMapData(const std::string File)
{
	std::shared_ptr<JH_Map> pMap = GetMap();
	std::shared_ptr<HQuadTree> pQuadTree = GetCurrentQuadTree();

	unique_ptr<BinaryWriter> Writer = make_unique< BinaryWriter>();
	
	Writer->Open(File);
	//Resource name
	Writer->String(pMap->m_TextureFileName);
	Writer->String(pMap->m_pNormMapFileName);
	Writer->String(pMap->m_HegithFileName);
	Writer->String(pMap->m_ShaderFileName);
	Writer->String(pMap->m_AlphaTextureName);

	//SPLATTING TEXTURE NAME
	Writer->Int(pMap->m_vSplattTextureList.size());
	for (int i = 0; i < pMap->m_vSplattTextureList.size(); i++)
	{
		Writer->String(FixupName(pMap->m_vSplattTextureList[i]->m_szPath + pMap->m_vSplattTextureList[i]->m_szName));
	}


	Writer->Int(pMap->m_iColumNum );
	Writer->Int(pMap->m_iRowNum);
	Writer->Int(pMap->m_iVertices);
	Writer->Int(pMap->m_iCellCol);
	Writer->Int(pMap->m_iCellRow);
	Writer->Int(pMap->m_iCellCount);
	Writer->Float(pMap->m_fCellDistance);
	Writer->Float(pMap->m_fScaleHeight);



	Writer->Int(pMap->m_VertexData.size()); 
	Writer->Byte(&pMap->m_VertexData.at(0),sizeof(PNCT_VERTEX),pMap->m_VertexData.size());
	Writer->Int(pMap->m_IndexData.size());
	Writer->Byte(&pMap->m_IndexData.at(0), sizeof(DWORD), pMap->m_IndexData.size());
	if (pMap->m_QuadTree == nullptr)
	{
		Writer->Bool(false);
		Writer->Close();
		return true; 
	}
		Writer->Bool(true);
		Writer->Dword(pMap->m_QuadTree->m_dwWidth);
		Writer->Dword(pMap->m_QuadTree->m_dwHeight);
		Writer->Int(pMap->m_QuadTree->m_iNumFace);
		SaveToQuadTree(pMap->m_QuadTree.get(),pMap->m_QuadTree->m_pRootNode, Writer.get());
		

	



	Writer->Close();
	return true;
}
std::shared_ptr<JH_Map> JH_MapMgr::LoadMap(const std::string File)
{




	unique_ptr<BinaryReader> Reader = make_unique< BinaryReader>();

	Reader->Open(File);
	//Resource name

	shared_ptr<LEVEL> pLevel = make_shared<LEVEL>();
	pLevel->m_pMap = make_shared< JH_Map>();
	pLevel->MapFileName = File;
	m_CurrentMap = pLevel;
	m_GMDataList.emplace_back(pLevel);


	JH_Map* pMap = pLevel->m_pMap.get();


	pMap->m_TextureFileName		= Reader->WString();
	pMap->m_pNormMapFileName	= Reader->WString();
	pMap->m_HegithFileName		= Reader->WString();
	pMap->m_ShaderFileName		= Reader->WString();
	pMap->m_AlphaTextureName	= Reader->WString();



	//SPLATTING TEXTURE NAME
	int iNum= Reader->Int();
	for (int i = 0; i < iNum; i++)
	{
		std::wstring file=Reader->WString();
		pMap->AddSplattTexture(file.c_str(),i+1);
	}


	pMap->m_iColumNum=Reader->Int();
	pMap->m_iRowNum=Reader->Int();
	pMap->m_iVertices = Reader->Int();
	pMap->m_iCellCol = Reader->Int();
	pMap->m_iCellRow = Reader->Int();
	pMap->m_iCellCount = Reader->Int();
	pMap->m_fCellDistance = Reader->Float();
	pMap->m_fScaleHeight = Reader->Float();
	


	pMap->m_VertexData.resize(Reader->Int());
	Reader->Byte(&pMap->m_VertexData.at(0), sizeof(PNCT_VERTEX), pMap->m_VertexData.size());

	pMap->m_IndexData.resize(Reader->Int());
	Reader->Byte(&pMap->m_IndexData.at(0), sizeof(DWORD), pMap->m_IndexData.size());



	pMap->SetDevice(DX::GetDevice().Get());
	pMap->SetDeviceContext(DX::GetContext().Get());
	pMap->LoadShader(pMap->m_ShaderFileName.c_str());
	pMap->CreateVertexBuffer();
	pMap->CreateIndexBuffer();
	pMap->CreateConstantBuffer();
	pMap->CreateInputLayout();
	pMap->LoadTexture(pMap->m_TextureFileName.c_str(),pMap->m_pNormMapFileName.c_str());
	pMap->UpdateTangentBuffer();

	bool bQuad=Reader->Bool();
	if (!bQuad ) { Reader->Close(); return  pLevel->m_pMap; }
	pMap->m_QuadTree = make_shared<HQuadTree>();
	pMap->m_QuadTree->m_pMap = pMap;


	pMap->m_QuadTree->m_dwWidth=Reader->Dword();
	pMap->m_QuadTree->m_dwHeight=Reader->Dword();
	pMap->m_QuadTree->m_iNumFace=Reader->Int();
	SAFE_NEW(pMap->m_QuadTree->m_pRootNode, JH_Node);
	LoadToQuadTree(pMap->m_QuadTree.get(), pMap->m_QuadTree->m_pRootNode, Reader.get());
	
	pMap->m_QuadTree->Set();
	Reader->Close();



	return pLevel->m_pMap;
}
	
	INT JH_MapMgr::AddGameMap(std::shared_ptr<JH_Map> pMap)
	{
		std::shared_ptr <LEVEL>  GM;
		GM = std::make_shared<LEVEL>();
		GM->m_pMap = pMap;
		

		m_CurrentMap = GM;
		
		m_GMDataList.push_back(GM);
		return 1;

	}
	//오브젝트 바운딩 박스 추가해야함
	//INT JH_MapMgr::AddObject(OBJECT Obj)
	//{

	//	std::shared_ptr<CBY::CBY_Object> Object;
	//	Object =std::make_shared<CBY::CBY_Object>();
	//	Object->Create(m_pd3dDevice, m_pContext, L"../../data/shader/ObjectShader.txt", nullptr, "VSOBJECT", "PS");
	//	Object->SkinLoad(Obj.m_MapObj->m_SkinName);
	//	Object->BoneLoad(Obj.m_MapObj->m_BoneName);

	//	Object->m_matWorld = Obj.m_MapObj->m_matWorld;
	//	std::shared_ptr<JH_MapObj> MapObj= std::make_shared< JH_MapObj>();
	//	MapObj->SetBoneName(Obj.m_MapObj->m_BoneName);
	//	MapObj->SetSkinName(Obj.m_MapObj->m_SkinName);
	//	MapObj->SetQuadIndex(Obj.m_MapObj->m_iQuadTreeIndex);
	//	MapObj->SetObj(Object);
	//	MapObj->SetFlag(Obj.m_MapObj->m_Flag);
	//	MapObj->SetID(m_ObjID++);
	//	
	//	MapObj->GetObj()->SetMatrix(&MapObj->GetObj()->m_matWorld, &m_pCamera->m_View, &m_pCamera->m_Proj);
	//	
	//	int ind=MapObj->GetQuadIndex();
	//	m_CurrentMap->m_pQuadTree->m_NodeList[ind]->m_ObjList.insert(std::make_pair(MapObj->GetID(), MapObj));
	//	m_CurrentMap->m_pQuadTree->m_ObjectList.insert(std::make_pair(MapObj->GetID(), MapObj));
	//	I_ObjMgr.AddObject(MapObj);
	//	//m_CurrentMap->m_pQuadTree->GetObjectAddNode(MapObj);
	//	return 1;

	//}

	std::shared_ptr<JH_Map> JH_MapMgr::CreateMap(std::string MapName,int iWidth,
		int iHeight,
		int iCellCount,
		int iCellSize,
		const TCHAR* pTexturFileName,
		const TCHAR* pNormalMapFileName,
		const TCHAR* pHeightMapFileName,
		bool bQuad)
	{


		shared_ptr<LEVEL> pLevel = make_shared<LEVEL>();
		
		pLevel->MapFileName = MapName;
		
		pLevel->m_pMap = make_shared<JH_Map>();

	
		
		pLevel->m_pMap->CreateMap(iWidth, iHeight, iCellCount, iCellSize, pTexturFileName, pNormalMapFileName, pHeightMapFileName,nullptr,bQuad);


		m_CurrentMap = pLevel;
		m_GMDataList.emplace_back(pLevel);
		return pLevel->m_pMap;
	}

	void JH_MapMgr::SaveToQuadTree(HQuadTree* QuadTree, JH_Node* pNode, BinaryWriter* Writer)
	{
		if (pNode == nullptr)return;

		//BOOL	BL[1];
		//int		ibuf[6] = {};
		//DWORD	Dbuf[5] = {};
		//float	fbuf[40] = {};
		//TCHAR Temp[256] = {};
		//TCHAR cbuf[256] = {};
		//
		////Dbuf[0] = pNode->m_dwPositionIndex[0];
		////Dbuf[1] = pNode->m_dwPositionIndex[1];
		////fwrite((void*)Dbuf, sizeof(DWORD), 2, fp);


		Writer->Byte(&pNode->m_Box.vMin, sizeof(D3DXVECTOR3), 1);
		Writer->Byte(&pNode->m_Box.vMax, sizeof(D3DXVECTOR3), 1);
		Writer->Byte(&pNode->m_Box.vCenter, sizeof(D3DXVECTOR3), 1);
		Writer->Byte(&pNode->m_Box.vAxis, sizeof(D3DXVECTOR3), 3);
		Writer->Byte(&pNode->m_Box.fExtent, sizeof(float), 3);
		Writer->Float(pNode->m_Box.fExtentXZ);
	

		Writer->Byte(&pNode->m_BoxPlane, sizeof(JH_PLANE), 6);

		Writer->Int(pNode->m_ObjList.size());
		for (auto obj : pNode->m_ObjList)
		{
			Writer->String(obj.second->GetName());
			Writer->Int(obj.second->GetID());
			Writer->Byte(&obj.second->m_matWorld, sizeof(D3DXMATRIX), 1);
			Writer->Byte(&obj.second->m_matTransform, sizeof(D3DXMATRIX), 1);
		}
		Writer->Bool(pNode->m_isLeaf);
		Writer->Byte(&pNode->m_dwDepth, sizeof(DWORD), 1);
		Writer->Byte(&pNode->m_dwCorner, sizeof(DWORD), 4);
		Writer->Int(pNode->m_iQuadTreeIndex);


	

		/*ibuf[0] = pNode->m_NeighborNodeList.size();
		fwrite((void*)ibuf, sizeof(int),1, fp);
		for (auto Node : pNode->m_NeighborNodeList)
		{
			if (Node)
			{
				ibuf[0] = Node->m_iQuadTreeIndex;
				fwrite((void*)ibuf, sizeof(int), 1, fp);
			}
		}*/
		Writer->Int(pNode->m_IndexList.size());
		if(pNode->m_IndexList.size()>0)
		Writer->Byte(&pNode->m_IndexList.at(0), sizeof(DWORD), pNode->m_IndexList.size());
		
		
		for (int iNode = 0; iNode < 4; iNode++)
		{
			if (pNode->m_pChild[iNode] != nullptr)
			{
				SaveToQuadTree(QuadTree,pNode->m_pChild[iNode], Writer);

			}
		}


	}
	void JH_MapMgr::LoadToQuadTree(HQuadTree* QuadTree, JH_Node* pNode, BinaryReader* Reader)
	{
		if (pNode == nullptr)return;

		//int		ibuf[6] = {};
		//DWORD	Dbuf[4] = {};
		//float	fbuf[40] = {};
	
		//TCHAR Temp[256] = {};
		//TCHAR cbuf[256] = {};
		//BOOL  Bf [1] = { };

		//



		//fread((void*)Dbuf, sizeof(DWORD), 2, fp);
		//pNode->m_dwPositionIndex[0]	=	Dbuf[0];
		//pNode->m_dwPositionIndex[1] =	Dbuf[1];




	
		Reader->Byte(&pNode->m_Box.vMin, sizeof(D3DXVECTOR3), 1);
		Reader->Byte(&pNode->m_Box.vMax, sizeof(D3DXVECTOR3), 1);
		Reader->Byte(&pNode->m_Box.vCenter, sizeof(D3DXVECTOR3), 1);
		Reader->Byte(&pNode->m_Box.vAxis, sizeof(D3DXVECTOR3), 3);
		Reader->Byte(&pNode->m_Box.fExtent, sizeof(float), 3);
		pNode->m_Box.fExtentXZ=Reader->Float();
		Reader->Byte(&pNode->m_BoxPlane, sizeof(JH_PLANE), 6);

		int iNum = Reader->Int();
		int iObj,iD;
		for (int i=0;i<iNum;i++)
		{
			std::string str;
			str =Reader->String();
			iD =Reader->Int();


			iObj = I_ObjMgr.CreateObject(str);
			JH_Obj*pObj = I_ObjMgr.GetPtr(iObj).get();
			pObj->SetID(iD);
			pNode->m_ObjList.insert(make_pair(pObj->GetID(), pObj));
			Reader->Byte(&pObj->m_matWorld, sizeof(D3DXMATRIX), 1);
			Reader->Byte(&pObj->m_matTransform, sizeof(D3DXMATRIX), 1);

		}
		pNode->m_isLeaf=Reader->Bool();
		Reader->Byte(&pNode->m_dwDepth, sizeof(DWORD), 1);
		Reader->Byte(&pNode->m_dwCorner, sizeof(DWORD), 4);
		pNode->m_iQuadTreeIndex=Reader->Int();

		///*fread((void*)ibuf, sizeof(int), 1, fp);
		//pNode->m_NeighborNodeList.resize(ibuf[0]);

		//for (auto Node : pNode->m_NeighborNodeList)
		//{
		//	if (Node)
		//	{
		//		fread((void*)ibuf, sizeof(int), 1, fp);
		//		Node->m_iQuadTreeIndex = ibuf[0];
		//	}
		//}*/

		pNode->m_IndexList.resize(Reader->Int());
		if (pNode->m_IndexList.size() > 0)
		{
			Reader->Byte(&pNode->m_IndexList.at(0), sizeof(DWORD), pNode->m_IndexList.size());
			pNode->m_pIndexBuffer.Attach(DX::CreateIndexBuffer(
				DX::GetDevice().Get(),
				&pNode->m_IndexList.at(0),
				pNode->m_IndexList.size(), sizeof(DWORD)));
		}
		for (int iNode = 0; iNode < 4; iNode++)
		{
			if (!pNode->m_isLeaf)
				SAFE_NEW(pNode->m_pChild[iNode], JH_Node);
			if (pNode->m_pChild[iNode]!= nullptr)
			{
				LoadToQuadTree(QuadTree,pNode->m_pChild[iNode], Reader);

			}
		}


	}
	void JH_MapMgr::SetCamera(JHCamera* Camera)
	{
		if (m_CurrentMap == nullptr)return;
		m_CurrentMap->m_pMap->SetCamera(Camera);
	}
	bool JH_MapMgr::Frame()
	{
		if (m_CurrentMap == nullptr) return false;

		m_CurrentMap->m_pMap->Frame();

		
		return true;
	}
	bool JH_MapMgr::Render()
	{
		if (m_CurrentMap == nullptr) return false;
		m_CurrentMap->m_pMap->Render();
		return true;
	}
	bool JH_MapMgr::Release()
	{
		return true;
	}
