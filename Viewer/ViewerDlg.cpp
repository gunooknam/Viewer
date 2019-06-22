
// ViewerDlg.cpp : ���� ����
//
#include "stdafx.h"
#include "Viewer.h"
#include "ViewerDlg.h"
#include "afxdialogex.h"
#include "PSNRDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CViewerDlg ��ȭ ����



CViewerDlg::CViewerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_VIEWER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CViewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICTURE_IN, m_PicOri);
	DDX_Control(pDX, IDC_PICTURE_OUT, m_PicProc);
}

BEGIN_MESSAGE_MAP(CViewerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_FILE_FILEOPEN, &CViewerDlg::OnFileOpenMenuBtnClick)
	ON_COMMAND(ID_FILE_FILECLOSE, &CViewerDlg::OnCloseMenuClick)
	ON_COMMAND(ID_EDIT_CONVERT, &CViewerDlg::OnConvertgrayBtnClick)
	ON_COMMAND(ID_EDIT_SCALING, &CViewerDlg::OnEditScalingClick)
	ON_COMMAND(ID_EDIT_ROTATION, &CViewerDlg::OnEditRotationClick)
	ON_COMMAND(ID_HISTOGRAM_GETHISTOGRAM, &CViewerDlg::OnHistogramGetClick)
	ON_COMMAND(ID_HISTOGRAM_HISTOGRAM, &CViewerDlg::OnHistogramEqualizationClicked)
	ON_COMMAND(ID_HISTOGRAM_HISTOGRAM32779, &CViewerDlg::OnHistogramMatchingClicked)
	ON_COMMAND(ID_EDIT_FILTER, &CViewerDlg::OnEditFilter)
	ON_COMMAND(ID_NOISEREDUCTION_ADDNOISE, &CViewerDlg::OnNoisereductionAddnoiseClicked)
	ON_COMMAND(ID_NOISEFILTERING_ORDER, &CViewerDlg::OnNoisefilteringOrderStatisticClicked)
	ON_COMMAND(ID_NOISEFILTERING_MEANFILTER, &CViewerDlg::OnNoisefilteringMeanfilterClicked)
	ON_COMMAND(ID_NOISEREDUCTION_GETPSNR, &CViewerDlg::OnGetPSNRClicked)
END_MESSAGE_MAP()


// CViewerDlg �޽��� ó����

BOOL CViewerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CViewerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CViewerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CViewerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CViewerDlg::DisplayImage(Mat DispMat, bool bInOut) {
	if (bInOut) {
		GetDlgItem(IDC_PICTURE_IN)->GetWindowRect(rect);
		ScreenToClient(rect);
		m_pDC = m_PicOri.GetDC();
		m_PicOri.GetClientRect(&rect);
	}
	else {
		GetDlgItem(IDC_PICTURE_OUT)->GetWindowRect(rect);
		ScreenToClient(rect);
		m_pDC = m_PicProc.GetDC();
		m_PicProc.GetClientRect(&rect);
	}
	IplImage*Ori = &IplImage(DispMat);
	IplImage*Resize = NULL;
	ResizeImage(Ori, &Resize, &rect);
	DisplayBitmap(m_pDC, rect, Resize);
}
void CViewerDlg::DisplayBitmap(CDC *pDC, CRect rect, IplImage* DisplpIImage) {
	BITMAPINFO bitmapInfo;
	bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapInfo.bmiHeader.biPlanes = 1;
	bitmapInfo.bmiHeader.biCompression = BI_RGB;
	bitmapInfo.bmiHeader.biXPelsPerMeter = 100;
	bitmapInfo.bmiHeader.biYPelsPerMeter = 100;
	bitmapInfo.bmiHeader.biClrUsed = 0;
	bitmapInfo.bmiHeader.biClrImportant = 0;
	bitmapInfo.bmiHeader.biSizeImage = 0;
	bitmapInfo.bmiHeader.biWidth = DisplpIImage->width;
	bitmapInfo.bmiHeader.biHeight = DisplpIImage->height;


	if (DisplpIImage->nChannels == 3) {
		IplImage*ReverseImg = cvCreateImage(CvSize(DisplpIImage->width, DisplpIImage->height), 8, 3);

		for (int h = 0; h < DisplpIImage->height; h++) {
			for (int w = 0; w < DisplpIImage->width; w++) {
				ReverseImg->imageData[h*DisplpIImage->widthStep + w * 3] = DisplpIImage->imageData[(DisplpIImage->height - h -1)*DisplpIImage->widthStep + w * 3];
				ReverseImg->imageData[h*DisplpIImage->widthStep + w * 3 + 1] = DisplpIImage->imageData[(DisplpIImage->height - h -1)*DisplpIImage->widthStep + w * 3 + 1];
				ReverseImg->imageData[h*DisplpIImage->widthStep + w * 3 + 2] = DisplpIImage->imageData[(DisplpIImage->height - h -1)*DisplpIImage->widthStep + w * 3 + 2];
			}
		}
		bitmapInfo.bmiHeader.biBitCount = DisplpIImage->depth * DisplpIImage->nChannels;
		pDC->SetStretchBltMode(COLORONCOLOR);
		::StretchDIBits(pDC->GetSafeHdc(), rect.left, rect.top, rect.right, rect.bottom, 0, 0, DisplpIImage->width, DisplpIImage->height, ReverseImg->imageData, &bitmapInfo,
			DIB_RGB_COLORS, SRCCOPY);
		cvReleaseImage(&ReverseImg);
	
	}
	else {
		IplImage* ReverseImg = cvCreateImage(cvGetSize(DisplpIImage), DisplpIImage->depth, 1);

		for (int h = 0; h < DisplpIImage->height; h++) {
			for (int w = 0; w < DisplpIImage->width; w++) {
				ReverseImg->imageData[h*DisplpIImage->widthStep + w] = DisplpIImage->imageData[(DisplpIImage->height - h)*DisplpIImage->widthStep + w];
			}
		}

		IplImage * tmp = cvCreateImage(cvGetSize(DisplpIImage), DisplpIImage->depth, 3);
		cvCvtColor(ReverseImg, tmp, CV_GRAY2BGR);

	    bitmapInfo.bmiHeader.biBitCount = tmp->depth * tmp->nChannels;
		pDC->SetStretchBltMode(COLORONCOLOR);
		::StretchDIBits(pDC->GetSafeHdc(), rect.left, rect.top, rect.right, rect.bottom,
			0, 0, tmp->width, tmp->height, tmp->imageData, &bitmapInfo,
			DIB_RGB_COLORS, SRCCOPY);

		cvReleaseImage(&ReverseImg);
		cvReleaseImage(&tmp);
	}
}
void CViewerDlg::ResizeImage(IplImage*src, IplImage ** dst, CRect * rect) {
	int ndst_width = 0, ndst_height = 0;

	if (src->width > src->height) {
		ndst_width = rect->Width();
		ndst_height = (src->height * rect->Width()) / src->width;
	}
	else {
		ndst_width = (src->width * rect->Height()) / src->height;
		ndst_height = rect->Height();
	}
	(*dst) = cvCreateImage(cvSize(ndst_width, ndst_height), IPL_DEPTH_8U, src->nChannels);

	cvResize(src, (*dst));
	rect->right = rect->left + ndst_width;
	rect->bottom = rect->top + ndst_height;
}

float** MemAlloc2Df(int nHeight, int nWidth, int nInitVal) {
	float** rtn = new float*[nHeight];
	for (int n = 0; n < nHeight; n++) {
		rtn[n] = new float[nWidth];
		memset(rtn[n], nInitVal, sizeof(float) * nWidth);
	}
	return rtn;
}

void MemFree2Df(float ** Mem, int nHeight) {
	for (int n = 0; n < nHeight; n++) {
		delete[] Mem[n];
	}
	delete[] Mem;
}

