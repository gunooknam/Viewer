// PSNRDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Viewer.h"
#include "PSNRDlg.h"
#include "afxdialogex.h"
#include "RawInfoDlg.h"
#include "VIewerDlg.h"

// CPSNRDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CPSNRDlg, CDialogEx)

CPSNRDlg::CPSNRDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PSNRDIALOG, pParent)
{

}

CPSNRDlg::~CPSNRDlg()
{
}

void CPSNRDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ORIFILENAME, Edit_File_Ori);
	DDX_Control(pDX, IDC_EDIT_NOISEFILENAME, Edit_File_Dst);
	DDX_Control(pDX, IDC_EDIT_PSNR, Edit_PSNR);

}
BEGIN_MESSAGE_MAP(CPSNRDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CPSNRDlg::OnOriImageButton)
	ON_BN_CLICKED(IDC_BUTTON2, &CPSNRDlg::OnResImageButton)
	ON_BN_CLICKED(IDC_BUTTON3, &CPSNRDlg::OnGetPsnrButton)
	ON_BN_CLICKED(IDCANCEL, &CPSNRDlg::OnBnClickedCancel)
END_MESSAGE_MAP()
// CPSNRDlg �޽��� ó�����Դϴ�.


double CPSNRDlg::GetPSNR(unsigned char** Ori, unsigned char **Dst, int nHeight, int nWidth) {

	double sum=0;
	for (int h = 0; h < nHeight; h++) {
		for (int w = 0; w < nWidth; w++) {
			sum += pow(Ori[h][w] - Dst[h][w] ,2 );
		}
	}
	double MSE = sum / (nHeight*nWidth);
	return  20 * log10( 255 / sqrt( MSE ) ) ;
}


void CPSNRDlg::OnOriImageButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CFileDialog dlg(TRUE);
	CRawInfoDlg RawDlg;

	if (Ori != NULL) {
		MemFree2D(Ori, nHeight_Ori);
	}
	if (dlg.DoModal() == IDOK) {
		if (dlg.GetFileExt() != "raw" && dlg.GetFileExt() != "RAW") {
			MessageBox("���� Ȯ���ڰ� raw ������ �ƴմϴ�. ");
			return;
		}
		FILE * fp;
		fopen_s(&fp, dlg.GetPathName(), "rb");
		if (RawDlg.DoModal() == IDOK) {

			nHeight_Ori = RawDlg.GetRawHeight();
			nWidth_Ori = RawDlg.GetRawWidth();

			if (nHeight_Ori == 0 || nWidth_Ori == 0 || RawDlg.GetRawFormat() != 3) {
				MessageBox(" �Է� ���� �߸��Ǿ����ϴ�. ");
				return;
			}

			Edit_File_Ori.SetWindowTextA(dlg.GetFileTitle());
			Ori = MemAlloc2D(nHeight_Ori, nWidth_Ori, 0);
			CString a = dlg.GetFileName();

			for (int h = 0; h < nHeight_Ori; h++) {
				fread(Ori[h], sizeof(unsigned char), nWidth_Ori, fp);
			}
		}
		fclose(fp);
	}
}


void CPSNRDlg::OnResImageButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CFileDialog dlg(TRUE);
	CRawInfoDlg RawDlg;

	if (Dst != NULL) {
		MemFree2D(Dst, nHeight_Dst);
	}

	if (dlg.DoModal() == IDOK) {
		if (dlg.GetFileExt() != "raw" && dlg.GetFileExt() != "RAW") {
			MessageBox("���� Ȯ���ڰ� raw ������ �ƴմϴ�.");
			return;
		}
		FILE * fp;
		fopen_s(&fp, dlg.GetPathName(), "rb");
		if (RawDlg.DoModal() == IDOK) {
			nHeight_Dst = RawDlg.GetRawHeight();
			nWidth_Dst = RawDlg.GetRawWidth();
			if (nHeight_Dst == 0 || nWidth_Dst == 0 || RawDlg.GetRawFormat() != 3) {
				MessageBox("�Է� ���� �߸��Ǿ����ϴ�.");
				return;
			}

			Edit_File_Dst.SetWindowTextA(dlg.GetFileTitle());
			Dst = MemAlloc2D(nHeight_Ori, nWidth_Ori, 0);

			for (int h = 0; h < nHeight_Dst; h++) {
				fread(Dst[h], sizeof(unsigned char), nWidth_Dst, fp);
			}
		}
		fclose(fp);
	}
}


void CPSNRDlg::OnGetPsnrButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (Ori == NULL || Dst == NULL) {
		MessageBox("���� ����� �� ������ �ҷ����� �ʾҽ��ϴ�.");
		return;
	}

	if (nHeight_Ori != nHeight_Dst || nWidth_Ori != nWidth_Dst) {
		MessageBox("���� ����� �� ������ ũ�Ⱑ �ٸ��ϴ�.");
		return;
	}

	CString strTemp;
	double dPSNR = GetPSNR(Ori, Dst, nHeight_Ori, nWidth_Ori);

	strTemp.Format(_T("%f"), dPSNR);
	Edit_PSNR.SetWindowTextA(strTemp);
}


void CPSNRDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (Ori != NULL) {
		MemFree2D(Ori, nHeight_Ori);
	}
	if (Dst != NULL) {
		MemFree2D(Dst, nWidth_Dst);
	}

	CDialog::OnCancel();
}
