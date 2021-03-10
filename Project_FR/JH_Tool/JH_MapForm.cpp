#pragma once
// JH_MapForm.cpp: 구현 파일
//

#include "pch.h"
#include "JH_Tool.h"
#include "JH_MapForm.h"
#include "afxdialogex.h"
#include"TextureMgr.h"
// JH_MapForm 대화 상자

IMPLEMENT_DYNAMIC(JH_MapForm, CFormView)

JH_MapForm::JH_MapForm()
	: CFormView(IDD_JH_MapForm)
	, m_iWidth(8)
	, m_iHeight(8)
	, m_iCellCount(2)
	, m_iCellSize(1)
	, m_TextrueName(_T("stones.bmp"))
	, m_NormalMapFile(_T("stones_NM_height.tga"))
	, m_HeightMapFile(_T("Generic_Rubber_A_Height_129.bmp"))
	, m_Brush(_T(""))
	, m_SplattTexture1(_T("032.bmp"))
	, m_SplattTexture2(_T(""))
	, m_SplattTexture3(_T(""))
	, m_SplattTexture4(_T(""))
	, m_SplattTex1Alpha(0)
	, m_SplattTex2Alpha(0)
	, m_SplattTex3Alpha(0)
	, m_SplattTex4Alpha(0)
	, m_SaveFileName(_T(""))
	, m_LoadFileName(_T(""))
	, m_SplattTexture(_T(""))
	, m_HeightValue(0)
	, m_fRadius(1)

	, m_CharX(0)
	, m_CharY(0)
	, m_CharZ(0)
{

}

JH_MapForm* JH_MapForm::CreateOne(CWnd* pParent)//하나의 윈도우에 하나가 생성되게 만들기위한함수
{
	JH_MapForm* pForm = new JH_MapForm;
	pForm->Create(NULL, NULL, WS_CHILD | WS_VISIBLE,
		CRect(0, 0, 500, 500), pParent, 0, NULL);
	return pForm;
}
JH_MapForm::~JH_MapForm()
{


}

void JH_MapForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_iWidth);
	DDX_Text(pDX, IDC_EDIT2, m_iHeight);
	DDX_Text(pDX, IDC_EDIT3, m_iCellCount);
	DDX_Text(pDX, IDC_EDIT4, m_iCellSize);
	DDX_Text(pDX, IDC_EDIT5, m_TextrueName);
	DDX_Text(pDX, IDC_EDIT6, m_NormalMapFile);
	DDX_Text(pDX, IDC_EDIT8, m_Brush);
	DDX_Text(pDX, IDC_EDIT10, m_SplattTexture1);
	DDX_Text(pDX, IDC_EDIT9, m_SplattTexture2);
	DDX_Text(pDX, IDC_EDIT11, m_SplattTexture3);
	DDX_Text(pDX, IDC_EDIT12, m_SplattTexture4);
	DDX_Text(pDX, IDC_EDIT14, m_SplattTex1Alpha);
	DDX_Text(pDX, IDC_EDIT15, m_SplattTex2Alpha);
	DDX_Text(pDX, IDC_EDIT16, m_SplattTex3Alpha);
	DDX_Text(pDX, IDC_EDIT17, m_SplattTex4Alpha);
	DDX_Text(pDX, IDC_EDIT18, m_SaveFileName);
	DDX_Text(pDX, IDC_EDIT19, m_LoadFileName);
	DDX_Text(pDX, IDC_EDIT20, m_SplattTexture);
	DDX_Text(pDX, IDC_EDIT13, m_HeightValue);
	DDX_Text(pDX, IDC_EDIT7, m_fRadius);
	DDX_Text(pDX, IDC_EDIT21, m_HeightMapFile);
	DDX_Text(pDX, IDC_CharX, m_CharX);
	DDX_Text(pDX, IDC_CharY, m_CharY);
	DDX_Text(pDX, IDC_CharZ, m_CharZ);
}


BEGIN_MESSAGE_MAP(JH_MapForm, CFormView)
	ON_BN_CLICKED(IDCANCEL, &JH_MapForm::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &JH_MapForm::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT5, &JH_MapForm::OnEnChangeEdit5)
	ON_BN_CLICKED(IDOK2, &JH_MapForm::OnBnClickedOk2)
	ON_EN_CHANGE(IDC_EDIT7, &JH_MapForm::OnEnChangeEdit7)
	ON_BN_CLICKED(IDOK4, &JH_MapForm::OnBnClickedOk4)
	ON_BN_CLICKED(IDOK4, &JH_MapForm::OnBnClickedOk4)
	ON_BN_CLICKED(IDOK5, &JH_MapForm::OnBnClickedOk5)
	ON_BN_CLICKED(IDOK6, &JH_MapForm::OnBnClickedOk6)
	ON_BN_CLICKED(IDOK7, &JH_MapForm::OnSplattTexture2BnClickedOk)
	ON_BN_CLICKED(IDOK8, &JH_MapForm::OnSplattTexture3BnClickedOk)
	ON_BN_CLICKED(IDOK9, &JH_MapForm::OnSplattTexture4BnClickedOk)
