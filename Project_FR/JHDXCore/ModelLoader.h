#pragma once

#include"JH_Mesh.h"
#include"JH_Obj.h"
#include"BinaryWriter.h"
#include"TextureMgr.h"
#include"LoadType.h"

class BinaryWriter;

class ModelLoader

{

private:
	
	const aiScene*					m_pScene;        //모델 정보

	vector<asBone>					m_Bones;		//본 정보
	vector<asMaterial>				m_Materials;	//메테리얼 정보
	vector<asMesh>					m_meshes;        //매쉬 정보

	

	//vector<pair<string, Bone>>		m_Bones;        //뼈 정보

	UINT                            m_numVertices;

	UINT                            m_numMaterial;

	ID3D11Device*					m_pDevice;
	Assimp::Importer * importer;

	JH_ColliderBox					m_ColiderBox;

	std::wstring WTextureName;

	//Animation;
	std::unique_ptr<asClip>			m_asClip;
	std::vector<asClipNode>			m_vClipNode;
public:
	ModelLoader();
	~ModelLoader();

	

	void ModelLoad(const string& fileName,ID3D11Device* pDevice);
	//Animation Export
	void ExportAnimClip(const std::string& fileName);
	void ReadClipData(int AnimIndex);
	void ReadKeyFrameData(aiNode* Node);
	void WriteAniClip(const string& fileName);
	


	
	

	//ExportModel
	bool ReadBoneData(aiNode* Node,int Index,int iParentIndex);
	bool ReadMeshData(aiNode* Node,int IBoneIndex);
	bool ReadMaterial();


	bool WriteModelBinary(const std::string FilePath);
		

	UINT                getNumMesh() const { return (UINT)m_meshes.size(); }

};
