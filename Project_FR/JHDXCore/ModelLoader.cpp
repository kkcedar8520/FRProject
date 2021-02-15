#include "ModelLoader.h"

ModelLoader::ModelLoader()
{
	//importer = new Assimp::Importer();
}
ModelLoader::~ModelLoader()
{
	//delete importer;
}
void ModelLoader::ModelLoad(const string& fileName, JH_Obj& Obj,ID3D11Device* pDevice)
{

	m_pDevice = pDevice;

	std::string FilePath="../../Data/Model/FBX/"+fileName+".FBX";

	m_pScene = aiImportFile(FilePath.c_str(), aiProcess_JoinIdenticalVertices |        // 동일한 꼭지점 결합, 인덱싱 최적화

		aiProcess_ValidateDataStructure |        // 로더의 출력을 검증

		aiProcess_ImproveCacheLocality |        // 출력 정점의 캐쉬위치를 개선

		aiProcess_RemoveRedundantMaterials |    // 중복된 매터리얼 제거

		aiProcess_GenUVCoords |                    // 구형, 원통형, 상자 및 평면 매핑을 적절한 UV로 변환

		aiProcess_TransformUVCoords |            // UV 변환 처리기 (스케일링, 변환...)

		aiProcess_FindInstances |                // 인스턴스된 매쉬를 검색하여 하나의 마스터에 대한 참조로 제거

		aiProcess_LimitBoneWeights |            // 정점당 뼈의 가중치를 최대 4개로 제한
		
		aiProcess_OptimizeMeshes |                // 가능한 경우 작은 매쉬를 조인

		aiProcess_GenSmoothNormals |            // 부드러운 노말벡터(법선벡터) 생성

		aiProcess_SplitLargeMeshes |            // 거대한 하나의 매쉬를 하위매쉬들로 분활(나눔)

		aiProcess_Triangulate |                    // 3개 이상의 모서리를 가진 다각형 면을 삼각형으로 만듬(나눔)

		aiProcess_ConvertToLeftHanded |            // D3D의 왼손좌표계로 변환

		aiProcess_SortByPType);                    // 단일타입의 프리미티브로 구성된 '깨끗한' 매쉬를 만듬


	{
		

	if (m_pScene)

		m_numMaterial = m_pScene->mNumMaterials;

		ReadMaterial();
		m_iBaseIndex = 0;
		m_iVertexIndex = 0;

		ReadBoneData(m_pScene->mRootNode, 0, 0);
		
		FilePath = "../../Data/Model/Binary/" + fileName + ".md";
		WriteModelBinary(FilePath);
	
		Obj.ReadFile(fileName);
	}
}
bool ModelLoader::ReadBoneData(aiNode* Node, int Index, int iParentIndex)
{

	cBone pBone;


	TCHAR WTextureName[1024];
	int length = strlen(Node->mName.C_Str());

	MultiByteToWideChar(CP_ACP, 0, Node->mName.C_Str(), length, &WTextureName[0], length + 1);
	lstrcpynW(WTextureName, WTextureName, length + 1);

	pBone.BoneName = WTextureName;
	pBone.iBoneIndex =Index;
	pBone.iBoneParentIndex = iParentIndex;

	
	D3DXMATRIX transform(Node->mTransformation[0]);

	D3DXMatrixTranspose(&pBone.m_Matworld, &transform);
	
	D3DXMATRIX MatParent;


	if (iParentIndex != 0)
		pBone.m_Matworld = pBone.m_Matworld*MatParent;
	else
		D3DXMatrixIdentity(&MatParent);

		m_Bones.push_back(std::move(pBone));

		if (Node->mNumMeshes >= 1)
		{
			ReadMeshData(Node, Index);
		}
		
		for (int i = 0; i <Node->mNumChildren; i++)
		{
			ReadBoneData(Node->mChildren[i],iParentIndex+1 , Index);
		}

		return true;
}
bool ModelLoader::ReadMeshData(aiNode* Node, int IBoneIndex)
{
	 cMesh aMesh;

	aMesh.IBoneIndex = IBoneIndex;

	TCHAR WTextureName[1024];
	int length = strlen(Node->mName.C_Str());

	MultiByteToWideChar(CP_ACP, 0, Node->mName.C_Str(), length, &WTextureName[0], length + 1);
	lstrcpynW(WTextureName, WTextureName, length+1);

	aMesh.Name = WTextureName;
	
	aiString tName;

	for (int iMesh = 0; iMesh < Node->mNumMeshes; ++iMesh)
	{
		UINT Index = Node->mMeshes[iMesh];
		
		aiMesh* SrcMesh = m_pScene->mMeshes[Index];
		
		aiMaterial* SrcMaterial = m_pScene->mMaterials[SrcMesh->mMaterialIndex];

		
		SrcMaterial->Get(AI_MATKEY_NAME, tName);

		int length = strlen(tName.C_Str());

		MultiByteToWideChar(CP_ACP, 0, tName.C_Str(), length, &WTextureName[0], length + 1);
		lstrcpynW(WTextureName, WTextureName, length + 1);
		aMesh.MaterialName = WTextureName;

		for (int iVertex= 0; iVertex<SrcMesh->mNumVertices ; ++iVertex)
		{
			PNCTIW_VERTEX Vertex;

			memcpy(&Vertex.p, &SrcMesh->mVertices[iVertex], sizeof(D3DXVECTOR3));

			if(SrcMesh->HasNormals())
			memcpy(&Vertex.n, &SrcMesh->mNormals[iVertex], sizeof(D3DXVECTOR3));

			if (SrcMesh->HasTextureCoords(0))
			{
				Vertex.t.x=SrcMesh->mTextureCoords[0]->x;
				Vertex.t.y = SrcMesh->mTextureCoords[0]->y;
			}


			aMesh.m_Vertices.emplace_back(Vertex);
		}


		for (int f = 0; f < SrcMesh->mNumFaces; ++f)
		{
			aiFace& aFace = SrcMesh->mFaces[f];
			for ( int id = 0;  id < aFace.mNumIndices; ++id)
			{
				aMesh.m_Indices.push_back(	aFace.mIndices[id]);
			}
		}
		
		m_meshes.emplace_back(aMesh);
	}


	return true;
}

