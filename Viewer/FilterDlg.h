#pragma once


// CFilterDlg 대화 상자입니다.

class CFilterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFilterDlg)

public:
	CFilterDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CFilterDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

private :
	CStatic m_EditFilterSize;
	int nFilterSize;
	int nFilterType;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_radio_Filtertype;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnClickedRadio(UINT msg);

	int getFilterSize();
	int getFilterType();
	
};
