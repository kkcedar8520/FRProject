#pragma once
#include"JHActor.h"
#include"JH_Input.h"
#include"HCore.h"
class JHPlayerObj :public JHActor
{

public:
	bool Frame();
	bool Render();

	JHPlayerObj()
	{
		m_fPosX = 400;
		m_fPosY = 600;
	}
	virtual ~JHPlayerObj(){}
};

