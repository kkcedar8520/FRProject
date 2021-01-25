#pragma once


// JH_ObjForm 대화 상자

class JH_ObjForm : public CFormView
{
	DECLARE_DYNAMIC(JH_ObjForm)
public:

	static JH_ObjForm* CreateOne(CWnd* pParent);
public:
	JH_ObjForm();   // 표준 생성자입니다.
	virtual ~JH_ObjForm();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_JH_ObjForm };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	CString m_FileName;
	afx_msg void OnBnClickedButton3();
};
