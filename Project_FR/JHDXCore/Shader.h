#pragma once
#include"JH_DXStd.h"
class Shader
{
	unique_ptr<ID3D11PixelShader>	m_pPS;
	unique_ptr<ID3D11VertexShader>	m_pVS;
public:
	void SetVertexShader(const std::string ShaderFile,const std::string functionName);
	void SetPixelShader(const std::string ShaderFile, const std::string functionName);
};