//	ON_EN_UPDATE(IDC_EDIT14, &JH_MapForm::OnUpdateSplattTex1)
	ON_EN_CHANGE(IDC_EDIT14, &JH_MapForm::OnEnChangeEdit14)
	ON_EN_CHANGE(IDC_EDIT15, &JH_MapForm::OnEnChangeEdit15)
	ON_EN_CHANGE(IDC_EDIT16, &JH_MapForm::OnEnChangeEdit16)
	ON_EN_CHANGE(IDC_EDIT17, &JH_MapForm::OnEnChangeEdit17)
	ON_BN_CLICKED(IDOK3, &JH_MapForm::OnSaveMapData)
	ON_BN_CLICKED(IDOK10, &JH_MapForm::OnLoadMapData)
	ON_EN_CHANGE(IDC_EDIT20, &JH_MapForm::OnSplattFile20)
	ON_EN_CHANGE(IDC_EDIT13, &JH_MapForm::OnMapUpDown)
	ON_BN_CLICKED(IDOK11, &JH_MapForm::OnMapFlatt)
	ON_BN_CLICKED(IDOK12, &JH_MapForm::OnSetCharPos)
END_MESSAGE_MAP()


// JH_MapForm 메시지 처리기


void JH_MapForm::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void JH_MapForm::OnBnClickedOk()
{
	
	UpdateData(TRUE);
	CJHToolApp* pApp = (CJHToolApp*)AfxGetApp();




	I_MapMgr.CreateMap(L"Basic", m_iWidth,
		m_iHeight,
		m_iCellCount,
		m_iCellSize,
		m_TextrueName,
		m_NormalMapFile,
		m_HeightMapFile);

	I_MapMgr.SetCamera(pApp->m_Core.m_pMainCamera.get());

	pApp->m_Core.m_CS.Release();
	pApp->m_Core.m_CS.CreateComputeShader(L"../../data/shader/ComputeShader.hlsl","CSMAIN");
	pApp->m_Core.m_CSBuf.iCol = I_MapMgr.GetCurrentMap()->m_pMap->m_iColumNum - 1;
	pApp->m_Core.m_CSBuf.iRow = I_MapMgr.GetCurrentMap()->m_pMap->m_iRowNum - 1;

	pApp->m_Core.m_CS.CreateStreamSRV(I_MapMgr.GetCurrentMap()->m_pMap->m_iRowNum - 1, I_MapMgr.GetCurrentMap()->m_pMap->m_iColumNum - 1);
	pApp->m_Core.m_CS.SetStructureBuffer(&pApp->m_Core.m_CSBuf,sizeof(CSBUFF));

	I_MapMgr.GetCurrentMap()->m_pMap->SetSplattingAlphaShaderResouceView(pApp->m_Core.m_CS.m_pDescSrv.Get());
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void JH_MapForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	UpdateData();
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}


void JH_MapForm::OnEnChangeEdit5()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void JH_MapForm::OnBnClickedOk2()
{
	UpdateData(FALSE);

	CString FileName;
	static int Tick= 0;
	
	CFileDialog dlg(FALSE, L"bmp|jpg", NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,
		L"bmp Files(*.bmp)|*.bmp| All Files(*.*)|*.*|", this);
	
	TCHAR szFileName[MAX_PATH];
	TCHAR Drive[MAX_PATH];
	TCHAR Dir[MAX_PATH];
	TCHAR FName[MAX_PATH];
	TCHAR Ext[MAX_PATH];
	T_STR DirBuf;
	if (dlg.DoModal()==IDOK)
	{
		FileName = dlg.GetPathName();
		_tsplitpath(FileName, Drive, Dir, FName, Ext);
		Ext[4] = 0;
		memset(szFileName, 0, sizeof(TCHAR) * MAX_PATH);
		TCHAR Mdir[MAX_PATH] = L"../../data/Map/";
		TCHAR* tok= wcstok(Dir, L"\\""");
		bool b = false;
		while (tok!=nullptr)
		{
			
			tok = wcstok(NULL, L"\\""");
			if (tok == nullptr)break;
			if (b)
			{
				DirBuf += L"/";
				DirBuf += tok;
			}
			if (StrStrW(tok,_T("data")))
			{
				b = true;
				DirBuf += L"../../";
				DirBuf += tok;
			}
		
		}
		DirBuf+= L"/";
		_stprintf_s(szFileName, _T("%s%s%s"), DirBuf.c_str(),FName, Ext);
		
		FileName = szFileName;
		switch (Tick)
		{
		case 0:
		{
			m_TextrueName = FileName;
			Tick++;
		}break;
		case 1:
		{
			m_NormalMapFile = FileName;
			Tick++;
		}break;
		case 2:
		{
			m_HeightMapFile = FileName;
			Tick = 0;
		}break;
		default:
		{
			Tick = 0;
		}
			break;
		}

		UpdateData(FALSE);
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void JH_MapForm::OnEnChangeEdit7()
{
	UpdateData(TRUE);

	CJHToolApp* pApp = (CJHToolApp*)AfxGetApp();
	pApp->m_Core.m_Sphere.Radius = m_fRadius;
	pApp->m_Core.m_CSBuf.fRadius = m_fRadius;
	UpdateData(TRUE);
}




void JH_MapForm::OnBnClickedOk4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	CJHToolApp* pApp = (CJHToolApp*)AfxGetApp();

	if(I_MapMgr.GetCurrentMap()!=nullptr)
	pApp->m_Core.m_eState = TOOLSTATE::HEIGHT;
	UpdateData(FALSE);
}


void JH_MapForm::OnBnClickedOk5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	CJHToolApp* pApp = (CJHToolApp*)AfxGetApp();

	pApp->m_Core.m_eState = TOOLSTATE::SPLATTING;
}




