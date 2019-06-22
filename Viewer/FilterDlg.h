#pragma once


// CFilterDlg ��ȭ �����Դϴ�.

class CFilterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFilterDlg)

public:
	CFilterDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CFilterDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

private :
	CStatic m_EditFilterSize;
	int nFilterSize;
	int nFilterType;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_radio_Filtertype;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnClickedRadio(UINT msg);

	int getFilterSize();
	int getFilterType();
	
};
