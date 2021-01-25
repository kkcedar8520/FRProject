#pragma once
#include"LightObj.h"

struct LightConstantBuffer
{
	D3DXVECTOR4 vAmbinentLightColor[g_iLightNum];
	D3DXVECTOR4 vDiffuseLightColor[g_iLightNum];
	D3DXVECTOR4 vSpecularLightColor[g_iLightNum];
	D3DXVECTOR4 vSpotLightColor[g_iLightNum];
	D3DXVECTOR4 vLightDirection[g_iLightNum];//W :∞®ºË
	D3DXVECTOR4 vLightPos[g_iLightNum];//W:≈∏¿‘
	D3DXVECTOR4 vSpotLight[g_iLightNum];// ≥ª∫Œ,ø‹∫Œ,»÷µµ theta, phi, Fallofff
	D3DXVECTOR4 vEyeDir;
	D3DXVECTOR4 vEyePos;
};

class LightMgr
{
public:

	vector<LightObj> m_LightObjList;
	vector<LightInfo> m_LightInfoList;

	Microsoft::WRL::ComPtr<ID3D11Buffer> m_pLightConstantBuffer[CONSTANT_BUFFER_SIZE];
	LightConstantBuffer m_cbLight;
	int m_iLightNum;
	ID3D11Device*			m_pDevice;
	ID3D11DeviceContext*	m_pContext;

public:
	static LightMgr& Get()
	{
		static LightMgr mgr;
		return mgr;
	}
public:
	int LightDataLoad(const TCHAR* pszLoad);
	void GetDevice(ID3D11Device* pdevcie);
	void GetContext(ID3D11DeviceContext* pContext);
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();

	virtual ~LightMgr();
private:
	LightMgr();
};


#define I_LIGHT_MGR LightMgr::Get()