void JH_MapForm::OnBnClickedOk6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(FALSE);

	CString FileName;

	CJHToolApp* pApp = (CJHToolApp*)AfxGetApp();



	CFileDialog dlg(FALSE, L"bmp|jpg", NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,
		L"bmp Files(*.bmp)|*.bmp| All Files(*.*)|*.*|", this);
	if (dlg.DoModal() == IDOK)
	{
		FileName = dlg.GetPathName();
		m_SplattTexture1 = FileName;
		m_SplattTex1ID=I_MapMgr.GetCurrentMap()->m_pMap->AddSplattTexture(m_SplattTexture1,1);
		pApp->m_Core.m_CSBuf.iIndex = 0;
		UpdateData(FALSE);
	}
}


void JH_MapForm::OnSplattTexture2BnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(FALSE);
	CString FileName;

	CJHToolApp* pApp = (CJHToolApp*)AfxGetApp();
	CFileDialog dlg(FALSE, L"bmp|jpg", NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,
		L"bmp Files(*.bmp)|*.bmp| All Files(*.*)|*.*|", this);


	if (dlg.DoModal() == IDOK)
	{
		FileName = dlg.GetPathName();
		m_SplattTexture2 = FileName;
		m_SplattTex2ID = I_MapMgr.GetCurrentMap()->m_pMap->AddSplattTexture(m_SplattTexture2, 2);
		pApp->m_Core.m_CSBuf.iIndex = 1;
		UpdateData(FALSE);
	}
}


void JH_MapForm::OnSplattTexture3BnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(FALSE);
	CString FileName;

	CJHToolApp* pApp = (CJHToolApp*)AfxGetApp();
	CFileDialog dlg(FALSE, L"bmp|jpg", NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,
		L"bmp Files(*.bmp)|*.bmp| All Files(*.*)|*.*|", this);

	//if (dlg.DoModal() == IDOK)
	//{
	//	FileName = dlg.GetPathName();
	//	m_SplattTexture3 = FileName;
	//	m_SplattTex3ID = pApp->m_Core.m_Map->AddSplattTexture(m_SplattTexture3,3);
	//	pApp->m_Core.m_vBuf0[0].iIndex = 2;
	//	UpdateData(FALSE);
	//}
	if (dlg.DoModal() == IDOK)
	{
		FileName = dlg.GetPathName();
		m_SplattTexture3 = FileName;
		m_SplattTex3ID = I_MapMgr.GetCurrentMap()->m_pMap->AddSplattTexture(m_SplattTexture3, 3);
		pApp->m_Core.m_CSBuf.iIndex = 2;
		UpdateData(FALSE);
	}
}


void JH_MapForm::OnSplattTexture4BnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(FALSE);
	CString FileName;

	CJHToolApp* pApp = (CJHToolApp*)AfxGetApp();
	CFileDialog dlg(FALSE, L"bmp|jpg", NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,
		L"bmp Files(*.bmp)|*.bmp| All Files(*.*)|*.*|", this);

	if (dlg.DoModal() == IDOK)
	{
		FileName = dlg.GetPathName();
		m_SplattTexture4 = FileName;
		m_SplattTex4ID = I_MapMgr.GetCurrentMap()->m_pMap->AddSplattTexture(m_SplattTexture4, 4);
		pApp->m_Core.m_CSBuf.iIndex = 3;
		UpdateData(FALSE);
	}
}






void JH_MapForm::OnEnChangeEdit14()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.
	UpdateData(TRUE);
	


	//I_Texture.GetPtr(m_SplattTex1ID)->SetAlpha(m_SplattTex1Alpha);
	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
}


