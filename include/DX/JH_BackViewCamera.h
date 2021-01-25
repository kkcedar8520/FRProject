#pragma once
#include"JHCamera.h"
class JH_BackViewCamera:public JHCamera
{
public:
	void Front(float Speed);
	void Side(float Speed);
public:
	bool Frame()override;
public:
	JH_BackViewCamera();
	~JH_BackViewCamera();
};

