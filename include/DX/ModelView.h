#pragma once

#include "JHCamera.h"
class ModelView : public JHCamera
{
public:
	D3DXMATRIX	m_mModelRot;
	D3DXMATRIX  m_mModelLastRot;
	D3DXVECTOR3 m_vModelCenter;
public:
	bool Frame() override;
	void Update(D3DXVECTOR4 value);
public:
	ModelView();
	virtual ~ModelView();
};