void JH_MapForm::OnEnChangeEdit15()
{
	UpdateData(TRUE);



	//I_Texture.GetPtr(m_SplattTex2ID)->SetAlpha(m_SplattTex2Alpha);
	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
}


void JH_MapForm::OnEnChangeEdit16()
{
	UpdateData(TRUE);

	

	//I_Texture.GetPtr(m_SplattTex3ID)->SetAlpha(m_SplattTex3Alpha);
	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
}


void JH_MapForm::OnEnChangeEdit17()
{
	UpdateData(TRUE);

	

	//I_Texture.GetPtr(m_SplattTex4ID)->SetAlpha(m_SplattTex4Alpha);
	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
}


void JH_MapForm::OnSaveMapData()
{
	UpdateData(FALSE);

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CJHToolApp* pApp = (CJHToolApp*)AfxGetApp();
	
	D3D11_TEXTURE2D_DESC td;
	ZeroMemory(&td, sizeof(td));
	td.Width = 160;
	td.Height = 160;
	td.MipLevels = 1;
	td.MiscFlags = 0;
	td.ArraySize = 1;
	td.SampleDesc.Count = 1;
	td.SampleDesc.Quality = 0;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	td.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	td.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	




	

	//CString ext;
	//ext = ".DDS";
	//m_SplattTexture += ext;
	//if (pApp->m_Core.pReadTexture.Get() != nullptr)
	//{

	//	hr = D3DX11SaveTextureToFile(pApp->m_Core.m_pContext,
	//		pApp->m_Core.pReadTexture.Get(),
	//		D3DX11_IFF_DDS, m_SplattTexture);
	//}

	//CString FileName;
	//CString sFath = _T("\\MapSave\\");

	//CFileDialog dlg(FALSE, L"bmp|jpg", NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,
	//	L"Map Files(*.Map)|*.Map| All Files(*.*)|*.*|", this);
	//dlg.m_ofn.lpstrInitialDir = sFath;

	//if (dlg.DoModal() == IDOK&& pApp->m_Core.m_Map!=nullptr)
	//{
	//	FileName = dlg.GetPathName();
	//	pApp->m_Core.m_Map->m_pSPTAFile = m_SplattTexture;
	//	pApp->m_Core.m_pSPTAFile = m_SplattTexture;
	//	//pApp->m_Core.SaveMapData(FileName);

	//	JH::I_MapMgr.SaveMapData(FileName);
	//	UpdateData(FALSE);
	//}


}


void JH_MapForm::OnLoadMapData()
{
	UpdateData(FALSE);
	CString FileName;
	CString sFath= _T("\\CBY_GameProject\\MapSave\\");

	CJHToolApp* pApp = (CJHToolApp*)AfxGetApp();
	CFileDialog dlg(FALSE, L"bmp|jpg", NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,
		L"Map Files(*.Map)|*.Map| All Files(*.*)|*.*|", this);
	dlg.m_ofn.lpstrInitialDir = sFath;
	
	if (dlg.DoModal() == IDOK)
	{
		FileName = dlg.GetPathName();
		m_LoadFileName = FileName;
		//I_MapMgr.AddMap(m_LoadFileName);
		//pApp->m_Core.m_Map=I_MapMgr.GetMap();
		//pApp->m_Core.m_QuadTree = I_MapMgr.GetCurrentQuadTree();
		//pApp->m_Core.LoadMapData(m_LoadFileName);
		UpdateData(FALSE);
	}
}


void JH_MapForm::OnSplattFile20()
{
	/*UpdateData(TRUE);
	CJHToolApp* pApp = (CJHToolApp*)AfxGetApp();
	if (pApp->m_Core.pUAVTexture)
	{
		CString ext;
		ext = ".DDS";
		m_SplattTexture += ext;
		
	}
	UpdateData(TRUE);*/
}


void JH_MapForm::OnMapUpDown()
{
	/*UpdateData(TRUE);

	CJHToolApp* pApp = (CJHToolApp*)AfxGetApp();
	pApp->m_Core.m_HeightVlaue = m_HeightValue;
	UpdateData(TRUE);*/
}


void JH_MapForm::OnMapFlatt()
{
	UpdateData(TRUE);
	CJHToolApp* pApp = (CJHToolApp*)AfxGetApp();

	
	pApp->m_Core.m_eState = TOOLSTATE::FLATTING;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}




void JH_MapForm::OnSetCharPos()
{
	
	//CJHToolApp* pApp = (CJHToolApp*)AfxGetApp();
	//UpdateData(TRUE);
	//pApp->m_Core.m_Map->SetCharPos(D3DXVECTOR3(m_CharX, m_CharY, m_CharZ));
	//UpdateData(FALSE);
}
