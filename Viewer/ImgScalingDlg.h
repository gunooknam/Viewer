#pragma once


// CImgScaleing 대화 상자입니다.

class CImgScalingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CImgScalingDlg)


private:
		CStatic m_EditScaleRate;

		double dScaleRate;
		int nInterpolationType;

public:
	CImgScalingDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CImgScalingDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCALEDDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnRadioClicked(UINT msg);
	afx_msg void OnBnClickedOk();
	int m_radio_Interp;
	double GetScaleRate();
	int GetInterType();
};
