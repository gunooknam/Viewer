#pragma once


// CImgScaleing ��ȭ �����Դϴ�.

class CImgScalingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CImgScalingDlg)


private:
		CStatic m_EditScaleRate;

		double dScaleRate;
		int nInterpolationType;

public:
	CImgScalingDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CImgScalingDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCALEDDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnRadioClicked(UINT msg);
	afx_msg void OnBnClickedOk();
	int m_radio_Interp;
	double GetScaleRate();
	int GetInterType();
};
