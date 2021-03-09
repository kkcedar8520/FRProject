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
	, m_SkinName(_T(""))
	, m_bSet(false)
	, m_BoneName(_T(""))
	, m_Value(0)
	, m_fScaleX(0)
	, m_fScaleY(0)
	, m_fScaleZ(0)
	, m_fTransX(0)
	, m_fTransZ(0)
	, m_fRotYaw(0)
	, m_fRotPit(0)
	, m_fRotRol(0)
	, m_fTransY(0)
	, m_Obj_ID(0)
	, m_ObjNode(0)
	, m_ObjFlag(0)
	, m_ObjPositionX(0)
	, m_ObjPositionY(0)
	, m_ObjPositionZ(0)
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
	DDX_Text(pDX, IDC_EDIT1, m_SkinName);
	DDX_Text(pDX, IDC_EDIT2, m_BoneName);
	DDX_Text(pDX, IDC_EDIT12, m_Value);
	DDX_Text(pDX, IDC_EDIT14, m_fScaleX);
	DDX_Text(pDX, IDC_EDIT15, m_fScaleY);
	DDX_Text(pDX, IDC_EDIT24, m_fScaleZ);
	DDX_Text(pDX, IDC_EDIT21, m_fTransX);
	DDX_Text(pDX, IDC_EDIT16, m_fTransZ);
	DDX_Text(pDX, IDC_EDIT22, m_fRotYaw);
	DDX_Text(pDX, IDC_EDIT23, m_fRotPit);
	DDX_Text(pDX, IDC_EDIT25, m_fRotRol);
	DDX_Text(pDX, IDC_EDIT19, m_fTransY);
	DDX_Control(pDX, IDC_LIST1, m_ObjectListBox);
	DDX_Text(pDX, IDC_SELECTOBJ, m_Obj_ID);
	DDX_Text(pDX, IDC_OBJNODE, m_ObjNode);
	DDX_Text(pDX, IDC_OBJFLAG, m_ObjFlag);
	DDX_Text(pDX, IDC_SELECTOBJ2, m_ObjPositionX);
	DDX_Text(pDX, IDC_SELECTOBJ3, m_ObjPositionY);
	DDX_Text(pDX, IDC_OBJFLAG2, m_ObjPositionZ);
}


void JH_ObjForm::OnBnClickedButton2()
{
	UpdateData(FALSE);

	CString FileName;

	static int Tick = 0;

	CFileDialog dlg(FALSE, L"bmp|jpg", NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,
		L"skn Files(*.skn)|*.skn|mtr Files(*.mtr)|*.mtr|All Files(*.*)|*.*|", this);

	TCHAR szFileName[MAX_PATH];
	TCHAR Drive[MAX_PATH];
	TCHAR Dir[MAX_PATH];
	TCHAR FName[MAX_PATH];
	TCHAR Ext[MAX_PATH];
	T_STR DirBuf;
	if (dlg.DoModal() == IDOK)
	{
		FileName = dlg.GetPathName();
		_tsplitpath(FileName, Drive, Dir, FName, Ext);
		Ext[4] = 0;
		memset(szFileName, 0, sizeof(TCHAR) * MAX_PATH);
		TCHAR Mdir[MAX_PATH] = L"../../data/Map/";
		TCHAR* tok = wcstok(Dir, L"\\""");
		bool b = false;
		while (tok != nullptr)
		{

			tok = wcstok(NULL, L"\\""");
			if (tok == nullptr)break;
			if (b)
			{
				DirBuf += L"/";
				DirBuf += tok;
			}
			if (StrStrW(tok, _T("data")))
			{
				b = true;
				DirBuf += L"../../";
				DirBuf += tok;
			}

		}
		DirBuf += L"/";
		_stprintf_s(szFileName, _T("%s%s%s"), DirBuf.c_str(), FName, Ext);



		FileName = szFileName;
		Tick = 1;
		m_SkinName = FileName;




		UpdateData(FALSE);
	}


}

