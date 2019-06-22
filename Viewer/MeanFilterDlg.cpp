// MeanFilterDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Viewer.h"
#include "MeanFilterDlg.h"
#include "afxdialogex.h"


// CMeanFilterDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CMeanFilterDlg, CDialogEx)

CMeanFilterDlg::CMeanFilterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MEANFILTERDIALOG, pParent)
{

}

CMeanFilterDlg::~CMeanFilterDlg()
{
}

void CMeanFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_ARITHMETIC, m_radio_mf);
	DDX_Control(pDX, IDC_EDIT_MF_FILTERSIZE, Edit_FilterSize);
	DDX_Control(pDX, IDC_EDIT_Q, Edit_Q);
}


BEGIN_MESSAGE_MAP(CMeanFilterDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CMeanFilterDlg::OnOkMfButtonClicked)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO_ARITHMETIC, IDC_RADIO_CONTRA, OnRadioClicked)
END_MESSAGE_MAP()


// CMeanFilterDlg �޽��� ó�����Դϴ�.


void CMeanFilterDlg::OnOkMfButtonClicked()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strTemp1, strTemp2;

	Edit_FilterSize.GetWindowTextA(strTemp1);
	Edit_Q.GetWindowTextA(strTemp2);

	nFilterSize = atoi(strTemp1);
	Q = atoi(strTemp2);

	CDialogEx::OnOK();
}

void CMeanFilterDlg::OnRadioClicked(UINT msg){
	UpdateData(TRUE);

	switch (m_radio_mf) {
	case 0:
		nMeanFilterType = 0;
		break;
	case 1:
		nMeanFilterType = 1;
		break;
	case 2:
		nMeanFilterType = 2;
		break;
	case 3:
		nMeanFilterType = 3;
		break;
	}
}

int CMeanFilterDlg::GetFilterSize() {
	return nFilterSize;
}
int CMeanFilterDlg::GetMeanFilterType() {
	return nMeanFilterType;
}
int CMeanFilterDlg::GetQ() {
	return Q;
}

