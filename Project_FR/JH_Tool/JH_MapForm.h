#pragma once


// JH_MapForm 대화 상자

class JH_MapForm : public CFormView
{
	DECLARE_DYNAMIC(JH_MapForm)

public:
	JH_MapForm();   // 표준 생성자입니다.
	virtual ~JH_MapForm();

	static JH_MapForm* CreateOne(CWnd* pParent);
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_JH_MapForm };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	int m_iWidth;
	int m_iHeight;
	int m_iCellCount;
	int m_iCellSize;
	virtual void OnInitialUpdate();
	afx_msg void OnEnChangeEdit5();
	CString m_TextrueName;
	afx_msg void OnBnClickedOk2();
	CString m_NormalMapFile;
	afx_msg void OnEnChangeEdit7();
	afx_msg void OnBnClickedOk4();
	CString m_Brush;
	afx_msg void OnBnClickedOk5();
};
