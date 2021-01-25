// JH_ObjForm.cpp: 구현 파일
//

#include "stdafx.h"
#include "JH_Tool.h"
#include "JH_ObjForm.h"
#include "afxdialogex.h"


// JH_ObjForm 대화 상자

IMPLEMENT_DYNAMIC(JH_ObjForm, CFormView)

JH_ObjForm::JH_ObjForm()
	: CFormView(IDD_JH_ObjForm)
	, m_FileName(_T(""))
{

}

JH_ObjForm::~JH_ObjForm()
{
}

JH_ObjForm* JH_ObjForm::CreateOne(CWnd* pParent)//하나의 윈도우에 하나가 생성되게 만들기위한함수
{
	JH_ObjForm* pForm = new JH_ObjForm;
	pForm->Create(NULL, NULL, WS_CHILD | WS_VISIBLE,
		CRect(0, 0, 500, 500), pParent, 0, NULL);
	return pForm;
}
void JH_ObjForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_FileName);
}
void JH_ObjForm::OnBnClickedButton2()
{
	UpdateData(FALSE);

	CString FileName;

	CFileDialog dlg(FALSE, L"bmp|jpg", NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,
		L"bmp Files(*.bmp)|*.bmp| All Files(*.*)|*.*|", this);

	if (dlg.DoModal() == IDOK)
	{
		FileName = dlg.GetPathName();

		m_FileName = FileName;

	}


	UpdateData(FALSE);
}
void JH_ObjForm::OnBnClickedButton3()
{
	UpdateData(TRUE);
	CJHToolApp* pApp = (CJHToolApp*)AfxGetApp();
	D3DXMATRIX mWorld;
	D3DXMatrixIdentity(&mWorld);
	pApp->m_Sample.CreateObj(
		m_FileName,
		mWorld);
}


BEGIN_MESSAGE_MAP(JH_ObjForm, CFormView)
	ON_BN_CLICKED(IDC_BUTTON2, &JH_ObjForm::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &JH_ObjForm::OnBnClickedButton3)
END_MESSAGE_MAP()


// JH_ObjForm 메시지 처리기
#include"pch.h"



