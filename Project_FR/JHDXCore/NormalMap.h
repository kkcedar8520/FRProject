#pragma once
#include"JH_DXStd.h"
class NormalMap
{
public:
	void CreateTangentSpaceVectors(D3DXVECTOR3 *v1, D3DXVECTOR3 *v2, D3DXVECTOR3 *v3,
		float v1u, float v1v,
		float v2u, float v2v,
		float v3u, float v3v,
		D3DXVECTOR3 *vTangent);
};

