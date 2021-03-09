#include "ModelLoader.h"

ModelLoader::ModelLoader()
{
	//importer = new Assimp::Importer();
}
ModelLoader::~ModelLoader()
{
	//delete importer;
}
void ModelLoader::ModelLoad(const string& fileName, ID3D11Device* pDevice)
{

	m_pDevice = pDevice;

	std::string FilePath="../../Data/Model/FBX/"+fileName+".FBX";

	m_pScene = aiImportFile(FilePath.c_str(), aiProcess_JoinIdenticalVertices |        // ������ ������ ����, �ε��� ����ȭ

		aiProcess_ValidateDataStructure |        // �δ��� ����� ����

		aiProcess_ImproveCacheLocality |        // ��� ������ ĳ����ġ�� ����

		aiProcess_RemoveRedundantMaterials |    // �ߺ��� ���͸��� ����

		aiProcess_GenUVCoords |                    // ����, ������, ���� �� ��� ������ ������ UV�� ��ȯ

		aiProcess_TransformUVCoords |            // UV ��ȯ ó���� (�����ϸ�, ��ȯ...)

		aiProcess_FindInstances |                // �ν��Ͻ��� �Ž��� �˻��Ͽ� �ϳ��� �����Ϳ� ���� ������ ����

		aiProcess_LimitBoneWeights |            // ������ ���� ����ġ�� �ִ� 4���� ����
		
		aiProcess_OptimizeMeshes |                // ������ ��� ���� �Ž��� ����

		aiProcess_GenSmoothNormals |            // �ε巯�� �븻����(��������) ����

		aiProcess_SplitLargeMeshes |            // �Ŵ��� �ϳ��� �Ž��� �����Ž���� ��Ȱ(����)

		aiProcess_Triangulate |                    // 3�� �̻��� �𼭸��� ���� �ٰ��� ���� �ﰢ������ ����(����)

		aiProcess_ConvertToLeftHanded |            // D3D�� �޼���ǥ��� ��ȯ

		aiProcess_SortByPType);                    // ����Ÿ���� ������Ƽ��� ������ '������' �Ž��� ����


	{
		

	if (m_pScene)

		m_numMaterial = m_pScene->mNumMaterials;

		ReadMaterial();
		ReadBoneData(m_pScene->mRootNode, 0, 0);
		
		FilePath = "../../Data/Model/Binary/" + fileName + ".md";
		WriteModelBinary(FilePath);
	
		
	}
}
bool ModelLoader::ReadBoneData(aiNode* Node, int Index, int iParentIndex)
{
	
	asBone pBone;


	TCHAR WTextureName[1024];
	int length = strlen(Node->mName.C_Str());

	MultiByteToWideChar(CP_ACP, 0, Node->mName.C_Str(), length, &WTextureName[0], length + 1);
	lstrcpynW(WTextureName, WTextureName, length + 1);

	pBone.BoneName = WTextureName;
	pBone.iBoneIndex = Index;
	pBone.iBoneParentIndex = iParentIndex;
	
	
	D3DXMATRIX transform(Node->mTransformation[0]);

	//��ǥ�躯ȯ ���켱�� ��켱���� 
	D3DXMatrixTranspose(&pBone.m_Matworld, &transform);

	D3DXMATRIX MatParent;
	

	//��ǥ������������ �θ� ��ǥ�踦 ����
	
	if (iParentIndex != 0)
		MatParent = m_Bones[iParentIndex].m_Matworld;
	else
		D3DXMatrixIdentity(&MatParent);

		pBone.m_Matworld = pBone.m_Matworld*MatParent;	
		m_Bones.push_back(std::move(pBone));

		if (Node->mNumMeshes >= 1)
		{
			ReadMeshData(Node, Index);
		}
		
		//���ȣ�� ��忡�ش��ϴ� �޽� ���� ���:�� =1:1
		for (int i = 0; i <Node->mNumChildren; i++)
		{
			ReadBoneData(Node->mChildren[i], m_Bones.size(), Index);
		}

		return true;
}
bool ModelLoader::ReadMeshData(aiNode* Node, int IBoneIndex)
{
	if(Node->mNumMeshes<1){return false;}
	 asMesh aMesh;

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

		UINT StartVertex = aMesh.m_Vertices.size();
		for (int iVertex= 0; iVertex<SrcMesh->mNumVertices ; ++iVertex)
		{
			PNCTIW_VERTEX Vertex;

			memcpy(&Vertex.p, &SrcMesh->mVertices[iVertex], sizeof(D3DXVECTOR3));

			if(SrcMesh->HasNormals())
			memcpy(&Vertex.n, &SrcMesh->mNormals[iVertex], sizeof(D3DXVECTOR3));

			if (SrcMesh->HasTextureCoords(0))
			{
				
				Vertex.t.x= SrcMesh->mTextureCoords[0][iVertex].x;
				Vertex.t.y= SrcMesh->mTextureCoords[0][iVertex].y;
			}


			aMesh.m_Vertices.emplace_back(Vertex);
		}


		for (int f = 0; f < SrcMesh->mNumFaces; ++f)
		{
			aiFace& aFace = SrcMesh->mFaces[f];
			for ( int id = 0;  id < aFace.mNumIndices; ++id)
			{
				aMesh.m_Indices.emplace_back(	aFace.mIndices[id]);
				aMesh.m_Indices.back() += StartVertex;
			}
		}
		
		m_meshes.emplace_back(aMesh);
	}


	return true;
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

		//���׸��� �̸� ��������
		//Material
		SrcMaterial->Get(AI_MATKEY_NAME, aiTexterureName);

		int strsize = MultiByteToWideChar(CP_ACP, 0, aiTexterureName.C_Str(), -1, NULL, NULL);
		MultiByteToWideChar(CP_ACP, 0, aiTexterureName.C_Str(), strlen(aiTexterureName.C_Str()), &WTextureName[0], strsize);
		lstrcpynW(WTextureName, WTextureName, strsize);

		m_Materials[i].Name = WTextureName;
		
		SrcMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, aiColor);

		SrcMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &aiTexterureName);
		
		

		//CHAR ->WCHAR ����
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

