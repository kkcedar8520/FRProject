#include "JH_Mesh.h"

JH_Mesh::JH_Mesh()
{


	m_iTexIndex = 0;
	m_iBaseVertex = 0;
	m_iNumVertex = 0;
	m_iParentIndex = -1;


	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matInverseWorld);
	D3DXMatrixIdentity(&m_matCalculation);


}

JH_Mesh::~JH_Mesh()
{

}