unsigned char ** MemAlloc2D(int nHeight, int nWidth, unsigned char nInitVal) {

	unsigned char** rtn = new unsigned char*[nHeight];
	for (int n = 0; n < nHeight; n++) {
		rtn[n] = new unsigned char[nWidth];
		memset(rtn[n], nInitVal, sizeof(unsigned char) * nWidth);
	}
	return rtn;
}
void MemFree2D(unsigned char** Mem, int nHeight) {
	for (int n = 0; n < nHeight; n++) {
		delete[] Mem[n];
	}
	delete[] Mem;
}

void CViewerDlg::OnFileOpenMenuBtnClick()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CFileDialog dlg(TRUE);

	if (isImageOpened)
	{

		if (ch_in_1 != NULL) 
		{
			MemFree2D(ch_in_1, nHeight_in);
		}
		if (ch_in_2 != NULL)
		{
			if (nFormat == FORMAT_YUV444) 
			{
				MemFree2D(ch_in_2, nHeight_in / 2);
			}
			else MemFree2D(ch_in_2, nHeight_in);
		}
		if (ch_in_3 != NULL)
		{
			if (nFormat == FORMAT_YUV420) {
				MemFree2D(ch_in_3, nHeight_in / 2);
			}
			else MemFree2D(ch_in_3, nHeight_in);
		}
		if (ch_in_gray != NULL)
		{
			MemFree2D(ch_in_gray, nHeight_in);
		}
	}
	if (dlg.DoModal() == IDOK)
	{
	
		if (dlg.GetFileExt() != "jpg" && dlg.GetFileExt() != "JPG" && dlg.GetFileExt() != "raw" && dlg.GetFileExt() != "yuv") {
			MessageBox("JPG �Ǵ� YUV, Gray ������ �ƴմϴ�.");
			return;
		}
		InpFileName = dlg.GetFileTitle();

		if (dlg.GetFileExt() == "jpg" || dlg.GetFileExt() == "JPG") 
		{
			Ori_Img = imread((const char*)dlg.GetPathName());
			nHeight_in = Ori_Img.rows;
			nWidth_in = Ori_Img.cols;
			if (Ori_Img.channels() == 3) 
			{
				ch_in_1 = MemAlloc2D(nHeight_in, nWidth_in, 0);
				ch_in_2 = MemAlloc2D(nHeight_in, nWidth_in, 0);
				ch_in_3 = MemAlloc2D(nHeight_in, nWidth_in, 0);
				for (int h = 0; h < nHeight_in; h++) 
				{
					for (int w = 0; w < nWidth_in; w++) 
					{
						Vec3b RGB = Ori_Img.at<Vec3b>(h, w);
						ch_in_1[h][w] = RGB[2];
						ch_in_2[h][w] = RGB[1];
						ch_in_3[h][w] = RGB[0];
					}
				}
				nFormat = FORMAT_RGB;
			}
			else { // Gray Image (JPG)

				ch_in_gray = MemAlloc2D(nHeight_in, nWidth_in, 0);
				for (int h = 0; h < nHeight_in; h++) {
					for (int w = 0; w < nWidth_in; w++) {
						ch_in_gray[h][w] = Ori_Img.at<unsigned char>(h, w);
					}
				}
				nFormat = FORMAT_GRAY; 
			}
			isImageOpened = true;
			DisplayImage(Ori_Img, true); //Į��� ���
		}
		else { //Raw File & YUV File
				CRawInfoDlg RawInfoDlg;
				if (RawInfoDlg.DoModal() == IDOK) 
				{
					nHeight_in = RawInfoDlg.GetRawHeight();
					nWidth_in = RawInfoDlg.GetRawWidth();
					nFormat = RawInfoDlg.GetRawFormat();

					if (nHeight_in == 0 || nWidth_in == 0) {
						MessageBox("���� �߸� �Է��Ͽ����ϴ�.");
						return;
					}
					FILE * fp_in;
					fopen_s(&fp_in, (const char*)dlg.GetPathName(), "rb");

					if (nFormat == FORMAT_GRAY) {
						ch_in_gray = MemAlloc2D(nHeight_in, nWidth_in, 0);

						for (int h = 0; h < nHeight_in; h++) {
							fread(ch_in_gray[h], sizeof(unsigned char), nWidth_in, fp_in);
						}

						Ori_Img = Mat(nHeight_in, nWidth_in, CV_8UC1);
						for (int h = 0; h < nHeight_in; h++) {
							for (int w = 0; w < nWidth_in; w++)
							{
								Ori_Img.at<unsigned char>(h, w) = ch_in_gray[h][w];
							}
						}

						//DisplayImage(Ori_Img, true);
					}
					else if (nFormat == FORMAT_YUV444) {
						ch_in_1 = MemAlloc2D(nHeight_in, nWidth_in, 0);
						ch_in_2 = MemAlloc2D(nHeight_in, nWidth_in, 0);
						ch_in_3 = MemAlloc2D(nHeight_in, nWidth_in, 0);
						for (int h = 0; h < nHeight_in; h++) {
							fread(ch_in_1[h], sizeof(unsigned char), nWidth_in, fp_in);
						}

						for (int h = 0; h < nHeight_in; h++) {
							fread(ch_in_2[h], sizeof(unsigned char), nWidth_in, fp_in);
						}
						for (int h = 0; h < nHeight_in; h++) {
							fread(ch_in_3[h], sizeof(unsigned char), nWidth_in, fp_in);
						}

						Ori_Img = Mat(nHeight_in, nWidth_in, CV_8UC3);
						for (int h = 0; h < nHeight_in; h++) {
							for (int w = 0; w < nWidth_in; w++) {
								Ori_Img.at<Vec3b>(h, w)[2] = ch_in_1[h][w] + 1.402*(ch_in_3[h][w] - 128);
								Ori_Img.at<Vec3b>(h, w)[1] = ch_in_1[h][w] - 0.344*(ch_in_2[h][w] - 128) - 0.714 * (ch_in_3[h][w] - 128);
								Ori_Img.at<Vec3b>(h, w)[0] = ch_in_1[h][w] + 1.772*(ch_in_2[h][w] - 128);
							}
						}
						//DisplayImage(Ori_Img, true);
					}
					else { //nFormat == FORMAT_YUV420
						ch_in_1 = MemAlloc2D(nHeight_in, nWidth_in, 0);
						ch_in_2 = MemAlloc2D(nHeight_in / 2, nWidth_in / 2, 0);
						ch_in_3 = MemAlloc2D(nHeight_in / 2, nWidth_in / 2, 0);
					
						for (int h = 0; h < nHeight_in; h++) {
							fread(ch_in_1[h], sizeof(unsigned char), nWidth_in, fp_in); // ���� ��������
						}
						for (int h = 0; h < nHeight_in / 2; h++) {
							fread(ch_in_2[h], sizeof(unsigned char), nWidth_in / 2, fp_in);
						}
						for (int h = 0; h < nHeight_in / 2; h++) {
							fread(ch_in_3[h], sizeof(unsigned char), nWidth_in / 2, fp_in);
						}

						Ori_Img = Mat(nHeight_in, nWidth_in, CV_8UC3);
						for (int h = 0; h < nHeight_in; h++) {
							for (int w = 0; w < nWidth_in; w++) {
								Ori_Img.at<Vec3b>(h, w)[2] = ch_in_1[h][w] + 1.402*(ch_in_3[h / 2][w / 2] - 128);
								Ori_Img.at<Vec3b>(h, w)[1] = ch_in_1[h][w] - 0.344* (ch_in_2[h / 2][w / 2] - 128) - 0.714 * (ch_in_3[h / 2][w / 2] - 128);
								Ori_Img.at<Vec3b>(h, w)[0] = ch_in_1[h][w] + 1.772* (ch_in_2[h /2][w / 2] - 128);
							}
						}
					}
					fclose(fp_in);
					isImageOpened = true;
					DisplayImage(Ori_Img, true);
			}
		}
	}
}

