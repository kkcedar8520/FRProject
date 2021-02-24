#include "JH_Node.h"



	JH_Node::JH_Node()
	{
	}


	JH_Node::~JH_Node()
	{
		for (int iNode = 0; iNode < 4; iNode++)
		{
				SAFE_DEL(m_pChild[iNode]);
		}
	}