void ModelLoader::ExportAnimClip(const std::string& fileName)
{
	std::string Path="../data/Model/Animation/"+fileName+".clip";

	ReadClipData(0);

}
void ModelLoader::ReadClipData(int AnimIndex)
{
	aiAnimation* aiAnim = m_pScene->mAnimations[AnimIndex];
	m_asClip = make_unique<asClip>();

	m_asClip->Name = aiAnim->mName.C_Str();

	m_asClip->FrameRate = aiAnim->mTicksPerSecond;
	//Float �����̽� ������ +1
	m_asClip->FrameCount = aiAnim->mDuration+1;
	//���� Ű�������� �������°� ������ �ִϸ��̼� Ű������ ������� ��� ���� �����������ʴ�
	for ( int ibone = 0; ibone < aiAnim->mNumChannels; ibone++)
	{
		asClipNode ClipNode;
		aiNodeAnim *Node = aiAnim->mChannels[ibone];

		ClipNode.Name=Node->mNodeName.C_Str();
		
		UINT Key = max(Node->mNumPositionKeys, max(Node->mNumScalingKeys, Node->mNumRotationKeys));

		asFrameData FrameData;
		for (int k = 0; k < Key; k++)
		{
			
			bool bVaild = false;

			float t=ClipNode.KeyFrame.size();
			//������������ ������ ���� ������
			if (fabsf(Node->mPositionKeys[k].mTime - t) <= D3DX_16F_EPSILON)
			{
				FrameData.Frame=Node->mPositionKeys[k].mTime;
				memcpy(&FrameData.vPosition, &Node->mPositionKeys[k].mValue, sizeof(D3DXVECTOR3));
				
				bVaild = true;
			}

			if (fabsf(Node->mRotationKeys[k].mTime - t) <= D3DX_16F_EPSILON)
			{
				FrameData.Frame = Node->mRotationKeys[k].mTime;
				memcpy(&FrameData.qRotation, &Node->mRotationKeys[k].mValue, sizeof(D3DXQUATERNION));

				bVaild = true;
			}

			if (fabsf(Node->mScalingKeys[k].mTime - t) <= D3DX_16F_EPSILON)
			{
				FrameData.Frame = Node->mScalingKeys[k].mTime;
				memcpy(&FrameData.vScale, &Node->mScalingKeys[k].mValue, sizeof(D3DXVECTOR3));

				bVaild = true;
			}

			if (bVaild)
				ClipNode.KeyFrame.emplace_back(FrameData);
		}

		//�ִϸ��̼��̾��� ��κ��� �������κ����� �󰳼���ŭ ä������
		if (ClipNode.KeyFrame.size()<m_asClip->FrameCount)
		{
			UINT KeyOffset = m_asClip->FrameCount - ClipNode.KeyFrame.size();
			
			FrameData = ClipNode.KeyFrame.back();
			for (int i = 0; i < KeyOffset; i++)
			{
				ClipNode.KeyFrame.emplace_back(FrameData);
			}
		}
		m_asClip->Duration = max(m_asClip->Duration, ClipNode.KeyFrame.back().Frame);

		m_vClipNode.emplace_back(ClipNode);
	}
	ReadKeyFrameData(m_pScene->mRootNode);
}
void ModelLoader::ReadKeyFrameData(aiNode* Node)
{
	asKeyFrame KeyFrame;
	KeyFrame.BoneName = Node->mName.C_Str();

	asFrameData FrameData;
	for (int k = 0; k < m_asClip->FrameCount;++k)
	{
		asClipNode* ClipNode = nullptr;
		for (int i = 0; i <m_vClipNode.size(); i++)
		{
			
			if (m_vClipNode[i].Name == Node->mName.C_Str())
			{
				ClipNode = &m_vClipNode[i];
				break;
			}
		}
		if (ClipNode == nullptr)
		{
			D3DXMATRIX matTransform= Node->mTransformation[0];
			D3DXMatrixTranspose(&matTransform,&matTransform);
			D3DXMatrixDecompose(&FrameData.vScale, &FrameData.qRotation, &FrameData.vPosition, &matTransform);
		}
		else
		{
			FrameData = ClipNode->KeyFrame[k];
		}
		KeyFrame.Transform.emplace_back(FrameData);
	}
	m_asClip->vKeyFrame.emplace_back(KeyFrame);

	for  (int iChild = 0; iChild < Node->mNumChildren;++iChild)
	{
		ReadKeyFrameData(Node->mChildren[iChild]);
	}
}
void ModelLoader::WriteAniClip(const string& fileName)
{
	unique_ptr<BinaryWriter> Writer = make_unique<BinaryWriter>();

	Writer->Open(fileName);

	if (m_asClip->vKeyFrame.size() > 0)
	{
		Writer->String(m_asClip->Name);
		Writer->Float(m_asClip->FrameCount);

		Writer->Float(m_asClip->FrameRate);
		Writer->Float(m_asClip->Duration);
		
		for (int  k = 0; k < m_asClip->vKeyFrame.size(); k++)
		{
			Writer->String(m_asClip->vKeyFrame[k].BoneName);
			asKeyFrame &KeyFrame=m_asClip->vKeyFrame[k];
			for (int t = 0; KeyFrame.Transform.size();++t)
			{
				Writer->Float(KeyFrame.Transform[t].Frame);
				Writer->Byte(KeyFrame.Transform[t].vPosition, sizeof(D3DXVECTOR3),1);
				Writer->Byte(KeyFrame.Transform[t].qRotation, sizeof(D3DXQUATERNION), 1);
				Writer->Byte(KeyFrame.Transform[t].vScale, sizeof(D3DXVECTOR3), 1);
			}
		}
	}
	Writer->Close();
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
			asBone& tBone=m_Bones[i];
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
			asMesh& tMesh = m_meshes[i];

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

