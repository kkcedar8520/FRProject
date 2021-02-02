#pragma once
#include"JH_DXStd.h"
class Buffer
{
	std::shared_ptr<ID3D11Buffer> m_Buffer;
public:
	std::shared_ptr<ID3D11Buffer> GetBuffer() { return m_Buffer; }
};

