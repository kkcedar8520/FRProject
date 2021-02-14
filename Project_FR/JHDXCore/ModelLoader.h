#pragma once

#include "Importer.hpp"
#include "cimport.h"
#include "postprocess.h"
#include "scene.h"
#include"JH_Mesh.h"
#include"JH_Obj.h"
#include"BinaryWriter.h"
#include"TextureMgr.h"

class BinaryWriter;
struct cMaterial
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
struct cBone
{
	std::wstring BoneName;

	INT iBoneIndex;
	INT iBoneParentIndex;

	D3DXMATRIX m_Matworld;
};
struct cMesh
{
	
	std::wstring Name;
	int IBoneIndex;

	std::wstring MaterialName;
	
	vector<PNCTIW_VERTEX> m_Vertices;
	vector<DWORD>m_Indices;

	aiMesh m_mesh;

};
class ModelLoader

{

private:
	
	const aiScene*					m_pScene;        //�� ����

	vector<cBone>					m_Bones;		//�� ����
	vector<cMaterial>				m_Materials;	//���׸��� ����
	vector<cMesh>					m_meshes;        //�Ž� ����


	//vector<pair<string, Bone>>		m_Bones;        //�� ����

	UINT                            m_numVertices;

	UINT                            m_numMaterial;

	ID3D11Device*					m_pDevice;
	Assimp::Importer * importer;

	int m_iBaseIndex;
	int m_iVertexIndex;

	std::wstring WTextureName;
public:
	ModelLoader();
	~ModelLoader();

	void InitScene();

	void ModelLoad(const string& fileName,JH_Obj& Obj,ID3D11Device* pDevice);




	
	
	//void Import(const string& fileName);

	bool ReadBoneData(aiNode* Node,int Index,int iParentIndex);
	bool ReadMeshData(aiNode* Node,int IBoneIndex);
	bool ReadMaterial();


	bool WriteModelBinary(const std::string FilePath);
		

	UINT                getNumMesh() const { return (UINT)m_meshes.size(); }

};
