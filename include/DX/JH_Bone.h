#pragma once

#include"JH_Model.h"
class JH_Bone
{
	std::wstring m_sBoneName;
	int m_IBoneIndex;
	int m_IParentIndex;
	D3DXMATRIX m_Matworld;
public:
	inline int GetBoneIndex() { return m_IBoneIndex; }
	inline std::wstring GetBoneName() { return m_sBoneName; }
	inline int GetParentIndex() { return m_IParentIndex; }
	inline D3DXMATRIX& GetWorld() { return m_Matworld; }

	inline void SetBoneIndex(int Index) {  m_IBoneIndex= Index; }
	inline void SetBoneName(std::wstring str) { m_sBoneName = str; }
	inline void SetParentIndex(int Index) {m_IParentIndex=Index; }
	inline void SetWorld(D3DXMATRIX mat) { m_Matworld=mat; }
public:
	JH_Bone();
	~JH_Bone();
};

