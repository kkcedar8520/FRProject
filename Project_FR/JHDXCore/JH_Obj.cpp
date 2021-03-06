#pragma once
#include "JH_Obj.h"
#include"JH_ObjMgr.h"
#include"LightMgr.h"

bool JH_Obj::ReadFile(const std::string file)
{

	
	m_ObjData=I_ObjMgr.GetDataPtr(file);
	if (m_ObjData == nullptr)
	{
		int index = I_ObjMgr.LoadData(file);
		if (index == -1) { return false; }

		m_ObjData = I_ObjMgr.GetDataPtr(index);
		
		InitMaterial();
		BindingMesh();

	}

	m_Name = file;
	Init();
	return true;
}
void JH_Obj::InitMaterial()
{
	for (auto& mat : m_ObjData->m_materials)
	{
		mat.Init();
	}
}
bool JH_Obj::Init()
{
	D3DXMatrixIdentity(&m_matTransform);
	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matProj);
	D3DXMatrixIdentity(&m_matNormal);
	
	m_ColiderBox.CreateBox(m_ObjData->GetBone()[0].GetWorld());
	m_ColiderBox.Create(DX::GetDevice().Get(), DX::GetContext().Get(), L"../../data/shader/BoxShader.txt", nullptr, nullptr);


	
	m_CBTF.Attach(DX::MakeConstantBuffer(DX::GetDevice().Get(), &m_sCBTF, sizeof(CB_TF), 1));
	return true;
}
bool JH_Obj::Frame()
{ 

	for (auto& mesh : m_ObjData->GetMesh())
	{

		mesh.Frame();
	}
	m_ColiderBox.SetMatrix(&m_matTransform, &m_pCamera->m_matView, &m_pCamera->m_matProj);
	m_ColiderBox.Frame();

	UpdateBuffer(m_pLightConstBuffer.Get(), &I_LIGHT_MGR.m_cbLight);
	//UpdateTarnsformCB();
	return true;
}
bool JH_Obj::Render()
{
	UINT offset = 0;
	UINT Stride = 0;
	SetMatrix(nullptr, &m_pCamera->m_matView, &m_pCamera->m_matProj);
	for (auto& mesh : m_ObjData->GetMesh())
	{
	
		mesh.Render();
	}
	return true;
}
void JH_Obj::RenderCollider()
{
	m_ColiderBox.Render();
}
bool JH_Obj::Release()
{
	return true;
}

void JH_Obj::BindingMesh()
{
	for (auto& mesh : m_ObjData->GetMesh())
	{
		JH_Bone* pBone=BoneFindByIndex(mesh.GetBoneIndex());
		mesh.SetBone(pBone);
		mesh.Binding(this);
	}
}



JH_Material* JH_Obj::MaterialFindByName(std::wstring Name)
{
	for (auto& Mat:m_ObjData->GetMaterial() )
	{
		if (Mat.Name == Name)
		{
			return &Mat;
		}
	}
}
JH_Material* JH_Obj::MaterialFindByIndex(int  id)
{
	return &m_ObjData->GetMaterial()[id];
}

JH_Bone* JH_Obj::BoneFindByName(std::wstring Name)
{
	for (auto& Bone : m_ObjData->GetBone())
	{
		if (Bone.GetBoneName() == Name)
		{
			return &Bone;
		}
	}
}
JH_Bone* JH_Obj::BoneFindByIndex(int id)
{
	for (auto& Bone : m_ObjData->GetBone())
	{
		if (Bone.GetBoneIndex() == id)
		{
			return &Bone;
		}
	}
}


