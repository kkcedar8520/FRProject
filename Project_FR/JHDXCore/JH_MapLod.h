#pragma once
#include"JH_Node.h"

	typedef std::vector<JH_Node*> KGNODE_VECTOR;
	class JH_MapLOD
	{
	public:
		std::vector<KGNODE_VECTOR> m_LevelList;
	public:
		void InitLevelOrder(JH_Node* pRootNode, int iMaxDepth);
	public:
		JH_MapLOD();
		virtual ~JH_MapLOD();
	};

