// ImgScaleing.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Viewer.h"
#include "ImgScalingDlg.h"
#include "afxdialogex.h"

// CImgScaleing ��ȭ �����Դϴ�.
IMPLEMENT_DYNAMIC(CImgScalingDlg, CDialogEx)
CImgScalingDlg::CImgScalingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SCALEDDIALOG, pParent)
	, m_radio_Interp(0)
{
}

CImgScalingDlg::~CImgScalingDlg()
{
}

void CImgScalingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SCALERATE, m_EditScaleRate); //���� @!
	DDX_Radio(pDX, IDC_RADIO_BILINEAR_S, m_radio_Interp);
}


BEGIN_MESSAGE_MAP(CImgScalingDlg, CDialogEx) 
	ON_BN_CLICKED(IDOK, &CImgScalingDlg::OnBnClickedOk) // �̺κ�
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO_BILINEAR_S, IDC_RADIO_BICUBIC_S, OnRadioClicked) //����
END_MESSAGE_MAP()


// CImgScaleing �޽��� ó�����Դϴ�.


void CImgScalingDlg::OnBnClickedOk()
{

	CString cstrTemp;

	m_EditScaleRate.GetWindowTextA(cstrTemp);

	dScaleRate = atof(cstrTemp);

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnOK();
}



void CImgScalingDlg::OnRadioClicked(UINT msg) {
	UpdateData(TRUE);
	switch (m_radio_Interp) {
	case 0:
		nInterpolationType = 0;
		break;
	case 1:
		nInterpolationType = 1;
		break;
	}
}

double CImgScalingDlg::GetScaleRate() { return dScaleRate; }
int CImgScalingDlg::GetInterType() { return nInterpolationType; }