void CViewerDlg::OnCloseMenuClick(){
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (isImageOpened) {
		if (ch_in_1 != NULL) {
			MemFree2D(ch_in_1, nHeight_in);
		}
		if (ch_in_2 != NULL) {
			if (nFormat == FORMAT_YUV444) {
				MemFree2D(ch_in_2, nHeight_in / 2);
			}
			else MemFree2D(ch_in_2, nHeight_in);
		}
		if (ch_in_3 != NULL) {
			if (nFormat == FORMAT_YUV420) {
				MemFree2D(ch_in_3, nHeight_in / 2);
			}
			else MemFree2D(ch_in_3, nHeight_in);
		}
		if (ch_in_gray != NULL) {
			MemFree2D(ch_in_gray, nHeight_in);
		}
	}
	::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);
}


void CViewerDlg::OnConvertgrayBtnClick()
{
	if (isImageOpened) {

		if (nFormat == FORMAT_GRAY) 
		{
			MessageBox("�Է� ������ ȸ���� �����Դϴ�.");
			return;
		}
		if (nFormat == FORMAT_YUV444 || nFormat == FORMAT_YUV420) {
			Proc_Img = Mat(nHeight_in, nWidth_in, CV_8UC1);
			for (int h = 0; h < nHeight_in; h++) {
				for (int w = 0; w < nWidth_in; w++) {
					Proc_Img.at<unsigned char>(h, w) = ch_in_1[h][w]; // 1ä�η� �ٲ��ش�. �װ��� ���÷���
				}
			}
			DisplayImage(Proc_Img, false);
			return;
		}
		if (nFormat == FORMAT_RGB) {
			if (ch_in_gray == NULL) {
				ch_in_gray = MemAlloc2D(nHeight_in, nWidth_in, 0);
			}

			for (int h = 0; h < nHeight_in; h++) {
				for (int w = 0; w < nWidth_in; w++) {
					ch_in_gray[h][w] = saturate_cast<unsigned char>(0.299 * ch_in_1[h][w] + 0.587*ch_in_2[h][w] + 0.114*ch_in_3[h][w]);
				}
			}
			Proc_Img = Mat(nHeight_in, nWidth_in, CV_8UC1);
			for (int h = 0; h < nHeight_in; h++) {
				for (int w = 0; w < nWidth_in; w++) {
					Proc_Img.at<unsigned char>(h, w) = ch_in_gray[h][w];
				}
			}
			DisplayImage(Proc_Img, false);
			return;
		  }
		}
		else
		{
			MessageBox("�ҷ��� ������ �����ϴ�.");
		}
}


bool CViewerDlg::isInsideBoundary(int nHeight, int nWidth, double h, double w) {
	if (h >= 0 && w >= 0 && h < nHeight && w < nWidth) {
		return true;
	}
	else return false;
}
unsigned char CViewerDlg::BilinearInterpolation(unsigned char**In, int nHeight_Ori, int nWidth_Ori, double h_Cvt, double w_Cvt) {

	//nHeight_Ori ��� ���� �̹����� ����
	//nWidth_Ori ��� ���� �̹����� ����
		unsigned char p1, p2, p3, p4;
		int h1, w1, h2, w2, h3, w3, h4, w4;
		h1 = static_cast<int>(h_Cvt);
		w1 = static_cast<int>(w_Cvt);
		h2 = h1; 
		w2 = w1 + 1;
		h3 = h1 + 1;
		w3 = w1;
		h4 = h3;
		w4 = w2;
	   //�ϴ� ������ �ִ��� ������ ���� ��Ƽ� ������ ��
       //h1,w1=p1          h2,w2=p2
		 ////////////////////
		 //                //
		 //                //
		 //                //
		 //                //
		 ////////////////////
	   //h3,w3=p3         h4,w4=p4
		if (h1 == nHeight_Ori - 1 && w1 == nWidth_Ori - 1) {
			return In[h1][w1];
		}
		else if (h1 == nHeight_Ori - 1 && w1 != nWidth_Ori - 1) {
			p1 = In[h1][w1];
			p2 = In[h2][w2];
			return  (w2 - w_Cvt)*p1 + (w_Cvt - w1)*p2;
		}
		else if (h1 != nHeight_Ori - 1 && w1 == nWidth_Ori - 1) {
			p1 = In[h1][w1];
			p3 = In[h3][w3];
			return (h3 - h_Cvt)*p1 + (h_Cvt - h1)*p3;
		}
		//////////////// ��������� �����ڸ� ó��
		else{
		// ��ʽ�����
			p1 = In[h1][w1];
			p2 = In[h2][w2];
			p3 = In[h3][w3];
			p4 = In[h4][w4];
			return  ( h3-h_Cvt )*((w2 - w_Cvt)*p1 + (w_Cvt - w1)*p2) + (h_Cvt-h1)*((w2 - w_Cvt)*p3 + (w_Cvt - w1)*p4);                                                                                                           
		}
}


unsigned char CViewerDlg::BicubicInterpolation(unsigned char** In, int nHeight_Ori, int nWidth_Ori, double h_Cvt, double w_Cvt) {
	//f(x) ax^3 +bx^2 +cx +d
	//f(-1) = -a+ b-c +d
	//f(0)=d
	//f(1)=a+b+c+d
	//f(2)=8a+4b+2c+d
	// [ f(-1),  = [ -1 1 -1 1   [ a
	//   f(0),        0 0 0 1      b
	//   f(1),        1 1 1 1      c
	//   f(2) ]       8 4 2 1 ]    d ]
	// f(n) = an^3+bn^2+cn+d
	// [ a,     [                [ f(-1),
	//   b,  =       �����        f(0),
	//   c,						   f(1),
	//   d ]                  ]    f(2) ]
	// f(n) = [n^3 n^2 n^ 1][ a
	//                        b
	//                        c
	//                        d ]
	int h1 = static_cast<int>(h_Cvt);
	int w1 = static_cast<int>(w_Cvt);
	if (h1 == 0)
		return In[h1][w1]; //�����ڸ� �е�
	else if (w1 == 0)
		return In[h1][w1];
	else if (w1 > nWidth_Ori - 3)
		return In[h1][nWidth_Ori-1]; //�����ڸ� �е�
	else if (h1 > nHeight_Ori - 3)
		return In[nHeight_Ori-1][w1];  //�����ڸ� �е�
	else
	{
		double n_w = w_Cvt - w1;  // �� �κ��� �����̴�. �������� ����
		double n_h = h_Cvt - h1;  //  �������� ����

		//a =  { {-1, 1,-1, 1},
		//	     { 0, 0, 0, 1},
		//	     { 1 ,1, 1, 1},
		//	     { 8, 4, 2, 1} };
		//>>> b= np.linalg.inv(a)  //python numpy ���� ���
		//>>> b
		//array([[ -1.66666667e-01,   5.00000000e-01,  -5.00000000e-01,
		//          1.66666667e-01],
		//       [  5.00000000e-01,  -1.00000000e+00,   5.00000000e-01,
		//          4.62592927e-18],
		//       [ -3.33333333e-01,  -5.00000000e-01,   1.00000000e+00,
		//         -1.66666667e-01],
		//       [  0.00000000e+00,   1.00000000e+00,   0.00000000e+00,
		//          0.00000000e+00]])
		double reverse_matrix[4][4] =  {{ -0.166666667,  0.5, -0.5,  0.166666667 },
										{		   0.5,   -1,  0.5,        0     },
										{ -0.333333333, -0.5,    1, -0.166666667 },
										{		   0,    1  ,    0,          0   }};
		double invmulrow[4];
		double rowvalue[4];
		double colvalue[4];
		//   ��   ��   ��   ��
		//  
		//   ��   ��   ��   ��
		//           �������̸� �����ϰ� �� -1 �ؼ� �� ó�� index�� �̵�
		//   ��   ��   ��   ��
		//
		//   ��   ��   ��   ��
		for (int i = 0; i < 4; i++)  // 4���� ����
		{
			for (int j = 0; j < 4; j++)
			{
				invmulrow[j] = reverse_matrix[j][0] * In[(h1 - 1) + i][w1 - 1] + reverse_matrix[j][1] * In[(h1 - 1) + i][w1] + reverse_matrix[j][2] * In[(h1 - 1) + i][w1 + 1] + reverse_matrix[j][3] * In[(h1 - 1) + i][w1 + 2];
			}
			rowvalue[i] = n_w*n_w*n_w*invmulrow[0] + n_w*n_w*invmulrow[1] + n_w*invmulrow[2] + invmulrow[3];
		}
		for (int i = 0; i < 4; i++) {

			colvalue[i] = reverse_matrix[i][0] * rowvalue[0] + reverse_matrix[i][1] * rowvalue[1] + reverse_matrix[i][2]*rowvalue[2] + reverse_matrix[i][3]*rowvalue[3];
		}

		
		double temp = (n_h*n_h*n_h*colvalue[0] + n_h*n_h*colvalue[1] + n_h*colvalue[2] + colvalue[3]);
		// ���� Ŭ�����̾���. Ŭ������ ���ϸ� -���� 255������ �ٴ� ��찡 �ִ�.
		// -������ unsigned char�� �ٲ�� ���� ���� 255�� �ڴ�.
		
		// 0 ~ 255���� Ŭ����
		return saturate_cast<unsigned char>(temp);
	}

} //Bicubic �� ���� �̻���

