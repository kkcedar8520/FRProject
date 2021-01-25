#pragma once
#include"JH_Map.h"
#include"JHCamera.h"
#include"JH_Select.h"
#include"JH_ShapeLine.h"
#include"JH_BaseObj.h"

class HNode
{
public:
	BOUNDINGBOX m_Box;
	vector<int> m_ObjList;


	BOOL	m_isLeaf;
	DWORD	m_dwDepth;
	DWORD	m_dwCorner[4];// 꼭지점 네점
	HNode*	m_pChild[4];
	vector<DWORD> m_IndexList;
	ComPtr<ID3D11Buffer> m_pIndexBuffer;
public:
	HNode() {}
	virtual ~HNode()
	{
		for (int  iNode = 0; iNode < 4; iNode++)
		{
			SAFE_DEL(m_pChild[iNode]);
		}
	}

};

class HQuadTree
{
public:
	float m_fTimer;
	HNode* m_pRootNode;
	JH_Map* m_pMap;
	JHCamera* m_pCamera;
	vector<HNode*>  m_SelectNodeList;

	vector<HNode*>  m_DrawNodeList;
	vector<HNode*>  m_DrawObjNodeList;
	shared_ptr<JH_ShapeLine>	m_BoxLine;
public:
	BOOL Build(JH_Map* pMap, JHCamera* pCamera);
	BOOL BuildTree(HNode* pNode);
	void DrawFindNode(HNode* pNode);
	void VisibleNode(HNode* pNode);
	BOOL DivideNode(HNode*pNode);
	void DrawNodeLine(HNode* pNode);
	void DrawLine(HNode* pNode);
	HNode* CreateNode(HNode* pParent, DWORD dwTL, DWORD dwTR, DWORD dwBL, DWORD dwBR);
	void  GetSelectNode(HNode* pNode);
	void CreateIndexList(HNode* pNode);
	void CreateBB(HNode* pNode);
	void DirectSelect(HNode* pNode);
	void Set();
	bool Frame();
	bool Render();
	bool Release();
	bool Draw(HNode* pNode, ID3D11DeviceContext* pContext);
public:
	bool FindInterSection();
public:
	HQuadTree();
	virtual ~HQuadTree();
};

