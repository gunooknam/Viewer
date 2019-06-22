// FilterDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Viewer.h"
#include "FilterDlg.h"
#include "afxdialogex.h"


// CFilterDlg ��ȭ �����Դϴ�.

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


// CFilterDlg �޽��� ó�����Դϴ�.


void CFilterDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString cstrTemp;
	m_EditFilterSize.GetWindowTextA(cstrTemp);
	nFilterSize = atoi(cstrTemp);
	CDialogEx::OnOK();
}


void CFilterDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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