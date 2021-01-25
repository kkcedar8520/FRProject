#pragma once
#include"JHActor.h"
class JHNpcObj :public JHActor
{
public:
	bool Init();
	bool Frame();
	bool Render();
	JHNpcObj(){}
	virtual ~JHNpcObj(){}

};

