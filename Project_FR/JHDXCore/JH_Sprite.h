#pragma once
#include"JH_ShapePlane.h"

struct JRECT
{
	D3DXVECTOR2 uv[4];
};

typedef vector<RECT> rtList;
typedef vector<JRECT> JrtLits;
class JH_Sprite:public JH_ShapePlane
{
public:
	float m_fChangeTime;
	float m_fOffsetTime;
	float m_fSecondPerRender;
	int	  m_iNumSpriteIndex;
	int	  m_iIndex;
	float m_fTimer;
	vector<rtList> m_VectorList;

public:
	vector<shared_ptr< ID3D11ShaderResourceView>> m_SRVList;
	JrtLits	m_uvList;
public:
	/*void SetOneTextureAnimation(float ChangeTime, float OffsetTime, int ColSprite = 0, int RowSprite = 0);
	void SetTexturesAnimation(float ChangeTime, float OffsetTime, int ColSprite = 0, int RowSprite = 0);*/
	void SetArrayRect(vector<RECT>& rtList,int width, int height,float fAnimaTime);
public:
	virtual bool Frame();
	virtual bool PostRender();
public:
	JH_Sprite();
	virtual ~JH_Sprite();
};