void CViewerDlg::OnEditScalingClick()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (isImageOpened && nFormat == FORMAT_GRAY) {
		if (ImgScalingDlg.DoModal() == IDOK) {
			int nInterpolationType = ImgScalingDlg.GetInterType();
			double dScaleRate = ImgScalingDlg.GetScaleRate();
			if (dScaleRate < 1 || dScaleRate > 2) {
				MessageBox("�����ϸ� ������ �߸��Ǿ����ϴ�.");
				return;
			}
			int nHeight_Scale = nHeight_in * dScaleRate; // scaleRate�� ����     4�� 6��
			int nWidth_Scale = nWidth_in * dScaleRate;  // scaleRate�� ���� 

			unsigned char ** Out = MemAlloc2D(nHeight_Scale, nWidth_Scale,0); //Ȯ��� �̹����� 0���� �� ä��

			for (int h = 0; h < nHeight_Scale; h++) {
				for (int w = 0; w < nWidth_Scale; w++) {
					double h_Ori = h / dScaleRate;
					double w_Ori = w / dScaleRate;
					if (nInterpolationType == BILINEAR) {
						Out[h][w] = BilinearInterpolation(ch_in_gray, nHeight_in, nWidth_in, h_Ori, w_Ori);
					}
					else {
						Out[h][w] = BicubicInterpolation(ch_in_gray, nHeight_in, nWidth_in, h_Ori, w_Ori);
					}
				}
			}
			Ori_Img = Mat(nHeight_in, nWidth_in, CV_8UC1); // C�� 1ä�� �ε�
			Proc_Img = Mat(nHeight_Scale, nWidth_Scale, CV_8UC1);

			for (int h = 0; h < nHeight_in; h++) {
				for (int w = 0; w < nWidth_in; w++) {
					Ori_Img.at<unsigned char>(h, w) = ch_in_gray[h][w];
				}
			}
			for (int h = 0; h < nHeight_Scale; h++) {
				for (int w = 0; w < nWidth_Scale; w++) {
					Proc_Img.at<unsigned char>(h, w) = Out[h][w];
				}
			}
			imshow("Original Image", Ori_Img);
			imshow("Scaled Image", Proc_Img);
			waitKey(0);
			}
		}
	else 
	{
		MessageBox("�ҷ��� ������ ���ų� ���� ������ ȸ���� ������ �ƴմϴ�.");
	}
}


void CViewerDlg::OnEditRotationClick()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (isImageOpened && nFormat == FORMAT_GRAY) {
		if (RotationDlg.DoModal() == IDOK) {
			int nInterpolationType = RotationDlg.GetInterpolationType();
			int nAngle = RotationDlg.GetAngle();

			if (nAngle < 0 || nAngle > 360) { 
				MessageBox("ȸ�� ������ �߸��Ǿ����ϴ�.");
				return;
			}
			unsigned char ** Out = MemAlloc2D(nHeight_in, nWidth_in, 0);
			int nHeight_2 = nHeight_in / 2;
			int nWidth_2 = nWidth_in / 2;

			double h_Rotate = 0;
			double w_Rotate = 0;
			/*
			double sin_value = (double)sin(nAngle * (PI / 180.0));
			double cos_value = (double)cos(nAngle * (PI / 180.0));
			*/

			for (int h = 0; h < nHeight_in; h++) {
				for (int w = 0; w < nWidth_in; w++) {

					// ȸ���� ��ǥ �� ���
					// double h_Rotate = ???
					// double w_Rotate = ???

					int rot_h = h - nHeight_2; // �߽��� 0���� �̵���Ų��.
					int rot_w = w - nWidth_2;  // �߽��� 0���� �̵���Ų��.

					w_Rotate = cos(nAngle * (PI / 180.0))*rot_w - sin(nAngle * (PI / 180.0))*rot_h + nWidth_2; // �׸��� �ٽ� �����ֱ�
					h_Rotate = sin(nAngle * (PI / 180.0))*rot_w + cos(nAngle * (PI / 180.0))*rot_h + nHeight_2; // �׸��� �ٽ� �����ֱ�

					if (isInsideBoundary(nHeight_in, nWidth_in, h_Rotate, w_Rotate)) {
						if (nInterpolationType == BILINEAR) {
							Out[h][w] = BilinearInterpolation(ch_in_gray, nHeight_in, nWidth_in, h_Rotate, w_Rotate);
						}
						else {
							Out[h][w] = BicubicInterpolation(ch_in_gray, nHeight_in, nWidth_in,h_Rotate, w_Rotate);
						}
					}

				}
			}
			Proc_Img = Mat(nHeight_in, nWidth_in, CV_8UC1);
			for (int h = 0; h < nHeight_in; h++) {
				for (int w = 0; w < nWidth_in; w++) {
					Proc_Img.at<unsigned char>(h, w) = Out[h][w];
				}
			}
			DisplayImage(Proc_Img,false);
			MemFree2D(Out, nHeight_in);

		}
	}
	else {
		MessageBox("�ҷ��� ������ ���ų� ���� ������ ȸ���� ������ �ƴմϴ�.");
	}
}



void CViewerDlg::OnHistogramGetClick()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (isImageOpened && nFormat == FORMAT_GRAY) {
		if (Hist == NULL) {
			Hist = new int[256];
		}
		memset(Hist, 0, sizeof(int) * 256);

		for (int h = 0; h < nHeight_in; h++) {
			for (int w = 0; w < nWidth_in; w++) {
				Hist[ch_in_gray[h][w]]++;
			}
		}
	    //�븻�������Ѵ� ������׷��̶� ���÷���
		int nMax = 0;

		for (int n = 0; n < 256; n++) {
			if (nMax < Hist[n]) {
				nMax = Hist[n];
			}
		}
		double dNormalizeFactor = 255.0 / nMax;

		Mat HistDisp = Mat(256, 256, CV_8UC1);
		HistDisp = Scalar::all(0);

		for (int w = 0; w < 256; w++) {
			int nNormalizedValue = (int)Hist[w] * dNormalizeFactor;
			for (int h = 255; h > 255 - nNormalizedValue; h--) {
				HistDisp.at<unsigned char>(h, w) = 255;
			}
		}
		imshow("Histogram of input Image", HistDisp);
		waitKey(0);
	}
}