void ModelLoader::InitScene()
{
	for (UINT i = 0; i < m_meshes.size(); ++i) {

		const aiMesh* pMesh = m_pScene->mMeshes[i];

		

		//m_numVertices += m_meshes[i].m_VertexData.size();

	}
}

bool ModelLoader::ReadMaterial()
{
	m_Materials.resize(m_pScene->mNumMaterials);

	for (int i = 0; i < m_pScene->mNumMaterials; i++)
	{
		aiMaterial* SrcMaterial = m_pScene->mMaterials[i];


		aiColor3D aiColor;
		aiString aiTexterureName;

		TCHAR WTextureName[1024];

		//메테리얼 이름 가져오기
		//Material
		SrcMaterial->Get(AI_MATKEY_NAME, aiTexterureName);

		int strsize = MultiByteToWideChar(CP_ACP, 0, aiTexterureName.C_Str(), -1, NULL, NULL);
		MultiByteToWideChar(CP_ACP, 0, aiTexterureName.C_Str(), strlen(aiTexterureName.C_Str()), &WTextureName[0], strsize);
		lstrcpynW(WTextureName, WTextureName, strsize);

		m_Materials[i].Name = WTextureName;
		
		SrcMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, aiColor);

		SrcMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &aiTexterureName);
		
		

		//CHAR ->WCHAR 변경
		//Diffuse
		strsize= MultiByteToWideChar(CP_ACP, 0, aiTexterureName.C_Str(), -1, NULL, NULL);
	
		int icheck= MultiByteToWideChar(CP_ACP, 0, aiTexterureName.C_Str(), strlen(aiTexterureName.C_Str()), &WTextureName[0], strsize);
		lstrcpynW(WTextureName, WTextureName, strsize);
		I_Texture.Add(m_pDevice, WTextureName, L"../../data/Texture/");

		m_Materials[i].Diffuse = I_Texture.SplitPath(WTextureName);
		m_Materials[i].DiffuseColor.x = aiColor.r;
		m_Materials[i].DiffuseColor.y = aiColor.g;
		m_Materials[i].DiffuseColor.z = aiColor.b;
		m_Materials[i].DiffuseColor.w = 1.0;



		//Ambient
		SrcMaterial->Get(AI_MATKEY_COLOR_AMBIENT, aiColor);

		SrcMaterial->GetTexture(aiTextureType_AMBIENT, 0, &aiTexterureName);
		

		strsize = MultiByteToWideChar(CP_ACP, 0, aiTexterureName.C_Str(), -1, NULL, NULL);
		MultiByteToWideChar(CP_ACP, 0, aiTexterureName.C_Str(), strlen(aiTexterureName.C_Str()), &WTextureName[0], strsize);
		lstrcpynW(WTextureName, WTextureName, strsize);
		I_Texture.Add(m_pDevice, WTextureName, L"../../data/Texture/");

		m_Materials[i].Normal = I_Texture.SplitPath(WTextureName);
		m_Materials[i].AmbientColor.x = aiColor.r;
		m_Materials[i].AmbientColor.y = aiColor.g;
		m_Materials[i].AmbientColor.z = aiColor.b;
		m_Materials[i].AmbientColor.w = 1.0;


		//Specular
		SrcMaterial->Get(AI_MATKEY_COLOR_SPECULAR, aiColor);
		SrcMaterial->GetTexture(aiTextureType_SPECULAR, 0, &aiTexterureName);
		
		strsize = MultiByteToWideChar(CP_ACP, 0, aiTexterureName.C_Str(), -1, NULL, NULL);
		MultiByteToWideChar(CP_ACP, 0, aiTexterureName.C_Str(), strlen(aiTexterureName.C_Str()), &WTextureName[0], strsize);
		lstrcpynW(WTextureName, WTextureName, strsize);
		I_Texture.Add(m_pDevice, WTextureName, L"../../data/Texture/");



		m_Materials[i].Specular = I_Texture.SplitPath(WTextureName);
		m_Materials[i].SpecularColor.x = aiColor.r;
		m_Materials[i].SpecularColor.y = aiColor.g;
		m_Materials[i].SpecularColor.z = aiColor.b;
		m_Materials[i].SpecularColor.w = 1.0;

		//EMiSSIVE
		SrcMaterial->Get(AI_MATKEY_COLOR_EMISSIVE, aiColor);
		SrcMaterial->GetTexture(aiTextureType_EMISSIVE, 0, &aiTexterureName);

		strsize = MultiByteToWideChar(CP_ACP, 0, aiTexterureName.C_Str(), -1, NULL, NULL);
		MultiByteToWideChar(CP_ACP, 0, aiTexterureName.C_Str(), strlen(aiTexterureName.C_Str()), &WTextureName[0], strsize);

		I_Texture.Add(m_pDevice, WTextureName, L"../../data/Texture/");
		m_Materials[i].Emissive = I_Texture.SplitPath(WTextureName);

		m_Materials[i].EmissiveColor.x = aiColor.r;
		m_Materials[i].EmissiveColor.y = aiColor.g;
		m_Materials[i].EmissiveColor.z = aiColor.b;
		m_Materials[i].EmissiveColor.w = 1.0;
	}

	return true;
}