void JH_ObjForm::OnBnClickedBoneLoad()
{

	UpdateData(FALSE);

	CString FileName;

	static int Tick = 0;

	CFileDialog dlg(FALSE, L"bmp|jpg", NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,
		L"md Files(*.md)|*.md|All Files(*.*)|*.*|", this);

	TCHAR szFileName[MAX_PATH];
	TCHAR Drive[MAX_PATH];
	TCHAR Dir[MAX_PATH];
	TCHAR FName[MAX_PATH];
	TCHAR Ext[MAX_PATH];
	T_STR DirBuf;
	if (dlg.DoModal() == IDOK)
	{
		FileName = dlg.GetPathName();
		_tsplitpath(FileName, Drive, Dir, FName, Ext);
		Ext[4] = 0;
		memset(szFileName, 0, sizeof(TCHAR) * MAX_PATH);
		TCHAR Mdir[MAX_PATH] = L"../../data/Model/Binary/";
		TCHAR* tok = wcstok(Dir, L"\\""");
		bool b = false;
		while (tok != nullptr)
		{

			tok = wcstok(NULL, L"\\""");
			if (tok == nullptr)break;
			if (b)
			{
				DirBuf += L"/";
				DirBuf += tok;
			}
			if (StrStrW(tok, _T("data")))
			{
				b = true;
				DirBuf += L"../../";
				DirBuf += tok;
			}

		}
		/*DirBuf += L"/";*/
		_stprintf_s(szFileName, _T("%s%s%s"), DirBuf.c_str(), FName, Ext);



		FileName = szFileName;
		m_BoneName = FileName;
		UpdateData(FALSE);
	}

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
void JH_ObjForm::OnBnClickedButton3()
{
	UpdateData(TRUE);
	CJHToolApp* pApp = (CJHToolApp*)AfxGetApp();
	D3DXMATRIX mWorld;
	D3DXMatrixIdentity(&mWorld);

	TCHAR szFileName[MAX_PATH];
	TCHAR Drive[MAX_PATH];
	TCHAR Dir[MAX_PATH];
	TCHAR FName[MAX_PATH];
	TCHAR Ext[MAX_PATH];
	T_STR DirBuf;
	CString FileName;
	CString SkinName, BoneName;

	std::wstring wstr;
	std::string str;

	BoneName = m_BoneName;
	_tsplitpath(BoneName, Drive, Dir, FName, Ext);
	BoneName = FName;


		
	
	wstr = FName;



	char buf[256] = { NULL };
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), &buf[0], wstr.size() + 1,nullptr,nullptr);
	
	str=buf;

	m_ObjectListBox.AddString(FName);


}