void CViewerDlg::OnHistogramEqualizationClicked()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (isImageOpened && nFormat == FORMAT_GRAY) {
		if (Hist == NULL) {
			Hist = new int[256];
		}
		memset(Hist, 0, sizeof(int) * 256);

		for (int h = 0; h < nHeight_in; h++) {
			for (int w = 0; w < nWidth_in; w++) {
				Hist[ch_in_gray[h][w]]++;
			}
		}
	}
	double Hist_CDF[256] = { 0.0 };
	Mat Eq_Img = Mat(256, 256, CV_8UC1);

	Hist_CDF[0] = (double)(Hist[0]/(nHeight_in*nWidth_in));
	for (int i = 1; i<256; i++) 
		Hist_CDF[i] = Hist_CDF[i-1] + (double)Hist[i]/(nHeight_in*nWidth_in);
	for (int i = 0; i < nHeight_in; i++) {
		for (int j = 0; j < nWidth_in; j++) {
			Eq_Img.at<unsigned char>(i, j) = (unsigned char)(Hist_CDF[ch_in_gray[i][j]] *255);
		}
	}

	// 1 . Hist ��� �����ٰ� �󵵼��� �����Ѵ�.
	int *Hist_Eq = new int[256];
	memset(Hist_Eq, 0, sizeof(int) * 256);

	for (int h = 0; h < nHeight_in; h++) {
		for (int w = 0; w < nWidth_in; w++) {
			Hist_Eq[Eq_Img.at<unsigned char>(h, w)]++;
		}
	}

	DisplayImage(Eq_Img, false);
	DisplayHistogram(Hist);
	DisplayHistogram(Hist_Eq);
}



void DisplayHistogram(int * Hist) {
	int nMax = 0;
	for (int n = 0; n < 256; n++) {
		int a = Hist[n];

		if (nMax < Hist[n]) {
			nMax = Hist[n];
		}
	}
	double dNormalizeFactor = 255.0 / nMax;
	Mat HistDisp = Mat(256, 256, CV_8UC1);
	HistDisp = Scalar::all(0);
	for (int w = 0; w < 256; w++) {
		int nNormalizedValue = (int)Hist[w] * dNormalizeFactor;
		for (int h = 255; h > 255 - nNormalizedValue; h--) {
			HistDisp.at<unsigned char>(h, w) = 255;
		}
	}
	imshow("Histogram", HistDisp);
	waitKey(0);
}


void CViewerDlg::OnHistogramMatchingClicked()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (isImageOpened && nFormat == FORMAT_GRAY) {
	
		if (Hist == NULL) {
				Hist = new int[256];
		}
		memset(Hist, 0, sizeof(int) * 256);

		for (int h = 0; h < nHeight_in; h++) {
			for (int w = 0; w < nWidth_in; w++) {
					Hist[ch_in_gray[h][w]]++;
			}
		}

		Mat MatchImg(256, 256, CV_8UC1), RefImg(nHeight_in, nWidth_in, CV_8UC1);
		int Hist_Ref[256] = { 0 };
		int Hist_Mat[256] = { 0 };
		float Hist_CDF[256], Hist_CDF_Ref[256];

		MatchImg = Scalar::all(0);
		RefImg = Scalar::all(0);

		srand(GetTickCount()); 
		
		for (int h = 0; h < RefImg.rows; h++) {
			for (int w = 0; w < RefImg.cols; w++) {
				RefImg.at<unsigned char>(h, w) = (unsigned char)rand() % 255;
				// ���� �̷��� �������� ������ �ȼ� ������ ��Ī�� ��Ų�ٸ� ����� ���� Ȯ���� �ϱ� ����
				Hist_Ref[RefImg.at<unsigned char>(h, w)]++;
			}
		}

		// -> �̰��� �ٸ� �̹����� �׽�Ʈ �غ� ��
		/*FILE * fp_ref;
		fopen_s(&fp_ref, "gAirplane256_256.raw", "rb");
		uchar**tempin = MemAlloc2D(256, 256,0);
		for (int h = 0; h < nHeight_in; h++) {
			fread(tempin[h], sizeof(unsigned char), nWidth_in, fp_ref);
		}
		for (int h = 0; h < RefImg.rows; h++) {
			for (int w = 0; w < RefImg.cols; w++) {
				RefImg.at<unsigned char>(h, w) = tempin[h][w];
				Hist_Ref[RefImg.at<unsigned char>(h, w)]++;
			}
		}*/
		//////////////////////////////////////////////

		Hist_CDF[0] = (double)Hist[0] / (nHeight_in * nWidth_in);
		Hist_CDF_Ref[0] = (double)Hist_Ref[0] / (nHeight_in * nWidth_in);

		for (int n = 1; n < 256; n++) {
			Hist_CDF[n] = (double)Hist[n] / (nHeight_in * nWidth_in) + Hist_CDF[n - 1];
			Hist_CDF_Ref[n] = (double)Hist_Ref[n] / (nHeight_in * nWidth_in) + Hist_CDF_Ref[n - 1];
		}

		double outputPixelVal[256] = { 0 }; // ���� �ڷῡ�� ���� output pixel value�� ���� �迭
		for (int i = 0; i < 256; i++) {
			double nMin = 1; // CDF�� 0~1 ������ ���� ���´�. 
			int xj = 0;
			for (int j = 0; j < 256; j++) {
				// �Ʒ� �κ��� �ݵ�� �ʿ��ϴ�. ������ ��Ȯ�� CDF�� �´� ���� ���� ������ 
				// �׷��� ���� ��Ȯ�ϰ� ����� �κ��� ã�ƾ��� �Ʒ�ó�� 
				if (abs(Hist_CDF[i] - Hist_CDF_Ref[j]) < nMin) { // CDF�� �����Լ��� �ƴ� �� �ִ�. �׷��� �Է°� �������� CDF�� ���� ����� �� ������
					nMin = abs(Hist_CDF[i] - Hist_CDF_Ref[j]);
					xj = j;
				}
				if (Hist_CDF[i] == Hist_CDF_Ref[j]) {  // �����ϸ� �׳� ���� ���´�.
					xj = j;
					break;
				}
			}
			outputPixelVal[i] = xj;
		}

		//Histogram Matching ������ ���� Matching ����� Mat�� ����
		for (int h = 0; h < MatchImg.rows; h++) {
			for (int w = 0; w < MatchImg.cols; w++) {
				MatchImg.at<unsigned char>(h, w) = outputPixelVal[ch_in_gray[h][w]];
				Hist_Mat[MatchImg.at<unsigned char>(h, w)]++;
			}
		} // ������ 256x256 �̹��� �����̴�.


		DisplayImage(MatchImg, false);
		DisplayHistogram(Hist_Ref);
		DisplayHistogram(Hist_Mat);
		//fclose(fp_ref);
	}

}


