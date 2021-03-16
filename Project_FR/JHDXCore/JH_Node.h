#pragma once
#include"JH_DXStd.h"
#include"JH_MapObj.h"


	class JH_Node
	{
	public:
		JH_Box m_Box;
		JH_PLANE											m_BoxPlane[6];
		std::vector<JH_Node*>								m_NeighborNodeList;
		std::map<int, JH_Obj*>								m_ObjList;
		BOOL												m_isLeaf;
		DWORD												m_dwDepth;
		DWORD												m_dwCorner[4];// 꼭지점 네점
		int													m_iQuadTreeIndex;
		JH_Node*											m_pChild[4];
		std::vector<DWORD>									m_IndexList;

		//이웃노드를 얻기위한 위치정보
		DWORD							m_dwPositionIndex[2];

		Microsoft::WRL::ComPtr<ID3D11Buffer> m_pIndexBuffer;
	public:
		JH_Node();
		virtual ~JH_Node();


	};
