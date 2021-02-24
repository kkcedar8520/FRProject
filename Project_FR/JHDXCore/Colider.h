#pragma once
#include"JH_DXStd.h"
class Colider:public Singleton<Colider>
{
	friend class Singleton<Colider>;
public:
	BOOL AABBtoAABB(JH_Box& A, JH_Box&B);
	BOOL OBBtoOBB(JH_Box& A, JH_Box&B);
	BOOL OBBtoSphere(JH_Box& A, JH_Box&B);
	BOOL OBBtoRay(JH_Box& A, JH_RAY& B);
};


#define I_Colider Colider::GetInstance()