#pragma once


// CPSNRDlg ��ȭ �����Դϴ�.

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


	CPSNRDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CPSNRDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PSNRDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnOriImageButton();
	afx_msg void OnResImageButton();
	afx_msg void OnGetPsnrButton();
	afx_msg void OnBnClickedCancel();
};
