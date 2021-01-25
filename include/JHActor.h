#pragma once
#include"JHObject.h"
#include"JH_Input.h"
class JHActor:public JHObject
{
protected:
	JH_Input m_Input;
public:
	RECT	m_rtDest;
public:
	/*void DrawRotateBlt() override;*/
	bool SetSRC(RECT rt);
	void SetPosition(float x, float y);
public:
	JHActor();
	virtual ~JHActor();
};

