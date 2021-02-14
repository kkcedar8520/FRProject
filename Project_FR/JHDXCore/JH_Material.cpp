#include "JH_Material.h"
#include "JH_Obj.h"

bool JH_Material::Init()
{
	
	m_CBMT.AmbientColor = AmbientColor;
	m_CBMT.DiffuseColor = DiffuseColor;
	m_CBMT.EmissiveColor = EmissiveColor;
	m_CBMT.SpecularColor = SpecularColor;

	m_CB = DX::MakeConstantBuffer(DX::GetDevice().Get(), &m_CBMT, sizeof(CB_MT), 1);
	



	


	return true;
}

bool JH_Material::Render()
{
	TCHAR* Temp=nullptr;

	DX::GetContext()->VSSetConstantBuffers(2, 1, m_CB.GetAddressOf());
	DX::GetContext()->PSSetConstantBuffers(2, 1, m_CB.GetAddressOf());

	

	DX::GetContext()->VSSetShaderResources(0, 1, &I_Texture.GetPtr(Diffuse.c_str())->m_pTextureRV);
	DX::GetContext()->PSSetShaderResources(0, 1, &I_Texture.GetPtr(Diffuse.c_str())->m_pTextureRV);


	return true;
}