#pragma once
#include"JHCamera.h"
#include"JH_Select.h"
#include"JH_ShapeLine.h"
#include"JH_Node.h"
#include"JH_MapLOD.h"

class JH_Map;

	class HQuadTree :public JH_MapLOD
	{
	public:
		bool										m_bFind;
		float										m_fTimer;
		float										m_fdistance;
		float										m_fInterval;
		
	
		int											m_iQuadTreeIndex;

		JH_Node*									m_pRootNode;

		JH_Node*									m_pFindNode;
		JH_Map*										m_pMap;

					

		std::map<int, JH_Node*>						m_NodeList;
		std::map<int,JH_Obj*>						m_ObjectList;
		std::vector<JH_Node*>						m_SelectNodeList;
	
		

		JH_Node*									m_pNearPointNode;
		
		
		std::vector<JH_Node*>						m_ContainObjNode;

		std::vector<JH_Node*>						m_DrawNodeList;
		std::vector < std::shared_ptr<JH_MapObj>>	m_DrawObjectList;
		std::vector<JH_Node*>						m_DrawObjNodeList;

		DWORD										m_dwWidth;
		DWORD										m_dwHeight;
		int											m_iNumFace;

		std::shared_ptr<JH_ShapeLine>	m_BoxLine;
	public:
		//쿼드트리 생성
		BOOL Build(JH_Map* pMap, JHCamera* pCamera);
		BOOL BuildTree(JH_Node* pNode);

		//렌더링할 노드들 선정
		void FindDrawNode(JH_Node* pNode);
		void VisibleNode(JH_Node* pNode);
		BOOL DivideNode(JH_Node*pNode);
		

		
		JH_Node* CreateNode(JH_Node* pParent, DWORD dwTL, DWORD dwTR, DWORD dwBL, DWORD dwBR);
		void	GetSelectNode(JH_Node* pNode);
		JH_Obj*	GetSelectObj();
		bool FindSelectPoint();
		bool FindNearSpecificRangeNode();

		bool ObjectAddNode(JH_Obj* Obj);
		bool GetCotainObjNode(JH_Node* pNode);
		bool ChangeObjectNode(JH_Obj* Obj);
		JH_Node* FindNode(JH_Node* pNode, JH_Obj* Obj);
		void FindObjectNode(JH_Node* pNode, std::shared_ptr<JH_MapObj> Obj);
		void SetNeighborNode(JH_Node* pNode);
		void FindNeighborNode(JH_Node* pNode);


		bool CheckRect(JH_Node* pNode, JH_MapObj* Obj);
		void CreateIndexList(JH_Node* pNode);
		void CreateBB(JH_Node* pNode);
		void ChangeBB(JH_Node* pNode, JH_Box Box);
		int	CheckOBBNodePlane(JH_Node* pNode, JH_Box& box);



		JH_Node* FindIDNode(JH_Node* pNode, JH_MapObj* Obj);
		
		void DirectSelect(JH_Node* pNode);
		void Set();
		bool Frame();
		bool Render();
		bool Release();
		bool Draw(JH_Node* pNode, ID3D11DeviceContext* pContext);
		void DrawNodeLine(JH_Node* pNode);
		void DrawLine(JH_Node* pNode);
		void DrawObjectBoxLine();
	public:
		bool FindInterSection();
		void FindNearInterSectionNode(JH_Node* pNode, D3DXVECTOR3 vInterSection);
		


	public:
		HQuadTree();
		virtual ~HQuadTree();
	};