void CViewerDlg::OnEditFilter()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (isImageOpened && nFormat == FORMAT_GRAY) {
		CFilterDlg FilterDlg;
		unsigned char** Pad, **Out;
		if (FilterDlg.DoModal() == IDOK) {
			
			// �ϴ��� ������ ��
	
			int nFilterType = FilterDlg.getFilterType();
			int nFilterSize = FilterDlg.getFilterSize();
			Mat Result(nHeight_in, nWidth_in, CV_8UC1);

			switch (nFilterType) {
			case FILTER_AVERAGE:
				
				if (nFilterSize >= 3) {
					if (nFilterSize % 2 == 0) {
						nFilterSize++;
					}
					Pad = Padding(ch_in_gray, nHeight_in, nWidth_in, nFilterSize);
					Out = MemAlloc2D(nHeight_in, nWidth_in, nFilterSize);

					AverageFilter(Pad, Out, nHeight_in, nWidth_in, nFilterSize);

					/*for (int i = 0; i < nHeight_in; i++) {
						for (int j = 0; j < nWidth_in; j++) {
							Result.at<unsigned char>(i, j) = Out[i][j];
						}  
					}*/    // �̷��� �ڵ尡 �Ʒ��� �ڵ�� ����

					DisplayImage(GrayToMat(Out,nHeight_in, nWidth_in), false);

					MemFree2D(Pad, nHeight_in + (int)(nFilterSize / 2) * 2);
					MemFree2D(Out, nHeight_in);
				}
				else MessageBox("Filter Size�� �߸��Ǿ����ϴ�. Filter Size�� 3�̻��� ���� ���� ������ �մϴ�.   ");
				break;

			case FILTER_SMOOTH:
					Pad = Padding(ch_in_gray, nHeight_in, nWidth_in, 3);
					Out = MemAlloc2D(nHeight_in, nWidth_in, 0);

					SmoothFilter(Pad, Out, nHeight_in, nWidth_in);

					/*for (int i = 0; i < nHeight_in; i++) {
						for (int j = 0; j < nWidth_in; j++) {
							Result.at<unsigned char>(i, j) = Out[i][j];
						}
					}*/

					DisplayImage(GrayToMat(Out, nHeight_in, nWidth_in), false);

					MemFree2D(Pad, nHeight_in);
					MemFree2D(Out, nHeight_in);
					break;

			case FILTER_SHARPEN:
					Pad = Padding(ch_in_gray, nHeight_in, nWidth_in, 3);
					Out = MemAlloc2D(nHeight_in, nWidth_in, 0);

					SharpenFilter(Pad, Out, nHeight_in, nWidth_in);

					/*for (int i = 0; i < nHeight_in; i++) {
						for (int j = 0; j < nWidth_in; j++) {
							Result.at<unsigned char>(i, j) = Out[i][j];
						}
					}
					DisplayImage(Result, false);
					*/

					DisplayImage(GrayToMat(Out, nHeight_in, nWidth_in), false);

					MemFree2D(Pad, nHeight_in);
					MemFree2D(Out, nHeight_in);
					break;

			case FILTER_GAUSSIAN:
					Pad = Padding(ch_in_gray, nHeight_in, nWidth_in, 3);
					Out = MemAlloc2D(nHeight_in, nWidth_in, 0);

					GaussianFilter(Pad, Out, nHeight_in, nWidth_in);

					/*Mat Result(nHeight_in, nWidth_in, CV_8UC1);
					for (int i = 0; i < nHeight_in; i++) {
						for (int j = 0; j < nWidth_in; j++) {
							Result.at<unsigned char>(i, j) = Out[i][j];
						}
					}
					DisplayImage(Result, false);*/

					DisplayImage(GrayToMat(Out, nHeight_in, nWidth_in), false);

					MemFree2D(Pad, nHeight_in);
					MemFree2D(Out, nHeight_in);
					break;
			}
		}
	}
	else {
	
		MessageBox("�ҷ��� ������ ���ų� ���� ������ ȸ���� ������ �ƴմϴ�.");
	}
}

unsigned char**Padding(unsigned char** In, int nHeight, int nWidth, int nFilterSize) {
	int nPadSize = (int)(nFilterSize / 2);
	unsigned char**Pad = MemAlloc2D(nHeight + 2 * nPadSize, nWidth + 2 * nPadSize, 0);

	for (int h = 0; h < nHeight; h++) {
		for (int w = 0; w < nHeight; w++) {
			Pad[h + nPadSize][w + nPadSize] = In[h][w];
		}
	}


	//   ------
	//
	//   ------
	for (int h = 0; h < nPadSize; h++) {
		for (int w = 0; w < nWidth; w++) {
			Pad[h][w + nPadSize] = In[0][w];
			Pad[h + nHeight + nPadSize][w + nPadSize] = In[nHeight - 1][w];
		}
	}

	//  |      |
	//  |      |
	//  |      |
	for (int h = 0; h < nHeight; h++) {
		for (int w = 0; w < nPadSize; w++) {
			Pad[h + nPadSize][w] = In[h][0];
			Pad[h + nPadSize][w + nWidth + nPadSize] = In[h][nWidth-1];
		}
	}

	for (int h = 0; h < nPadSize; h++) {
		for (int w = 0; w < nPadSize; w++) {
			Pad[h][w] = In[0][0];
			Pad[h + nHeight + nPadSize][w] = In[nHeight - 1][0];
			Pad[h][w + (nWidth + nPadSize)] = In[0][nWidth - 1];
			Pad[h + nHeight + nPadSize][w + nWidth + nPadSize] = In[nHeight - 1][nWidth - 1];
		}
	}

	return Pad;
}
void AverageFilter(unsigned char **In_Pad, unsigned char**Out, int nHeight, int nWidth, int nFilterSize) {


	for (int i = 1; i <= nHeight; i++) {
		for (int j = 1; j <= nWidth; j++) {
			int sum = 0;
			for (int u = 0; u < nFilterSize; u++) {
				for (int v = 0; v < nFilterSize; v++) {
					// In_Pad[i + u - 1][j + v - 1]
					sum += In_Pad[i + u - 1][j + v - 1];
				}
			}
			Out[i-1][j-1] = sum / (nFilterSize*nFilterSize);
		}
	}
}

void SmoothFilter(unsigned char **In_Pad, unsigned char**Out, int nHeight, int nWidth) {


	double SmoothMask[3][3] = { { 1.0 / 16, 2.0 / 16, 1.0 / 16 },
								{ 2.0 / 16, 4.0 / 16, 2.0 / 16 },
								{ 1.0 / 16, 2.0 / 16, 1.0 / 16 } };
	int nFilterSize = 3;

	for (int i = 1; i <= nHeight; i++) {
		for (int j = 1; j <= nWidth; j++) {
			double sum = 0;
			for (int u = 0; u < nFilterSize; u++) {
				for (int v = 0; v < nFilterSize; v++) {
					// In_Pad[i + u - 1][j + v - 1]
					sum += (In_Pad[i + u - 1][j + v - 1])* SmoothMask[u][v];
				}
			}
			Out[i-1][j-1] = saturate_cast<unsigned char>(sum);
		}
	}

}

void SharpenFilter(unsigned char **In_Pad, unsigned char**Out, int nHeight, int nWidth) {

	int SharpenMask[3][3] = { {  0, -1,  0 },
							 { -1,  5, -1 },
							 {  0, -1,  0 } };
	int nFilterSize = 3;

	for (int i = 1; i <= nHeight; i++) {
		for (int j = 1; j <= nWidth; j++) {
			int sum = 0;
			for (int u = 0; u < nFilterSize; u++) {
				for (int v = 0; v < nFilterSize; v++) {
					// In_Pad[i + u - 1][j + v - 1]
					sum += In_Pad[i + u - 1][j + v - 1] * SharpenMask[u][v];
				}
			}
			Out[i-1][j-1] = saturate_cast<unsigned char>(sum);
			//Out[i][j] = sum; // => �̹��� �������
		}
	}
	
}
void GaussianFilter(unsigned char **In_Pad, unsigned char**Out, int nHeight, int nWidth) {

	int nFilterSize = 3;
	float sigma = 2.f;


	float GaussianMask[3][3] = { 0 };

	float value, Sum = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			// �߽��� 0�̴�.
			value = exp((-1.0)*((i - 1)*(i - 1)+(j - 1)*(j - 1)) / (2.0 * sigma * sigma)) / sqrt((2.0 * PI * sigma * sigma));
			Sum += value;
			GaussianMask[i][j] = value;
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			GaussianMask[i][j] = GaussianMask[i][j] / Sum;
		}
	}
	
/*	float test = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			test+=GaussianMask[i][j];
		}
	} */      // => ���� ��� ������ 1�� �ٻ�

	for (int i = 1; i <= nHeight; i++) {
		for (int j = 1; j <= nWidth; j++) {
			int sum = 0;
			for (int u = 0; u < nFilterSize; u++) {
				for (int v = 0; v < nFilterSize; v++) {
					sum += In_Pad[i + u - 1][j + v - 1]* GaussianMask[u][v];
				}
			}
			Out[i-1][j-1] = saturate_cast<unsigned char>(sum);
		}
	}
}


