#pragma once

#include"JH_Model.h"
class JH_Bone
{
	std::string m_sBoneName;
	int m_IBoneIndex;
	int m_IParentIndex;
	D3DXMATRIX m_Matworld;
public:
	inline int GetBoneIndex() { return m_IBoneIndex; }
	inline std::string GetBoneName() { return m_sBoneName; }
public:
	JH_Bone();
	~JH_Bone();
};

