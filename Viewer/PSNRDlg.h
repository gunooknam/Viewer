#pragma once


// CPSNRDlg 대화 상자입니다.

class CPSNRDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPSNRDlg)


private:
	unsigned char** Ori, **Dst;

	int nHeight_Ori, nWidth_Ori;
	int nHeight_Dst, nWidth_Dst;

	CEdit Edit_File_Ori, Edit_File_Dst, Edit_PSNR;
	double GetPSNR(unsigned char** Ori, unsigned char **Dst, int nHeight, int nWidth);

public:
	afx_msg void OnOriopenButtonClicked();
	afx_msg void OnNoiseopenButtonClicked();
	afx_msg void OnGetpsnrButtonClicked();
	afx_msg void OnBnClickedButtonClose();


	CPSNRDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CPSNRDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PSNRDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnOriImageButton();
	afx_msg void OnResImageButton();
	afx_msg void OnGetPsnrButton();
	afx_msg void OnBnClickedCancel();
};
