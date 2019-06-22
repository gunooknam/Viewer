#pragma once


// CRotationDlg ��ȭ �����Դϴ�.

class CRotationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRotationDlg)


private:
	CStatic m_EditRotateAngle;

	int nAngle;
	int nInterpolationType;

public:
	CRotationDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRotationDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ROTATIONDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_radio_interp;
	afx_msg void OnBnClickedOkbutton();
	afx_msg void OnRadioClicked(UINT msg);
	int GetAngle();
	int GetInterpolationType();

};
