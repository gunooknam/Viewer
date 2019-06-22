#pragma once


// CRawInfoDlg ��ȭ �����Դϴ�.

class CRawInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRawInfoDlg)

public:
	CRawInfoDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRawInfoDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_radio_rawFileInfo;
	afx_msg void OnClickedRadio(UINT msg);
	afx_msg void OnBnClickedOKButton1();
	afx_msg void OnBnClickedCancelButton1();
	bool isTrue;
	int GetRawHeight();
	int GetRawWidth();
	int GetRawFormat();

private:
	int nWidth;
	int nHeight;
	int nFormat;

	CEdit m_EditHeight;
	CEdit m_EditWidth;
};
