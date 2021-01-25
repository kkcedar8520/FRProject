#include "ModelView.h"

void ModelView::Update(D3DXVECTOR4 value)
{
	D3DXQUATERNION qRot;
	D3DXMATRIX matRot;
	D3DXQuaternionRotationYawPitchRoll(&qRot, value.y, value.x, value.z);
	D3DXMatrixAffineTransformation(&matRot, 1.0f, NULL, &qRot, &m_vPos);
	D3DXMatrixInverse(&m_matView, NULL, &matRot);
}
bool ModelView::Frame()
{
	m_fRadius += m_nMouseWhellDelta * m_fRadius * 0.1f / 120.0f;
	m_fRadius = min(m_fMaxRadius, m_fRadius);
	m_fRadius = max(m_fMinRadius, m_fRadius);
	m_nMouseWhellDelta = 0;

	// Camera transform
	D3DXMATRIX matCameraRot;
	D3DXMatrixInverse(&matCameraRot, NULL,
		m_ViewArcBall.GetRotationMatrix());
	D3DXVECTOR3 vWorldUp, vWorldAhead;
	D3DXVECTOR3 vLocalUp = D3DXVECTOR3(0, 1, 0);
	D3DXVECTOR3 vLocalAhead = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformCoord(&vWorldUp, &vLocalUp, &matCameraRot);
	D3DXVec3TransformCoord(&vWorldAhead, &vLocalAhead, &matCameraRot);
	m_vPos = m_vAt - vWorldAhead * m_fRadius;
	D3DXMatrixLookAtLH(&m_matView,
		&m_vPos,
		&m_vAt,
		&vWorldUp);

	// world(object) transform
	D3DXMATRIX mInvView;
	D3DXMatrixInverse(&mInvView, NULL, &m_matView);
	mInvView._41 = 0.0f;
	mInvView._42 = 0.0f;
	mInvView._43 = 0.0f;

	D3DXMATRIX mModelLastRotInv;
	D3DXMatrixInverse(&mModelLastRotInv, NULL, &m_mModelLastRot);

	D3DXMATRIX mModelRot;
	mModelRot = *m_WorldArcBall.GetRotationMatrix();

	m_mModelRot = m_mModelRot * m_matView * mModelLastRotInv *
		mModelRot * mInvView;


	m_mModelLastRot = mModelRot;

	m_mModelRot._41 = m_vAt.x;
	m_mModelRot._42 = m_vAt.y;
	m_mModelRot._43 = m_vAt.z;

	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans, -m_vModelCenter.x,
		-m_vModelCenter.y, -m_vModelCenter.z);
	m_matWorld = matTrans * m_mModelRot;

	UpdateBasisVector();
	return true;
}

ModelView::ModelView()
{
	D3DXMatrixIdentity(&m_mModelLastRot);
	D3DXMatrixIdentity(&m_mModelRot);
	m_vModelCenter.x = 0;
	m_vModelCenter.y = 0;
	m_vModelCenter.z = 0;
}


ModelView::~ModelView()
{
}