Mat GrayToMat(unsigned char** img, int nHeight, int nWidth) {
	Mat rtn = Mat(nHeight, nWidth, CV_8UC1);

	for (int h = 0; h < nHeight; h++) {

		for (int w = 0; w < nWidth; w++) {
			rtn.at<unsigned char>(h, w) = img[h][w];
		}
	}	
	return rtn;
}

void CViewerDlg::OnNoisereductionAddnoiseClicked(){
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CAddNoiseDlg AddNoiseDlg;
	BYTE** NoiseImg = MemAlloc2D(nHeight_in, nWidth_in, 0);
	if (isImageOpened && nFormat == FORMAT_GRAY)
	{
		if (AddNoiseDlg.DoModal() == IDOK)
		{
			CString OutFileName = InpFileName;
			float Value_1 = AddNoiseDlg.GetVal_1();
			float Value_2 = AddNoiseDlg.GetVal_2();

			int nNoiseType = AddNoiseDlg.GetNoiseType();

			if (nNoiseType == NOISE_GN) {

				if (Value_2 < 1) {
					MessageBox("ǥ������ ���� �߸��Ǿ����ϴ�. ǥ������ ���� 1 �̽��̾�� �մϴ�.");
					MemFree2D(NoiseImg, nHeight_in);
					return;
				}
				InputGaussianNoise(ch_in_gray, NoiseImg, nHeight_in, nWidth_in, Value_1, Value_2);
				OutFileName += "_GN.raw";
			}
			else {

				if (Value_1 <= 0 && Value_2 <= 0) {
					MessageBox("�� ���� Ȯ�� �� �� ��� �ϳ��� 0 ���� Ŀ�� �մϴ�.");
					MemFree2D(NoiseImg, nHeight_in);
					return;
				}
				InputSaltPepperNoise(ch_in_gray, NoiseImg, nHeight_in, nWidth_in, Value_1, Value_2);
				OutFileName += "_SPN.raw";

			}

			FILE * fp;

			fopen_s(&fp, OutFileName, "wb");
			for (int h = 0; h < nHeight_in; h++) 
				fwrite(NoiseImg[h], sizeof(unsigned char), nWidth_in, fp);

			fclose(fp);
			MemFree2D(NoiseImg, nHeight_in);
			
		}
	}
}

void InputGaussianNoise(unsigned char** In, unsigned char **Out, int nHeight, int nWidth, float fMean, float fStdev) {
	float fTemp = 0, fPDF[256] = { 0.0f };
	GetGaussianPDF(fPDF, 256, fMean, fStdev);
	srand(GetTickCount());
	for (int h = 0; h < nHeight; h++)
	{
		for (int w = 0; w < nWidth; w++)
		{
			fTemp = (float)In[h][w] + GetNoise(fPDF, 256);
			Out[h][w] = saturate_cast<unsigned char>(fTemp);
					// �̰��� saturate_cast�� �ٲپ���.
		}
	}
}

void InputSaltPepperNoise(unsigned char**in, unsigned char **Out, int nHeight, int nWidth, float fSProb, float fPProb) {
	float Low = fSProb;
	float High = 1.0f - fPProb;
	float fRand;
	srand(GetTickCount());
	for (int h = 0; h < nHeight; h++)
	{
		for (int w = 0; w < nWidth; w++)
		{
			fRand = ((float)rand() / RAND_MAX);
			if (fRand < Low)
			{
				Out[h][w] = 255;
			}
			else if (fRand > High)
			{
				Out[h][w] = 0
					;
			}
			else Out[h][w] = in[h][w];
		}
	}
}

void GetGaussianPDF(float* EmptyPDF, int nLength, float fMean, float fStDev) {

	int n;
	int Center = nLength / 2;
	float x;
	for (n = 0; n<nLength; n++)
	{
		x = (float)(n - Center);
		EmptyPDF[n] = (1 / ((float)sqrt(2 * PI) * fStDev)) * exp(-pow(x - fMean, 2) / (2 * fStDev * fStDev));
	}

}
float GetNoise(float*PDF, int nLength) {

	int n;
	int Center = nLength / 2;
	float fRand, fComp, fTemp = 0;
	float x = 0, fDiff;
	float* CDF = new float[nLength];
	CDF[0] = 0;
	fRand = (float)rand() / (RAND_MAX + 1); // 0~1 Uniform Distribution 

	for (n = 1; n<nLength; n++)
	{
		CDF[n] = (PDF[n] + PDF[n - 1]) / 2 + CDF[n - 1];
		fDiff = fRand - CDF[n];
		if (fDiff < 0)
		{
			x = ((float)n - Center);
			break;
		}
	}

	fComp = (fRand - CDF[n - 1]) / (CDF[n] - CDF[n - 1]);
	delete[] CDF;
	return x + fComp;

}

void ArithmeticMeanFilter(unsigned char**img_in, unsigned char** Out, int nHeight, int nWidth, int nFilterSize) {
	
	int nTemp;
	int nPadSize = (int)(nFilterSize / 2);

	unsigned char ** img_Pad = Padding(img_in, nHeight, nWidth, nFilterSize);

	for (int h = 0; h < nHeight; h++) {
		for (int w = 0; w < nWidth; w++) {
			nTemp = 0;
			for (int m = 0; m < nFilterSize; m++) {
				for (int n = 0; n < nFilterSize; n++) {
					nTemp += img_Pad[h + m][w + n];
				}
			}
			Out[h][w] = saturate_cast<unsigned char>(nTemp / (nFilterSize*nFilterSize));
		}
	}

	MemFree2D(img_Pad, nHeight + 2 * nPadSize);
}
void GeometricMeanFilter(unsigned char**img_in, unsigned char**Out, int nHeight, int nWidth, int nFilterSize) {
	double nTemp;
	int nPadSize = (int)(nFilterSize / 2);
	unsigned char ** img_Pad = Padding(img_in, nHeight, nWidth, nFilterSize);

	for (int h = 0; h < nHeight; h++) {
		for (int w = 0; w < nWidth; w++) {
			nTemp = 1;
			for (int m = 0; m < nFilterSize; m++) {
				for (int n = 0; n < nFilterSize; n++) {
					nTemp *= img_Pad[h + m][w + n];
				}
			}

			//int a = static_cast<unsigned char>(pow(nTemp, 1.0 / (nFilterSize*nFilterSize)));


			Out[h][w] = saturate_cast<unsigned char>(pow(nTemp , 1.0/(nFilterSize*nFilterSize)));
			//int a = Out[h][w];

		}
	}
	MemFree2D(img_Pad, nHeight + 2 * nPadSize);


	//std::cout << pow(4, 1 / 2) <<std::endl;
			 // ���⼭ ���� �� ��!


}
void HarmonicMeanFilter(unsigned char**img_in, unsigned char** Out, int nHeight, int nWidth, int nFilterSize) {
	double nTemp ;
	int nPadSize = (int)(nFilterSize / 2);

	unsigned char ** img_Pad = Padding(img_in, nHeight, nWidth, nFilterSize);

	for (int h = 0; h < nHeight; h++) {
		for (int w = 0; w < nWidth; w++) {
			nTemp = 0;
			for (int m = 0; m < nFilterSize; m++) {
				for (int n = 0; n < nFilterSize; n++) {
					nTemp += (double)1.0/img_Pad[h + m][w + n];
					
				}
			}
			Out[h][w] = saturate_cast<unsigned char>(nFilterSize*nFilterSize / nTemp);
		}
	}
	MemFree2D(img_Pad, nHeight + 2 * nPadSize);
}
void ContraharmonicMeanFilter(unsigned char** img_in, unsigned char**Out, int nHeight, int nWidth, int nFilterSize, int Q) {
	double nTemp;
	double nTemp2;
	int nPadSize = (int)(nFilterSize / 2);
	unsigned char ** img_Pad = Padding(img_in, nHeight, nWidth, nFilterSize);
	for (int h = 0; h < nHeight; h++) {
		for (int w = 0; w < nWidth; w++) {
			nTemp = 0;
			nTemp2 = 0;
			for (int m = 0; m < nFilterSize; m++) {
				for (int n = 0; n < nFilterSize; n++) {
					nTemp += pow(img_Pad[h + m][w + n],Q+1);
					nTemp2 += pow(img_Pad[h + m][w + n], Q);
				}
			}
			Out[h][w] = saturate_cast<unsigned char>(nTemp / nTemp2);
		}
	}
	MemFree2D(img_Pad, nHeight + 2 * nPadSize);
}

