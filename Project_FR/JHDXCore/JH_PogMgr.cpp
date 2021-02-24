#include "JH_PogMgr.h"


	JH_PogMgr::JH_PogMgr()
	{
	}
	JH_PogMgr::~JH_PogMgr()
	{
	}

	void JH_PogMgr::Create(ID3D11Device* pd3device, ID3D11DeviceContext* pContext, D3DXVECTOR4 ClipPlane, D3DXVECTOR4 FogColor, D3DXVECTOR4 FogInfo)
	{
		m_pPogCB.Attach(DX::MakeConstantBuffer(pd3device, &m_cbPog, 1, sizeof(PogCB)));

		m_cbPog.g_ClipPlane = ClipPlane;
		m_cbPog.g_FogColor = FogColor;
		m_cbPog.g_FogInfo = FogInfo;
	}
	Microsoft::WRL::ComPtr<ID3D11Buffer> JH_PogMgr::GetBuffer()
	{
		return m_pPogCB.Get();
	}
