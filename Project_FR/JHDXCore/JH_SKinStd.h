#pragma once
#include"JH_ObjStd.h"
struct HTriSkin
{
	PNCTIW_VERTEX	v[3];
	int			iSubIndex;
	HTriSkin()
	{
		iSubIndex = -1;
	}
};

class HMeshSkin:public HMesh
{
public:
	vector<PNCTIW_VERTEX> m_vbSkinList;
	vector<HTriSkin> m_SkinTriList;
	vector<HMeshSkin> subMesh;
public:
	HMeshSkin() {};
	~HMeshSkin() {};

private:

};

