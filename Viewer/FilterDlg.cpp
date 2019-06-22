// FilterDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Viewer.h"
#include "FilterDlg.h"
#include "afxdialogex.h"


// CFilterDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CFilterDlg, CDialogEx)

CFilterDlg::CFilterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

CFilterDlg::~CFilterDlg()
{
}

void CFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_AVERAGEFILTERRADIO, m_radio_Filtertype);
	DDX_Control(pDX, IDC_EDIT_FILTERSIZE, m_EditFilterSize);
}


BEGIN_MESSAGE_MAP(CFilterDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CFilterDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CFilterDlg::OnBnClickedCancel)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_AVERAGEFILTERRADIO, IDC_GAUSSIANFILTERRADIO, OnClickedRadio)
END_MESSAGE_MAP()


// CFilterDlg 메시지 처리기입니다.


void CFilterDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString cstrTemp;
	m_EditFilterSize.GetWindowTextA(cstrTemp);
	nFilterSize = atoi(cstrTemp);
	CDialogEx::OnOK();
}


void CFilterDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}


void CFilterDlg::OnClickedRadio(UINT msg) {
	UpdateData(TRUE);
	switch (m_radio_Filtertype)
	{
	case 0:
		nFilterType = 0;
		break;
	case 1:
		nFilterType = 1;
		break;
	case 2:
		nFilterType = 2;
		break;
	case 3:
		nFilterType = 3;
		break;
	}
}

int CFilterDlg::getFilterSize() { return nFilterSize; }
int CFilterDlg::getFilterType() { return nFilterType; }