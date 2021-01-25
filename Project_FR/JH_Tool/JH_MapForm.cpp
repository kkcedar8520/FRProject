#pragma once
// JH_MapForm.cpp: 구현 파일
//

#include "pch.h"
#include "JH_Tool.h"
#include "JH_MapForm.h"
#include "afxdialogex.h"


// JH_MapForm 대화 상자

IMPLEMENT_DYNAMIC(JH_MapForm, CFormView)

JH_MapForm::JH_MapForm()
	: CFormView(IDD_JH_MapForm)
	, m_iWidth(8)
	, m_iHeight(8)
	, m_iCellCount(2)
	, m_iCellSize(1)
	, m_TextrueName(_T(""))
	, m_NormalMapFile(_T(""))
	, m_Brush(_T(""))
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
	pApp->m_Sample.CreateMap(
		m_iWidth,
		m_iHeight,
		m_iCellCount,
		m_iCellSize,
		m_TextrueName,
		m_NormalMapFile);
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
	static bool Tick= 1;
	
	CFileDialog dlg(FALSE, L"bmp|jpg", NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,
		L"bmp Files(*.bmp)|*.bmp| All Files(*.*)|*.*|", this);

	if (dlg.DoModal()==IDOK)
	{
		FileName = dlg.GetPathName();

		if (Tick)
		{
			m_TextrueName = FileName;
			Tick = false;
		}
		else
		{
			m_NormalMapFile = FileName;
			Tick = true;
		}
		UpdateData(FALSE);
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void JH_MapForm::OnEnChangeEdit7()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}




void JH_MapForm::OnBnClickedOk4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	CJHToolApp* pApp = (CJHToolApp*)AfxGetApp();

	pApp->m_Sample.m_Map->m_bMapEdit= !pApp->m_Sample.m_Map->m_bMapEdit;
}


void JH_MapForm::OnBnClickedOk5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	CJHToolApp* pApp = (CJHToolApp*)AfxGetApp();

	pApp->m_Sample.bSplatting = !pApp->m_Sample.bSplatting;
}