bool ModelLoader::WriteModelBinary(const std::string FilePath)
{
	unique_ptr<BinaryWriter> Writer = make_unique<BinaryWriter>();

	Writer->Open(FilePath);

	if (m_Materials.size() > 0)
	{
		Writer->Int(m_Materials.size());
		for (int i = 0; i < m_Materials.size(); i++)
		{
			Writer->String(m_Materials[i].Name);
			Writer->Byte(m_Materials[i].DiffuseColor, sizeof(D3DXVECTOR4), 1);
			Writer->Byte(m_Materials[i].EmissiveColor, sizeof(D3DXVECTOR4), 1);
			Writer->Byte(m_Materials[i].SpecularColor, sizeof(D3DXVECTOR4), 1);
			Writer->Byte(m_Materials[i].AmbientColor, sizeof(D3DXVECTOR4), 1);
			
			Writer->String(m_Materials[i].Diffuse);
			Writer->String(m_Materials[i].Specular);
			Writer->String(m_Materials[i].Emissive);
			Writer->String(m_Materials[i].Normal);
		}
		
	}

	if (m_Bones.size())
	{
		Writer->Int(m_Bones.size());
		for (int i = 0; i < m_Bones.size(); i++)
		{
			cBone& tBone=m_Bones[i];
			Writer->String(tBone.BoneName);
			
			Writer->Int(tBone.iBoneIndex);
			Writer->Int(tBone.iBoneParentIndex);
			
			Writer->Byte(tBone.m_Matworld, sizeof(D3DXMATRIX), 1);
		}
	}

	if (m_meshes.size())
	{
		Writer->Int(m_meshes.size());
		for (int i = 0; i < m_meshes.size(); i++)
		{
			cMesh& tMesh = m_meshes[i];

			Writer->String(tMesh.Name);
			Writer->Int(tMesh.IBoneIndex);


			Writer->String(tMesh.MaterialName);
			Writer->Int(tMesh.m_Vertices.size());
			Writer->Byte(&tMesh.m_Vertices[0], sizeof(PNCTIW_VERTEX), tMesh.m_Vertices.size());
			Writer->Int(tMesh.m_Indices.size());
			Writer->Byte(&tMesh.m_Indices.at(0), sizeof(DWORD), tMesh.m_Indices.size());
		}
	}

	Writer->Close();
	return true;
}