#pragma once
#include "Importer.hpp"
#include "cimport.h"
#include "postprocess.h"
#include "scene.h"
struct asMaterial
{
	std::wstring Name;

	D3DXVECTOR4 AmbientColor;
	D3DXVECTOR4 DiffuseColor;
	D3DXVECTOR4 SpecularColor;
	D3DXVECTOR4 EmissiveColor;

	std::wstring Diffuse;
	std::wstring Specular;
	std::wstring Emissive;
	std::wstring Normal;
};
struct asBone
{
	std::wstring BoneName;

	INT iBoneIndex;
	INT iBoneParentIndex;

	D3DXMATRIX m_Matworld;
};
struct asMesh
{

	std::wstring Name;
	int IBoneIndex;

	std::wstring MaterialName;

	vector<PNCTIW_VERTEX> m_Vertices;
	vector<DWORD>m_Indices;

	aiMesh m_mesh;

};

struct asFrameData
{
	float			Frame;
	
	D3DXVECTOR3		vPosition;
	D3DXQUATERNION	qRotation;
	D3DXVECTOR3		vScale;
};
struct asKeyFrame
{
	std::string BoneName;
	std::vector<asFrameData> Transform;
};
struct asClipNode
{
	std::string Name;
	std::vector<asFrameData> KeyFrame;
};

struct asClip
{
	std::string Name;
	float Duration;
	float FrameCount;
	float FrameRate;

	vector<asKeyFrame> vKeyFrame;
};