void MedianFilter(unsigned char **img_in, unsigned char**Out, int nHeight, int nWidth, int nFilterSize) {

	int nTemp;
	int nPadSize = (int)(nFilterSize / 2);
	std::vector<unsigned char> List;
	unsigned char ** img_Pad = Padding(img_in, nHeight, nWidth, nFilterSize);

	for (int h = 0; h < nHeight; h++) {
		for (int w = 0; w < nWidth; w++) {

			List.clear();

			for (int m = 0; m < nFilterSize; m++) {
				for (int n = 0; n < nFilterSize; n++) {

					List.push_back(img_Pad[h + m][w + n]);

				}
			}
			sort(List.begin(), List.end());
			Out[h][w] = saturate_cast<unsigned char>(List[List.size() / 2]);
		}
	}
	MemFree2D(img_Pad, nHeight + 2 * nPadSize);
}

void AdaptiveMedianFilter(unsigned char**Img_in, unsigned char** Out, int nHeight, int nWidth, int nFilterSize_Min,  int nFilterSize_Max) {
// Z_med ����ũ ���� �ȼ��� �� �߰���
// Z_min ����ũ ���� �ȼ��� �� �ּҰ�
// Z_max ����ũ ���� �ȼ��� �� �ִ밪
// S_Max ����ũ�� �ִ밪
// Z_XY ���� ��ġ�� ��
// Level A
// A1 = Zmed- Zmin
// A2 = Zmed- Zmax
// if A1 > 0 and A2 <0, Go to Level B
// else increase mask Size
// if mask size < Smax, repeat Level A
// else return Zxy
// Level B
// B1 = Zxy - Zmin
// B2 = Zxy - Zmax
// if B1 > 0 and B2 < 0,return Zxy
// else return Zmed
	int A1, A2, B1, B2;
	int Zxy;
	int nPadSize = (int)(nFilterSize_Max / 2);
	unsigned char ** img_Pad = Padding(Img_in, nHeight, nWidth, nFilterSize_Max);
	int nFilter_Change;
	std::vector<unsigned char>List;
		for (int h = nPadSize; h < nHeight+ nPadSize; h++) {
			for (int w = nPadSize; w < nWidth + nPadSize; w++) {
				A1 = 0, A2 = 0, B1 = 0, B2 = 0;
				Zxy = img_Pad[h][w];
				nFilter_Change = nFilterSize_Min;
/////////////////// this is Level A Scope////////////////////////////////////////
				while (1) {
					for (int n = 0; n < nFilter_Change; n++) {
						for (int m = 0; m < nFilter_Change; m++) {
							List.push_back(img_Pad[h + n - nPadSize][w + m - nPadSize]);
						}
					}
				sort(List.begin(), List.end());
				int Zmed = List[List.size() / 2];
				int Zmin = List[0];
				int Zmax = List[List.size() - 1];
				A1 = Zmed - Zmin;
				A2 = Zmed - Zmax;
				if (A1 > 0 && A2 < 0)
					goto B;
				else
					nFilter_Change += 2;

				if (nFilter_Change <= nFilterSize_Max)
					continue;
				else {
					Out[h- nPadSize][w- nPadSize] = Zxy;
					goto Next;
				}
			}
/////////////// This is Level B scope ///////////////////////////////////////////
B:
				B1 = Zxy - List[0];
				B2 = Zxy - List[nFilter_Change*nFilter_Change - 1];

				if (B1 >0 && B2 <0) 
					Out[h- nPadSize][w- nPadSize] = Zxy;
				else
					Out[h- nPadSize][w- nPadSize] = List[List.size()/2]; 

			Next:
				List.clear();
		}
	}
	MemFree2D(img_Pad, nHeight + 2 * nPadSize);
}	

void CViewerDlg::OnNoisefilteringOrderStatisticClicked()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	COrderStatisticsDlg OSFDlg;

	if (isImageOpened == true && nFormat == FORMAT_GRAY) {
		if (OSFDlg.DoModal() == IDOK) {
			int nFilterSize = OSFDlg.GetFilterSIze1();

			int a = OSFDlg.Getm_radio_osf();
			int nFilterType = OSFDlg.GetOSFType();

			if (nFilterSize < 3) {
				MessageBox("���� ũ�Ⱑ �߸��Ǿ����ϴ�.");
			}
			if (nFilterSize % 2 == 0) {
				nFilterSize++;
			}
			CString OutFileName = InpFileName;
			unsigned char** Out = MemAlloc2D(nHeight_in, nWidth_in, 0);

			switch (nFilterType) {

			case NF_MEDIAN:
				MedianFilter(ch_in_gray, Out, nHeight_in, nWidth_in, nFilterSize);
				OutFileName += "_MEDF.raw";
				break;

			case NF_ADAPTIVEMEDIAN:
				int MaxFilterSize = OSFDlg.GetFilterSize2();
				AdaptiveMedianFilter(ch_in_gray, Out, nHeight_in, nWidth_in, nFilterSize, MaxFilterSize);
				OutFileName += "_AMDEF.raw";
				break;
			}

			DisplayImage(GrayToMat(Out, nHeight_in, nWidth_in), false);
			FILE * fp;
			fopen_s(&fp, OutFileName, "wb");
			for (int h = 0; h < nHeight_in; h++) {
				fwrite(Out[h], sizeof(unsigned char), nWidth_in, fp);
			}
			fclose(fp);
		}
	}
}


void CViewerDlg::OnNoisefilteringMeanfilterClicked()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CMeanFilterDlg MFDlg;

	if (isImageOpened == true && nFormat == FORMAT_GRAY) {
		if (MFDlg.DoModal() == IDOK) {
			int nFilterSize = MFDlg.GetFilterSize();
			int nFilterType = MFDlg.GetMeanFilterType();
			if (nFilterSize < 3) {
				MessageBox("���� ũ�Ⱑ �߸��Ǿ����ϴ�.");
				return;
			}
			if (nFilterSize % 2 == 0) {
				nFilterSize++;
			}
			CString OutFileName = InpFileName;
			unsigned char** Out = MemAlloc2D(nHeight_in, nWidth_in, 0);

			switch (nFilterType) {
			case NF_ARITHMETIC:
				ArithmeticMeanFilter(ch_in_gray, Out, nHeight_in, nWidth_in, nFilterSize);
				OutFileName += "_ANF.raw";
				break;
			case NF_GEOMETRIC:
				GeometricMeanFilter(ch_in_gray, Out, nHeight_in, nWidth_in, nFilterSize);
				OutFileName += "_GMF.raw";
				break;
			case NF_HARMONIC:
				HarmonicMeanFilter(ch_in_gray, Out, nHeight_in, nWidth_in, nFilterSize);
				OutFileName += "_HMF.raw";
				break;
			case NF_CONTRAHARMONIC:
				int Q = MFDlg.GetQ();
				ContraharmonicMeanFilter(ch_in_gray, Out, nHeight_in, nWidth_in, nFilterSize, Q);
				OutFileName += "_CHMF.raw";
				break;
			}
			DisplayImage(GrayToMat(Out, nHeight_in, nWidth_in), false);
			FILE * fp;
			fopen_s(&fp, OutFileName, "wb");
			for (int h = 0; h < nHeight_in; h++) {

				fwrite(Out[h], sizeof(unsigned char), nWidth_in, fp);
			}
			fclose(fp);
		}
	}
}


void CViewerDlg::OnGetPSNRClicked()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CPSNRDlg PSNRDlg;
	PSNRDlg.DoModal();
}
