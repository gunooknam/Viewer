#pragma once


// COrderStatisticsDlg ��ȭ �����Դϴ�.

class COrderStatisticsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(COrderStatisticsDlg)

private:
	int m_radio_osf;

	int nFilterSize1;
	int nFilterSize2;
	int nOSFType;

	CEdit Edit_FilterSize1;
	CEdit Edit_FilterSize2;

public:
	int Getm_radio_osf() {return m_radio_osf;}
	int GetFilterSIze1();
	int GetFilterSize2();
	int GetOSFType();


public:
	COrderStatisticsDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~COrderStatisticsDlg();


// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnOkOsfButtonClicked();
	afx_msg void OnRadioClicked(UINT msg);
};
