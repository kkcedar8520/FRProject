#include "JH_Sprite.h"



void JH_Sprite::SetArrayRect(vector<RECT>& rtList,int width,int height,float fAnimaTime)
{
	
	m_iNumSpriteIndex = rtList.size();


	for(int rtN=0 ;rtN< m_iNumSpriteIndex;rtN++)
	{
		JRECT rt;

		rt.uv[0].x = rtList[rtN].left/(float)width;
		rt.uv[0].y = rtList[rtN].top/(float)height;
		rt.uv[1].x = (rtList[rtN].left+rtList[rtN].right)/(float)width;
		rt.uv[1].y=  rtList[rtN].top / (float)height;
		rt.uv[2].x = rtList[rtN].left / (float)width;
		rt.uv[2].y = (rtList[rtN].top+rtList[rtN].bottom)/(float)height;
		rt.uv[3].x = (float)rt.uv[1].x;
		rt.uv[3].y = (float)rt.uv[2].y;

		m_uvList.push_back(rt);
	}
	m_fSecondPerRender = fAnimaTime / m_iNumSpriteIndex;
}
bool JH_Sprite::Frame()
{
	if (m_fChangeTime<=0.0f)
	{
	}
	m_fOffsetTime += g_SecondPerFrame;
	if (m_fOffsetTime>=m_fSecondPerRender)
	{
		m_iIndex++;
		m_fOffsetTime -= m_fSecondPerRender;
		if (m_iIndex>=m_iNumSpriteIndex)
		{
			m_iIndex = 0;
		}
	}
	return true;
}
bool JH_Sprite::PostRender()
{
	if (m_SRVList.size()>0)
	{
		
	}
	else
	{
		m_VertexData[0].t = m_uvList[m_iIndex].uv[0];
		m_VertexData[1].t = m_uvList[m_iIndex].uv[1];
		m_VertexData[2].t = m_uvList[m_iIndex].uv[2];
		m_VertexData[3].t = m_uvList[m_iIndex].uv[3];

		m_dxHelper.GetDeviceContext()->UpdateSubresource(m_dxHelper.GetVertexBuffer(), 0, nullptr, &m_VertexData.at(0), 0, 0);
	}
	m_dxHelper.PostRender();
	return true;
}


JH_Sprite::JH_Sprite()
{
	m_iNumSpriteIndex = 0;
	m_fChangeTime = 0;
	m_fOffsetTime = 0;
	m_fSecondPerRender = 0;
	m_iNumSpriteIndex = 0;
	m_iIndex = 0;
	m_fTimer = 0.0f;
}


JH_Sprite::~JH_Sprite()
{
}
