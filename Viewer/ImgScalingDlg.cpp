// ImgScaleing.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Viewer.h"
#include "ImgScalingDlg.h"
#include "afxdialogex.h"

// CImgScaleing 대화 상자입니다.
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
	DDX_Control(pDX, IDC_EDIT_SCALERATE, m_EditScaleRate); //여기 @!
	DDX_Radio(pDX, IDC_RADIO_BILINEAR_S, m_radio_Interp);
}


BEGIN_MESSAGE_MAP(CImgScalingDlg, CDialogEx) 
	ON_BN_CLICKED(IDOK, &CImgScalingDlg::OnBnClickedOk) // 이부분
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO_BILINEAR_S, IDC_RADIO_BICUBIC_S, OnRadioClicked) //여기
END_MESSAGE_MAP()


// CImgScaleing 메시지 처리기입니다.


void CImgScalingDlg::OnBnClickedOk()
{

	CString cstrTemp;

	m_EditScaleRate.GetWindowTextA(cstrTemp);

	dScaleRate = atof(cstrTemp);

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
