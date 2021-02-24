#include"JH_MapLod.h"

	void  JH_MapLOD::InitLevelOrder(JH_Node* pRootNode, int iMaxDepth)
	{
		m_LevelList.resize(iMaxDepth + 1);
		for (int iLevel = 1; iLevel < iMaxDepth + 1; iLevel++)
		{
			m_LevelList[iLevel].resize(pow(4.0f, iLevel));
		}
		m_LevelList[0].push_back(pRootNode);
	}

	JH_MapLOD::JH_MapLOD()
	{
	}


	JH_MapLOD::~JH_MapLOD()
	{
	}