void JH_ObjForm::OnBnClickedObjectSelect()
{
	CJHToolApp* pApp = (CJHToolApp*)AfxGetApp();

	//pApp->m_Core.bSelect = true;
	//pApp->m_Core.m_ToolState = SELECT;
	//if(pApp->m_Core.m_pSelectMapObj)
	//pApp->m_Core.m_pSelectMapObj = nullptr;

}
void JH_ObjForm::OnBnClickedSet()
{
	CJHToolApp* pApp = (CJHToolApp*)AfxGetApp();
	//pApp->m_Core.bSet = true;


	//pApp->m_Core.m_ToolState = SETTING;


	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
void JH_ObjForm::OnBnClickedRotation()
{
	UpdateData(TRUE);
	CJHToolApp* pApp = (CJHToolApp*)AfxGetApp();


	//if (!pApp->m_Core.m_pSelectMapObj)return;
	//pApp->m_Core.m_fYaw =m_fRotYaw ;
	//pApp->m_Core.m_fPitch = m_fRotPit;
	//pApp->m_Core.m_fRoll = m_fRotRol;
	//pApp->m_Core.ObjRotation();
	//pApp->m_Core.m_QuadTree->ChangeObjectNode(pApp->m_Core.m_pSelectMapObj);


	UpdateData(FALSE);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
void JH_ObjForm::OnBnClickedMove()
{
	UpdateData(TRUE);
	CJHToolApp* pApp = (CJHToolApp*)AfxGetApp();

	//if (!pApp->m_Core.m_pSelectMapObj)return;

	//pApp->m_Core.m_ToolState = MOVE;
	//pApp->m_Core.m_fValue = m_Value;


	UpdateData(FALSE);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
void JH_ObjForm::OnBnClickedScale()
{
	UpdateData(TRUE);
	CJHToolApp* pApp = (CJHToolApp*)AfxGetApp();

	//if (!pApp->m_Core.m_pSelectMapObj)return;
	//if (m_fScaleX != 0.0f && m_fScaleY != 0.0f && m_fScaleZ != 0.0f)
	//{
	//	pApp->m_Core.m_fScaleX = m_fScaleX;
	//	pApp->m_Core.m_fScaleY = m_fScaleY;
	//	pApp->m_Core.m_fScaleZ = m_fScaleZ;
	//}
	//pApp->m_Core.ObjScale();
	//pApp->m_Core.m_QuadTree->ChangeObjectNode(pApp->m_Core.m_pSelectMapObj);

	UpdateData(FALSE);
}
void JH_ObjForm::OnBnClickedDelete()
{

	CJHToolApp* pApp = (CJHToolApp*)AfxGetApp();
	//pApp->m_Core.ObjectDelete();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void JH_ObjForm::OnBnClickedTransLation()
{
	UpdateData(TRUE);
	CJHToolApp* pApp = (CJHToolApp*)AfxGetApp();
	//if (!pApp->m_Core.m_pSelectMapObj)return;
	//pApp->m_Core.m_matMove._41 = m_fTransX;
	//pApp->m_Core.m_matMove._42 = m_fTransY;
	//pApp->m_Core.m_matMove._43 = m_fTransZ;
	//pApp->m_Core.ObjTranslation();
	//pApp->m_Core.m_QuadTree->ChangeObjectNode(pApp->m_Core.m_pSelectMapObj);

	UpdateData(FALSE);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
void JH_ObjForm::OnLbnObjSelChange()
{
	CString name;
	CString Ext;
	std::string ObjName;

	int iIndex = m_ObjectListBox.GetCurSel();
	m_ObjectListBox.GetText(iIndex, name);
	Ext = L".skn";
	m_SkinName = name + Ext;
	Ext = L".md";
	m_BoneName = name ;
	CJHToolApp* pApp = (CJHToolApp*)AfxGetApp();
	
	char buf[255] = { NULL };
	wcstombs(buf, m_BoneName.GetString(), m_BoneName.GetLength());
	pApp->m_Core.m_ObjFileName = buf;

	UpdateData(FALSE);
}

void JH_ObjForm::OnBnClickedShowinfom()
{
	CJHToolApp* pApp = (CJHToolApp*)AfxGetApp();
	//if (!pApp->m_Core.m_pSelectMapObj)return;


	//m_Obj_ID = pApp->m_Core.m_pSelectMapObj->GetID();
	//m_ObjNode = pApp->m_Core.m_pSelectMapObj->GetQuadIndex();
	//m_ObjFlag = pApp->m_Core.m_pSelectMapObj->GetFlag();

	//m_ObjPositionX = pApp->m_Core.m_pSelectMapObj->GetObj()->m_matWorld._41;
	//m_ObjPositionY = pApp->m_Core.m_pSelectMapObj->GetObj()->m_matWorld._42;
	//m_ObjPositionZ = pApp->m_Core.m_pSelectMapObj->GetObj()->m_matWorld._43;
	UpdateData(FALSE);
}
void JH_ObjForm::OnEnChangeObjflag()
{
	CJHToolApp* pApp = (CJHToolApp*)AfxGetApp();
	//if (!pApp->m_Core.m_pSelectMapObj)return;

	//UpdateData(TRUE);
	//pApp->m_Core.m_pSelectMapObj->SetFlag(m_ObjFlag);

	UpdateData(FALSE);
}
void JH_ObjForm::OnBnClickedColider()
{
	CJHToolApp* pApp = (CJHToolApp*)AfxGetApp();

	
	UpdateData(TRUE);


	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
void JH_ObjForm::OnBnClickedEdit()
{
	CJHToolApp* pApp = (CJHToolApp*)AfxGetApp();

	pApp->m_Core.m_eState = TOOLSTATE::OBJECTEDIT;
	UpdateData(TRUE);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
void JH_ObjForm::OnBnClickedCreate()
{
	CJHToolApp* pApp = (CJHToolApp*)AfxGetApp();

	pApp->m_Core.m_eState = TOOLSTATE::OBJECTNEW;
	UpdateData(TRUE);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


BEGIN_MESSAGE_MAP(JH_ObjForm, CFormView)
	ON_BN_CLICKED(IDC_BUTTON2, &JH_ObjForm::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &JH_ObjForm::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_SELECT, &JH_ObjForm::OnBnClickedObjectSelect)
	ON_BN_CLICKED(IDC_SET, &JH_ObjForm::OnBnClickedSet)
	ON_BN_CLICKED(IDC_ROTATION, &JH_ObjForm::OnBnClickedRotation)
	ON_BN_CLICKED(IDC_Move, &JH_ObjForm::OnBnClickedScale)
	ON_BN_CLICKED(IDC_Move2, &JH_ObjForm::OnBnClickedMove)
	ON_BN_CLICKED(IDC_Delete, &JH_ObjForm::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_SELECT4, &JH_ObjForm::OnBnClickedTransLation)
	ON_BN_CLICKED(IDC_BUTTON4, &JH_ObjForm::OnBnClickedBoneLoad)
	ON_LBN_SELCHANGE(IDC_LIST1, &JH_ObjForm::OnLbnObjSelChange)
	ON_BN_CLICKED(IDC_SHOWINFOM, &JH_ObjForm::OnBnClickedShowinfom)
	ON_EN_CHANGE(IDC_OBJFLAG, &JH_ObjForm::OnEnChangeObjflag)
	ON_BN_CLICKED(IDC_COLIDER, &JH_ObjForm::OnBnClickedColider)
	ON_BN_CLICKED(IDC_EDIT, &JH_ObjForm::OnBnClickedEdit)
	ON_BN_CLICKED(IDC_Create, &JH_ObjForm::OnBnClickedCreate)
END_MESSAGE_MAP()


// JH_ObjForm 메시지 처리기
#include"pch.h"



















































