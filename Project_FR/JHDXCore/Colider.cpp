#include "Colider.h"

BOOL Colider::AABBtoAABB(JH_Box& A, JH_Box& B)
{
	return true;
}
BOOL Colider::OBBtoOBB(JH_Box& A, JH_Box&B)
{
	D3DXVECTOR3 SA;
	float r1, r2, r0;
	
	vector<D3DXVECTOR3> Axisarray;
	Axisarray.resize(6);
	
	memcpy(Axisarray.at(0), A.vAxis[0], sizeof(D3DXVECTOR3) * 3);
	memcpy(Axisarray.at(3), B.vAxis[0], sizeof(D3DXVECTOR3) * 3);
	//사영계산의 최적화 사영공간을 평행한축의 경우수로 계산한다
	for (int  iAxis = 0; iAxis < 6; iAxis++)
	{
		SA = Axisarray[iAxis];

		D3DXVECTOR3 vDistX,vDistY,vDistZ;
		vDistX = A.fExtent[0] * A.vAxis[0];
		vDistY = A.fExtent[1] * A.vAxis[1];
		vDistZ = A.fExtent[2] * A.vAxis[2];
		
		r1 = fabs(D3DXVec3Dot(&vDistX, &SA))+ fabs(D3DXVec3Dot(&vDistY, &SA))+ fabs(D3DXVec3Dot(&vDistZ, &SA));
		
		vDistX = B.fExtent[0] * B.vAxis[0];
		vDistY = B.fExtent[1] * B.vAxis[1];
		vDistZ = B.fExtent[2] * B.vAxis[2];

		r2 = fabs(D3DXVec3Dot(&vDistX, &SA)) + fabs(D3DXVec3Dot(&vDistY, &SA)) + fabs(D3DXVec3Dot(&vDistZ, &SA));
	
		r0 = D3DXVec3Length(&(A.vCenter - B.vCenter));
		if (r0 <= (r1 + r2))
		{
			return true;
		}

	}



	return false;

	
}
BOOL Colider::OBBtoSphere(JH_Box& A, JH_Box&B)
{
	return true;
}
BOOL Colider::OBBtoRay(JH_Box& A, JH_RAY& B)
{
	return true;
}