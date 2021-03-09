//#include "MaxObj.h"
//HRESULT MaxObj::CreateVertexData()
//{
//	HRESULT hr = S_OK;
//	m_iVertexSize = sizeof(PNCT_VERTEX);
//	m_VertexData.resize(m_FaceBuffer.size()*3);
//
//	for (int iFace = 0; iFace < m_FaceBuffer.size(); iFace++)
//	{
//		for (int iVertex = 0; iVertex < 3; iVertex++)
//		{
//			//			m_VertexData[iFace * 3 + iVertex] = m_FaceBuffer[iFace].v[iVertex];
//		}
//	}
//	return hr;
//
//}
//HRESULT MaxObj::CreateIndexData()
//{
//	HRESULT hr = S_OK;
//	return hr;
//}
//int MaxObj::GetParentIndex(const TCHAR*	strName)
//{
//	for (int iObj = 0; iObj < m_ExpObject.size(); iObj++)
//	{
//		T_STR szName = m_ExpObject[iObj].m_szName;
//		if (strName == szName)
//		{
//			return iObj;
//		}
//	}
//	return -1;
//}
//bool	MaxObj::Load(ID3D11Device* pdvice, ID3D11DeviceContext* pContext, const TCHAR* LoadFile)
//{
//	m_pd3dDevice = pdvice;
//	m_pContext = pContext;
//	Parsing(LoadFile);
//	Convert();
//	Create(pdvice, pContext, L"../../data/shader/ColorBlend.txt", L"../../data/Resource/Galloper.bmp");
//	return true;
//}
//void	MaxObj::Convert()
//{
//	int iBaseOffset = 0;
//
//
//
//	for (int iObj = 0; iObj < m_ExpObject.size(); iObj++)
//	{
//		HMesh& JH_Mesh=m_ExpObject[iObj];
//		//JH_Mesh.m_AnimTrackPos.assign(m_ExpObject[iObj].m_AnimTrackPos.begin(),
//		//	m_ExpObject[iObj].m_AnimTrackPos.end());
//
//		//JH_Mesh.m_AnimTrackRotate.assign(m_ExpObject[iObj].m_AnimTrackRotate.begin(),
//		//	m_ExpObject[iObj]->m_AnimTrackRotate.end());
//		//JH_Mesh.m_AnimTrackScale.assign(m_ExpObject[iObj]->m_AnimTrackScale.begin(),
//		//	m_ExpObject[iObj]->m_AnimTrackScale.end());
//
//	
//		JH_Mesh.m_matWorld = m_ExpObject[iObj].m_matWorld;
//		//JH_Mesh.m_szName = m_ExpObject[iObj].m_szName;
//		//JH_Mesh.m_szParentName = m_ExpObject[iObj].m_szParentName;
//
//
//		D3DXMATRIX matParentInverse, matDefaultAnim;
//		D3DXMatrixIdentity(&matParentInverse);
//		JH_Mesh.m_iParentIndex = GetParentIndex(m_ExpObject[iObj].m_szParentName);
//
//		if (JH_Mesh.m_iParentIndex >= 0)
//		{
//			D3DXMatrixInverse(&matParentInverse, NULL, &m_ExpObject[JH_Mesh.m_iParentIndex].m_matWorld);
//		}
//		matDefaultAnim = JH_Mesh.m_matWorld*matParentInverse;
//
//		D3DXVECTOR3 vPos, vScale;
//		D3DXQUATERNION qR;
//		D3DXMatrixDecompose(&vScale, &qR, &vPos, &matDefaultAnim);
//
//		JH_Mesh.m_vAnimPos = vPos;
//		JH_Mesh.m_vAnimScale = vScale;
//		JH_Mesh.m_qAnimRotation = qR;
//		D3DXQuaternionIdentity(&JH_Mesh.m_qAnimScaleRotation);
//
//
//
//
//
//		int iRef = m_ExpObject[iObj].m_iRef;
//
//		//레퍼런싱한 메테리얼이없을경우의 조건
//		if (iRef >= 0)
//		{
//			if (m_ExpMtlList[iRef].submtl.size() > 0)
//			{
//				int iSubMtrl = m_ExpMtlList[iRef].submtl.size();
//				JH_Mesh.subMesh.resize(iSubMtrl);
//				for (int i = 0; i < iSubMtrl; i++)
//				{
//					if (m_ExpMtlList[iRef].submtl[i].m_MapList.size() > 0) {
//
//						JH_Mesh.subMesh[i].m_iTextIndex = I_Texture.Add(m_pd3dDevice.Get(),
//							m_ExpMtlList[iRef].submtl[i].m_MapList[0].szTextureName,
//							L"../../data/Obj/");
//
//						
//				
//						JH_Mesh.subMesh[i].m_pTexture = I_Texture.GetPtr(JH_Mesh.subMesh[i].m_iTextIndex);
//					}
//				}
//			}
//			else
//			{
//				if (m_ExpMtlList[iRef].m_MapList.size() > 0) 
//				{
//					JH_Mesh.m_iTextIndex = I_Texture.Add(m_pd3dDevice.Get(),
//						m_ExpMtlList[iRef].m_MapList[0].szTextureName,
//						L"../../data/Obj/");
//
//				}
//		
//				
//				JH_Mesh.m_pTexture = I_Texture.GetPtr(JH_Mesh.m_iTextIndex);
//
//			}
//		}
//
//		//파일에 있는 월드행렬의 역행렬로 오브젝트를 원위치로 돌려놓고 다시 월드행렬로 위치시킴
//
//
//
//
//
//
//		//D3DXMatrixInverse(&JH_Mesh.m_matInverseWorld, NULL, &JH_Mesh.m_matWorld);
//
//		PNCT_VERTEX v;
//		int index;
//		// 데이터 복사
//		/*for (int iFace = 0; iFace < m_ExpObject[iObj].m_TriList.size(); iFace++)
//		{
//			for (int iVertex = 0; iVertex < 3; iVertex++)
//			{
//				AddVertex(iObj, iFace, iVertex, JH_Mesh);
//			}
//
//		}*/
//
//		if (JH_Mesh.subMesh.size() > 0)
//		{
//			for (int i = 0; i < JH_Mesh.subMesh.size(); i++)
//			{
//
//
//				JH_Mesh.subMesh[i].m_iNumFace = m_ExpObject[iObj].subMesh[i].m_TriList.size();
//				JH_Mesh.subMesh[i].m_iNumVertex = m_ExpObject[iObj].subMesh[i].m_TriList.size()*3;
//				JH_Mesh.subMesh[i].m_iBaseVertex += iBaseOffset;
//				iBaseOffset += JH_Mesh.subMesh[i].m_iNumVertex;
//		
//
//				// PNCT 버퍼에 한번에 몰아넣음
//				std::copy(m_ExpObject[iObj].subMesh[i].m_TriList.begin(),
//					m_ExpObject[iObj].subMesh[i].m_TriList.end(),
//					back_inserter(m_FaceBuffer));
//
//			}
//
//		}
//		else
//		{
//		
//			JH_Mesh.m_iNumFace = m_ExpObject[iObj].m_TriList.size();
//			JH_Mesh.m_iNumVertex = m_ExpObject[iObj].m_TriList.size() * 3;
//			JH_Mesh.m_iBaseVertex += iBaseOffset;
//			iBaseOffset += JH_Mesh.m_iNumVertex;
//
//			std::copy(m_ExpObject[iObj].m_TriList.begin(),
//				m_ExpObject[iObj].m_TriList.end(),
//				back_inserter(m_FaceBuffer));
//		}
//
//
//	}
//
//
//}
//bool	MaxObj::Parsing(const TCHAR* FileName)
//{
//	if (!OpenStream(FileName)) { return false; }
//
//	_fgetts(m_pBuffer, 256, m_pStream);
//	_stscanf(m_pBuffer, _T("%s %d %d %d %d %d %d \n"),m_pString,
//		&m_Scene.FirstFrame,
//		&m_Scene.LastFrame,
//		&m_Scene.FrameSpeed,
//		&m_Scene.TickPerFrame,
//		&m_Scene.iNumMaterial,
//		&m_Scene.iNumMesh);
//	
//	int iNumSubMtl=0;
//	int iNumTex;
//	m_ExpMtlList.resize(m_Scene.iNumMaterial);
//	for (int iMtrl = 0; iMtrl < m_Scene.iNumMaterial; iMtrl++)
//	{
//		_fgetts(m_pBuffer, 256, m_pStream);
//		_stscanf(m_pBuffer,_T("%s %d %s %d"), m_pString,
//			&m_iTemp, m_pString,
//			&iNumSubMtl);
//		m_ExpMtlList[iMtrl].submtl.resize(iNumSubMtl);
//		if (iNumSubMtl > 0)
//		{
//			for (int iSubMtrl = 0; iSubMtrl < iNumSubMtl; iSubMtrl++)
//			{
//				_fgetts(m_pBuffer, 256, m_pStream);
//				_stscanf(m_pBuffer, _T("%s %d %s %d\n"),
//					m_pString,
//					&iSubMtrl,
//					m_pString,
//					&iNumTex);
//			
//				m_ExpMtlList[iMtrl].submtl[iSubMtrl].m_MapList.resize(iNumTex);
//				for (int iTex = 0; iTex < iNumTex; iTex++)
//				{
//					_fgetts(m_pBuffer, 256, m_pStream);
//					_stscanf(m_pBuffer, _T("%s %d %d %s\n"),
//						m_pString,
//						&m_iTemp,
//						&m_ExpMtlList[iMtrl].submtl[iSubMtrl].m_MapList[iTex].iSubNo,
//						m_ExpMtlList[iMtrl].submtl[iSubMtrl].m_MapList[iTex].szTextureName);
//
//				}
//
//			}
//		}
//		else
//		{
//				
//			_fgetts(m_pBuffer, 256, m_pStream);
//			_stscanf(m_pBuffer, _T("%s  %d\n"),m_pString,
//				&iNumTex);
//			m_ExpMtlList[iMtrl].m_MapList.resize(iNumTex);
//			for (int iTex = 0; iTex < iNumTex; iTex++)
//			{
//				_fgetts(m_pBuffer, 256, m_pStream);
//				_stscanf(m_pBuffer, _T("%s %d %d %s\n"),
//					m_pString,
//					&m_iTemp,
//					&m_ExpMtlList[iMtrl].m_MapList[iTex].iSubNo,
//					m_ExpMtlList[iMtrl].m_MapList[iTex].szTextureName);
//
//			}
//
//		}
//
//	}
//	int iNumTri = 0;
//	int iNumVertex = 0;
//	int iNumFace = 0;
//	int iSubIndex = -1;
//	int LastSubIndex = -1;
//	int iAniArray[4];
//	m_ExpObject.resize(m_Scene.iNumMesh);
//	
//	for (int iObj = 0; iObj < m_ExpObject.size(); iObj++)
//	{
//
//
//		_fgetts(m_pBuffer, 256, m_pStream);
//		_stscanf(m_pBuffer, _T("%s %d %s %d %s %d %s %d %s %d %s %d \n"),
//			m_pString, &m_iTemp,
//			m_pString, &m_ExpObject[iObj].m_iRef,
//			m_pString, &iAniArray[0],
//			m_pString, &iAniArray[1],
//			m_pString, &iAniArray[2],
//			m_pString, &iAniArray[3]);
//
//		m_ExpObject[iObj].m_AnimTrackPos.resize(iAniArray[0]);
//		m_ExpObject[iObj].m_AnimTrackRotate.resize(iAniArray[1]);
//		m_ExpObject[iObj].m_AnimTrackScale.resize(iAniArray[2]);
//		m_ExpObject[iObj].subMesh.resize(iAniArray[3]);
//
//		_fgetts(m_pBuffer, 256, m_pStream);
//		_stscanf(m_pBuffer, _T("%s %s\n"),
//			m_ExpObject[iObj].m_szName,
//			m_ExpObject[iObj].m_szParentName);
//
//		_fgetts(m_pBuffer, 256, m_pStream);
//		_stscanf(m_pBuffer, _T("\t%s\n"), m_pString);
//		_fgetts(m_pBuffer, 256, m_pStream);
//		_stscanf(m_pBuffer, _T("%f %f %f %f\n"),
//			&m_ExpObject[iObj].m_matWorld._11, &m_ExpObject[iObj].m_matWorld._12, &m_ExpObject[iObj].m_matWorld._13, &m_ExpObject[iObj].m_matWorld._14);
//		_fgetts(m_pBuffer, 256, m_pStream);
//		_stscanf(m_pBuffer, _T("%f %f %f %f\n"),
//			&m_ExpObject[iObj].m_matWorld._21, &m_ExpObject[iObj].m_matWorld._22, &m_ExpObject[iObj].m_matWorld._23, &m_ExpObject[iObj].m_matWorld._24);
//		_fgetts(m_pBuffer, 256, m_pStream);
//		_stscanf(m_pBuffer, _T("%f %f %f %f\n"),
//			&m_ExpObject[iObj].m_matWorld._31, &m_ExpObject[iObj].m_matWorld._32, &m_ExpObject[iObj].m_matWorld._33, &m_ExpObject[iObj].m_matWorld._34);
//		_fgetts(m_pBuffer, 256, m_pStream);
//		_stscanf(m_pBuffer, _T("\t%f %f %f %f\n"),
//			&m_ExpObject[iObj].m_matWorld._41, &m_ExpObject[iObj].m_matWorld._42, &m_ExpObject[iObj].m_matWorld._43, &m_ExpObject[iObj].m_matWorld._44);
//
//
//		if (m_ExpObject[iObj].subMesh.size() > 0)
//		{
//
//			_fgetts(m_pBuffer, 256, m_pStream);
//			_stscanf(m_pBuffer, _T("%s\n"), m_pString);
//			for (int iSubMesh = 0; iSubMesh <
//				m_ExpObject[iObj].subMesh.size(); iSubMesh++)
//			{
//				_fgetts(m_pBuffer, 256, m_pStream);
//				_stscanf(m_pBuffer, _T("%d %d\n"),
//					&m_iTemp,
//					&iNumFace);
//				m_ExpObject[iObj].subMesh[iSubMesh].m_TriList.resize(iNumFace);
//			}
//
//
//			for (int iSubMesh = 0; iSubMesh <
//				m_ExpObject[iObj].subMesh.size(); iSubMesh++)
//			{
//
//				if (m_ExpObject[iObj].subMesh[iSubMesh].m_TriList.size() > 0)
//				{
//					_fgetts(m_pBuffer, 256, m_pStream);
//					_stscanf(m_pBuffer, _T("%s %d\n"), m_pString,&m_iTemp);
//				}
//				for (int iFace = 0; iFace < m_ExpObject[iObj].subMesh[iSubMesh].m_TriList.size(); iFace++)
//				{
//
//					int iNumVertex = 3;
//					for (int iVertex = 0; iVertex < iNumVertex; iVertex++)
//					{
//
//						_fgetts(m_pBuffer, 256, m_pStream);
//						_stscanf(m_pBuffer, _T("\t%f %f %f\n "),
//							&m_ExpObject[iObj].subMesh[iSubMesh].m_TriList[iFace].v[iVertex].p.x,
//							&m_ExpObject[iObj].subMesh[iSubMesh].m_TriList[iFace].v[iVertex].p.y,
//							&m_ExpObject[iObj].subMesh[iSubMesh].m_TriList[iFace].v[iVertex].p.z
//						);
//
//						_fgetts(m_pBuffer, 256, m_pStream);
//						_stscanf(m_pBuffer, _T("\t%f %f %f\n "),
//							&m_ExpObject[iObj].subMesh[iSubMesh].m_TriList[iFace].v[iVertex].n.x,
//							&m_ExpObject[iObj].subMesh[iSubMesh].m_TriList[iFace].v[iVertex].n.y,
//							&m_ExpObject[iObj].subMesh[iSubMesh].m_TriList[iFace].v[iVertex].n.z
//						);
//						_fgetts(m_pBuffer, 256, m_pStream);
//						_stscanf(m_pBuffer, _T("\t%f %f %f %f\n "),
//							&m_ExpObject[iObj].subMesh[iSubMesh].m_TriList[iFace].v[iVertex].c.x,
//							&m_ExpObject[iObj].subMesh[iSubMesh].m_TriList[iFace].v[iVertex].c.y,
//							&m_ExpObject[iObj].subMesh[iSubMesh].m_TriList[iFace].v[iVertex].c.z,
//							&m_ExpObject[iObj].subMesh[iSubMesh].m_TriList[iFace].v[iVertex].c.w
//						);
//						_fgetts(m_pBuffer, 256, m_pStream);
//						_stscanf(m_pBuffer, _T("\t%f %f\n "),
//							&m_ExpObject[iObj].subMesh[iSubMesh].m_TriList[iFace].v[iVertex].t.x,
//							&m_ExpObject[iObj].subMesh[iSubMesh].m_TriList[iFace].v[iVertex].t.y
//						);
//
//					}
//
//				}
//			}
//		}
//		else
//		{
//
//			_fgetts(m_pBuffer, 256, m_pStream);
//			_stscanf(m_pBuffer, _T("%s %d\n"),
//				m_pString,
//				&iNumFace);
//			 m_ExpObject[iObj].m_TriList.resize(iNumFace);
//			if (m_ExpObject[iObj].m_TriList.size() > 0)
//			{
//				_fgetts(m_pBuffer, 256, m_pStream);
//				_stscanf(m_pBuffer, _T("%s %d\n"), m_pString,&m_ExpObject[iObj].m_iRef);
//			}
//
//
//			for (int iFace = 0; iFace < m_ExpObject[iObj].m_TriList.size(); iFace++)
//			{
//
//
//				int iNumVertex = 3;
//				for (int iVertex = 0; iVertex < iNumVertex; iVertex++)
//				{
//
//
//					_fgetts(m_pBuffer, 256, m_pStream);
//					_stscanf(m_pBuffer, _T("\t%f %f %f\n "),
//						&m_ExpObject[iObj].m_TriList[iFace].v[iVertex].p.x,
//						&m_ExpObject[iObj].m_TriList[iFace].v[iVertex].p.y,
//						&m_ExpObject[iObj].m_TriList[iFace].v[iVertex].p.z
//						);
//			
//					_fgetts(m_pBuffer, 256, m_pStream);
//					_stscanf(m_pBuffer, _T("\t%f %f %f\n "),
//						&m_ExpObject[iObj].m_TriList[iFace].v[iVertex].n.x,
//						&m_ExpObject[iObj].m_TriList[iFace].v[iVertex].n.y,
//						&m_ExpObject[iObj].m_TriList[iFace].v[iVertex].n.z
//					);
//					_fgetts(m_pBuffer, 256, m_pStream);
//					_stscanf(m_pBuffer, _T("\t%f %f %f %f\n "),
//						&m_ExpObject[iObj].m_TriList[iFace].v[iVertex].c.x,
//						&m_ExpObject[iObj].m_TriList[iFace].v[iVertex].c.y,
//						&m_ExpObject[iObj].m_TriList[iFace].v[iVertex].c.z,
//						&m_ExpObject[iObj].m_TriList[iFace].v[iVertex].c.w
//					);
//					_fgetts(m_pBuffer, 256, m_pStream);
//					_stscanf(m_pBuffer, _T("\t%f %f\n "),
//						&m_ExpObject[iObj].m_TriList[iFace].v[iVertex].t.x,
//						&m_ExpObject[iObj].m_TriList[iFace].v[iVertex].t.y
//					);
//				
//				}
//
//			}
//		}
//		_fgetts(m_pBuffer, 256, m_pStream);
//		_stscanf(m_pBuffer, _T("%s \n"),m_pString);
//		_fgetts(m_pBuffer, 256, m_pStream);
//		_stscanf(m_pBuffer, _T("%s \n"), m_pString);
//		for (int iTrack = 0; iTrack < m_ExpObject[iObj].m_AnimTrackPos.size(); iTrack++)
//		{
//			_fgetts(m_pBuffer, 256, m_pStream);
//			_stscanf(m_pBuffer, _T("\t %d %f %f %f \n"),
//
//				&m_ExpObject[iObj].m_AnimTrackPos[iTrack].iTick,
//				&m_ExpObject[iObj].m_AnimTrackPos[iTrack].p.x,
//				&m_ExpObject[iObj].m_AnimTrackPos[iTrack].p.y,
//				&m_ExpObject[iObj].m_AnimTrackPos[iTrack].p.z);
//
//		}
//		_fgetts(m_pBuffer, 256, m_pStream);
//		_stscanf(m_pBuffer, _T("%s \n"), m_pString);
//		for (int iTrack = 0; iTrack < m_ExpObject[iObj].m_AnimTrackRotate.size(); iTrack++)
//		{
//			_fgetts(m_pBuffer, 256, m_pStream);
//			_stscanf(m_pBuffer, _T("\t %d %f %f %f %f \n"),
//
//				&m_ExpObject[iObj].m_AnimTrackRotate[iTrack].iTick,
//				&m_ExpObject[iObj].m_AnimTrackRotate[iTrack].q.x,
//				&m_ExpObject[iObj].m_AnimTrackRotate[iTrack].q.y,
//				&m_ExpObject[iObj].m_AnimTrackRotate[iTrack].q.z);
//
//		}
//		_fgetts(m_pBuffer, 256, m_pStream);
//		_stscanf(m_pBuffer, _T("%s \n"), m_pString);
//		for (int iTrack = 0; iTrack < m_ExpObject[iObj].m_AnimTrackScale.size(); iTrack++)
//		{
//			_fgetts(m_pBuffer, 256, m_pStream);
//			_stscanf(m_pBuffer, _T("\t %d %f %f %f %f %f %f %f \n"),
//
//				&m_ExpObject[iObj].m_AnimTrackScale[iTrack].iTick,
//				&m_ExpObject[iObj].m_AnimTrackScale[iTrack].p.x,
//				&m_ExpObject[iObj].m_AnimTrackScale[iTrack].p.y,
//				&m_ExpObject[iObj].m_AnimTrackScale[iTrack].p.z,
//				&m_ExpObject[iObj].m_AnimTrackScale[iTrack].q.x,
//				&m_ExpObject[iObj].m_AnimTrackScale[iTrack].q.y,
//				&m_ExpObject[iObj].m_AnimTrackScale[iTrack].q.z);
//
//		}
//	}
//	
//
//}
//bool MaxObj::Init()
//{
//	return true;
//}
//bool MaxObj::Frame()
//{
//	float fTime = 0;
//	fTime = g_SecondPerFrame * m_Scene.FrameSpeed*m_Scene.TickPerFrame;
//
//	if (fTime >= m_Scene.TickPerFrame)
//	{
//		fTime = m_Scene.TickPerFrame;
//	}
//	if (fTime >= m_Scene.TickPerFrame) fTime = m_Scene.TickPerFrame;
//
//	m_fElapseTick += fTime;
//	if (m_fElapseTick >= m_Scene.LastFrame*m_Scene.TickPerFrame)
//	{
//		m_fElapseTick = 0.0f;
//	}
//	D3DXVECTOR3 vPos;
//	D3DXVECTOR3 vScale(1, 1, 1);
//	D3DXMATRIX matRotation;
//	D3DXMATRIX matScaleRotation;
//	D3DXMATRIX matInverseScaleRotation;
//	D3DXMATRIX matScale;
//
//	D3DXQUATERNION Quat, qScale;
//
//
//
//
//	for (int iObj = 0; iObj < m_ExpObject.size(); iObj++)
//	{
//		
//		D3DXMatrixIdentity(&m_ExpObject[iObj].m_matCalculation);
//
//		D3DXQuaternionIdentity(&Quat);
//		D3DXMatrixIdentity(&matRotation);
//		D3DXMatrixIdentity(&matScaleRotation);
//		D3DXMatrixIdentity(&matScale);
//		D3DXMatrixIdentity(&matInverseScaleRotation);
//
//
//		vPos = m_ExpObject[iObj].m_vAnimPos;
//		Quat = m_ExpObject[iObj].m_qAnimRotation;
//		vScale = m_ExpObject[iObj].m_vAnimScale;
//		qScale = m_ExpObject[iObj].m_qAnimScaleRotation;
//
//		D3DXMatrixScaling(&matScale, vScale.x, vScale.y, vScale.z);
//		D3DXMatrixRotationQuaternion(&matRotation, &m_ExpObject[iObj].m_qAnimRotation);
//
//
//
//
//		if (m_ExpObject[iObj].m_AnimTrackPos.size() > 0)
//		{
//			AnimTrack start, end;
//			start.iTick = 0;
//			start.p = vPos;
//			int finalindex = m_ExpObject[iObj].m_AnimTrackPos.size() - 1;
//			end = m_ExpObject[iObj].m_AnimTrackPos[finalindex];
//			for (int i = 0; i < m_ExpObject[iObj].m_AnimTrackPos.size(); i++)
//			{
//				if (m_ExpObject[iObj].m_AnimTrackPos[i].iTick <= m_fElapseTick)
//				{
//					start = m_ExpObject[iObj].m_AnimTrackPos[i];
//				}
//				if (m_ExpObject[iObj].m_AnimTrackPos[i].iTick > m_fElapseTick)
//				{
//					end = m_ExpObject[iObj].m_AnimTrackPos[i];
//					break;
//				}
//			}
//
//			float step = end.iTick - start.iTick;
//
//			float t = 0.0f;
//			if (step > 0.0f)
//			{
//				float t = (m_fElapseTick - start.iTick) / step;
//			}
//			D3DXVec3Lerp(&vPos, &start.p, &end.p, t);
//		}
//		if (m_ExpObject[iObj].m_AnimTrackRotate.size() > 0)
//		{
//			AnimTrack start, end;
//			start.iTick = 0;
//			start.q = Quat;
//			int finalindex = m_ExpObject[iObj].m_AnimTrackRotate.size() - 1;
//			end = m_ExpObject[iObj].m_AnimTrackRotate[finalindex];
//
//			for (int i = 0; i < m_ExpObject[iObj].m_AnimTrackRotate.size(); i++)
//			{
//				if (m_ExpObject[iObj].m_AnimTrackRotate[i].iTick <= m_fElapseTick)
//				{
//					start = m_ExpObject[iObj].m_AnimTrackRotate[i];
//				}
//				if (m_ExpObject[iObj].m_AnimTrackRotate[i].iTick > m_fElapseTick)
//				{
//					end = m_ExpObject[iObj].m_AnimTrackRotate[i];
//					break;
//				}
//			}
//
//
//
//			float step = end.iTick - start.iTick;
//			float t = 0.0f;
//			if (step > 0.0f)
//			{
//				float t = (m_fElapseTick - start.iTick) / step;
//			}
//			D3DXQuaternionSlerp(&Quat, &start.q, &end.q, t);
//			D3DXMatrixRotationQuaternion(&matRotation, &Quat);
//
//
//		}
//		if (m_ExpObject[iObj].m_AnimTrackScale.size() > 0)
//		{
//			AnimTrack start, end;
//			start.iTick = 0;
//			start.p = vScale;
//			start.q = qScale;
//
//			int finalindex = m_ExpObject[iObj].m_AnimTrackScale.size() - 1;
//			end = m_ExpObject[iObj].m_AnimTrackScale[finalindex];
//			for (int i = 0; i < m_ExpObject[iObj].m_AnimTrackScale.size(); i++)
//			{
//				if (m_ExpObject[iObj].m_AnimTrackScale[i].iTick <= m_fElapseTick)
//				{
//					start = m_ExpObject[iObj].m_AnimTrackScale[i];
//				}
//				if (m_ExpObject[iObj].m_AnimTrackScale[i].iTick > m_fElapseTick)
//				{
//					end = m_ExpObject[iObj].m_AnimTrackScale[i];
//					break;
//				}
//			}
//
//			float step = end.iTick - start.iTick;
//			float t = 0.0f;
//			if (step > 0.0f)
//			{
//				float t = (m_fElapseTick - start.iTick) / step;
//			}
//			D3DXQuaternionSlerp(&Quat, &start.q, &end.q, t);
//			D3DXMatrixRotationQuaternion(&matScaleRotation, &Quat);
//			D3DXMatrixInverse(&matInverseScaleRotation, NULL, &matScaleRotation);
//
//			D3DXVec3Lerp(&vScale, &start.p, &end.p, t);
//			D3DXMatrixScaling(&matScale, vScale.x, vScale.y, vScale.z);
//
//			matScale = matInverseScaleRotation * matScale*matScaleRotation;
//
//		}
//
//
//
//		m_ExpObject[iObj].m_matCalculation = matScale * matRotation;
//		m_ExpObject[iObj].m_matCalculation._41 = vPos.x;
//		m_ExpObject[iObj].m_matCalculation._42 = vPos.y;
//		m_ExpObject[iObj].m_matCalculation._43 = vPos.z;
//
//		if (m_ExpObject[iObj].m_iParentIndex >= 0)
//		{
//			D3DXMATRIX matParent = m_ExpObject[m_ExpObject[iObj].m_iParentIndex].m_matCalculation;
//			m_ExpObject[iObj].m_matCalculation *= matParent;
//		}
//	}
//
//	return true;
//}
//bool MaxObj::Render()
//{
//	PreRender();
//	for (int iObj = 0; iObj < m_ExpObject.size() ;iObj++)
//	{
//		m_ExpObject[iObj].m_cbData = m_cbData;
//		m_ExpObject[iObj].m_matCalculation *= m_matWorld;
//	
//		D3DXMatrixTranspose(&m_ExpObject[iObj].m_cbData.matWorld,
//			&m_ExpObject[iObj].m_matCalculation);
//
//
//		m_pContext->UpdateSubresource(
//			m_pConstantBuffer.Get(),
//			0, NULL, &m_ExpObject[iObj].m_cbData, 0, 0);
//
//		if (m_ExpObject[iObj].subMesh.size() > 0)
//		{
//			for (int iSub = 0; iSub < m_ExpObject[iObj].subMesh.size(); iSub++)
//			{
//				if (m_ExpObject[iObj].subMesh[iSub].m_iNumVertex <= 0) continue;
//				if (m_ExpObject[iObj].subMesh[iSub].m_pTexture != NULL)
//				{
//
//					m_pContext->PSSetShaderResources(0, 1, &m_ExpObject[iObj].subMesh[iSub].m_pTexture->m_pTextureRV);
//					m_pContext->Draw(m_ExpObject[iObj].subMesh[iSub].m_iNumVertex,
//						m_ExpObject[iObj].subMesh[iSub].m_iBaseVertex);
//				}
//				else
//				{
//					m_pContext->Draw(m_ExpObject[iObj].subMesh[iSub].m_iNumVertex,
//						m_ExpObject[iObj].subMesh[iSub].m_iBaseVertex);
//				}
//
//			}
//
//		}
//		else
//		{
//			if (m_ExpObject[iObj].m_pTexture != nullptr)
//			{
//				m_pContext->PSSetShaderResources(0, 1, &m_ExpObject[iObj].m_pTexture->m_pTextureRV);
//				m_pContext->Draw(m_ExpObject[iObj].m_iNumVertex,
//					m_ExpObject[iObj].m_iBaseVertex);
//			}
//			else
//			{
//				m_pContext->Draw(m_ExpObject[iObj].m_iNumVertex,
//					m_ExpObject[iObj].m_iBaseVertex);
//			}
//
//		}
//
//	}
//	return true;
//}
//bool MaxObj::Release()
//{
//	return true;
//}
//
//bool	MaxObj::OpenStream(const TCHAR* FileName)
//{
//	m_pStream = _tfopen(FileName, _T("rt"));
//	if (m_pStream==nullptr)
//	{ 
//		return false;
//	}
//	return true;
//}
//bool	MaxObj::CloseStream() 
//{
//	fclose(m_pStream);
//	return true;
//}