void JH_Obj::SetMatrix(D3DXMATRIX*  world, D3DXMATRIX*  View, D3DXMATRIX*  Proj)
{
	if (world != nullptr)
	{
		m_matWorld =* world;
	}

	if (View != nullptr)
	{
		m_matView = *View;
	}

	if (Proj != nullptr)
	{
		m_matProj = *Proj;
	}


	////D3DXMatrixTranspose(&m_sCBTF.matWorld,&m_matTransform);
	////D3DXMatrixTranspose(&m_sCBTF.matView, &m_matView);
	////D3DXMatrixTranspose(&m_sCBTF.matProj, &m_matProj);
	
	
	//메쉬들의 트랜스폼 세팅
	for(auto& mesh: m_ObjData->GetMesh())
	{
		D3DXMATRIX matFinal = DX::DecomposeMtrixMultiply(m_matWorld, m_matTransform);
		mesh.SetMatrix(&matFinal, &m_matView, &m_matProj);
		
	}
}

void JH_Obj::SetTransform(D3DXMATRIX& Mat)
{
	m_matTransform = Mat;
	m_ColiderBox.m_matWorld = m_matTransform;
	
	m_ColiderBox.m_matFinal=DX::DecomposeMtrixMultiply(m_matTransform, m_ColiderBox.m_matTransform);
	m_ColiderBox.CreateBox(m_ColiderBox.m_matFinal);
}
void JH_Obj::SetPos(D3DXVECTOR3 vPos)
{
	m_matTransform._41 = vPos.x;
	m_matTransform._42 = vPos.y;
	m_matTransform._43 = vPos.z;

	m_ColiderBox.m_matWorld = m_matTransform;

	m_ColiderBox.m_matFinal = DX::DecomposeMtrixMultiply(m_matTransform, m_ColiderBox.m_matTransform);
	m_ColiderBox.CreateBox(m_ColiderBox.m_matFinal);
	
}
void JH_Obj::SetScale(D3DXVECTOR3 vScale)
{
	D3DXVECTOR3 vS, vP;
	D3DXQUATERNION qR;
	D3DXMATRIX mR, mS;
	D3DXMatrixDecompose(&vS, &qR, &vP, &m_matTransform);
	vS = vScale;

	D3DXMatrixRotationQuaternion(&mR, &qR);
	D3DXMatrixScaling(&mS, vS.x, vS.y, vS.z);
	m_matTransform = mS * mR;
	m_matTransform._41 = vP.x;
	m_matTransform._42 = vP.y;
	m_matTransform._43 = vP.z;

	m_ColiderBox.m_matWorld = m_matTransform;

	m_ColiderBox.m_matFinal = DX::DecomposeMtrixMultiply(m_ColiderBox.m_matWorld, m_ColiderBox.m_matTransform);
	m_ColiderBox.CreateBox(m_ColiderBox.m_matFinal);
}
void JH_Obj::SetRotation(D3DXMATRIX Mat)
{
	D3DXVECTOR3 vS, vP;
	D3DXQUATERNION qR;
	D3DXMATRIX mR, mS;
	D3DXMatrixDecompose(&vS, &qR, &vP, &m_matTransform);


	D3DXMatrixRotationQuaternion(&mR, &qR);
	mR = Mat;

	D3DXMatrixScaling(&mS, vS.x, vS.y, vS.z);
	m_matTransform = mS * mR;
	m_matTransform._41 = vP.x;
	m_matTransform._42 = vP.y;
	m_matTransform._43 = vP.z;

	m_ColiderBox.m_matWorld = m_matTransform;

	m_ColiderBox.m_matFinal = DX::DecomposeMtrixMultiply(m_ColiderBox.m_matWorld, m_ColiderBox.m_matTransform);

	m_ColiderBox.CreateBox(m_ColiderBox.m_matFinal);
}
void JH_Obj::CreateColiderBox(D3DXMATRIX& mat)
{
	m_ColiderBox.CreateBox(mat);
}

void JH_Obj::UpdateTarnsformCB()
{
	DX::GetContext()->UpdateSubresource(m_CBTF.Get(), 0, nullptr, &m_sCBTF, 0, 0);
}
void JH_Obj::CreateTransformCB()
{

}
JH_Obj::JH_Obj()
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matTransform);
	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matProj);
}
JH_Obj::~JH_Obj()
{
	
}