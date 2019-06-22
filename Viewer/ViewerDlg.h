
// ViewerDlg.h : 헤더 파일
//

#pragma once

#include <opencv2\opencv.hpp>
#include "RawInfoDlg.h"
#include "ImgScalingDlg.h"
#include "RotationDlg.h"
#include "FilterDlg.h"
#include "AddNoiseDlg.h"
#include "MeanFilterDlg.h"
#include "OrderStatisticsDlg.h"
#include <vector>

using namespace cv;


#define CLIP(x) ((x>255)? 255:(x<0)? 0 :x)
#define PI 3.141592


// CViewerDlg 대화 상자
class CViewerDlg : public CDialogEx
{


//////////// This is Enum EREA///////////////

	enum NoiseFilterType {
		NF_ARITHMETIC,
		NF_GEOMETRIC,
		NF_HARMONIC,
		NF_CONTRAHARMONIC,
		NF_MEDIAN,
		NF_ADAPTIVEMEDIAN
	};


	enum ImageFormat {
		FORMAT_RGB,
		FORMAT_YUV444,
		FORMAT_YUV420,
		FORMAT_GRAY
	};

	enum InterpolationType {
		BILINEAR,
		BICUBIC
	};

	enum FilterType
	{
		FILTER_AVERAGE,
		FILTER_SMOOTH,
		FILTER_SHARPEN,
		FILTER_GAUSSIAN
	};


	enum NoiseType {
		NOISE_GN,
		NOISE_SP
	};

/////////////////////////////////////////////

private:
		unsigned char **ch_in_1, **ch_in_2, **ch_in_3;
		unsigned char **ch_in_gray;

		int * Hist;

		int nHeight_in, nWidth_in;
		int nFormat;
		bool isImageOpened;

		CString InpFileName;

public:
	CStatic m_PicOri;
	CStatic m_PicProc;
	CRawInfoDlg RawInfoDlg;
	CImgScalingDlg ImgScalingDlg;
	CRotationDlg RotationDlg;



	Mat Ori_Img, Proc_Img;
	CRect rect;
	CDC* m_pDC;

	void DisplayImage(Mat DispMat, bool bInOut);
	void DisplayBitmap(CDC *pDC, CRect rect, IplImage* DisplpIImage);
	void ResizeImage(IplImage*src, IplImage**dst, CRect*rect);
	bool isInsideBoundary(int nHeight, int nWidth, double h, double w);
	unsigned char BilinearInterpolation(unsigned char**In, int nHeight_Ori, int nWidth_Ori, double h_Cvt, double w_Cvt);
	unsigned char BicubicInterpolation(unsigned char** In, int nHeight_Ori, int n_Width_Ori, double h_Cvt, double w_Cvt);
	
// 생성입니다.
public:
	CViewerDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VIEWER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpenMenuBtnClick();
	afx_msg void OnCloseMenuClick();
	afx_msg void OnConvertgrayBtnClick();
	afx_msg void OnEditScalingClick();
	afx_msg void OnEditRotationClick();
	afx_msg void OnHistogramGetClick();
	afx_msg void OnHistogramEqualizationClicked();
	afx_msg void OnHistogramMatchingClicked();
	afx_msg void OnEditFilter();
	afx_msg void OnNoisereductionAddnoiseClicked();
	afx_msg void OnNoisefilteringOrderStatisticClicked();
	afx_msg void OnNoisefilteringMeanfilterClicked();
	afx_msg void OnGetPSNRClicked();
};



unsigned char ** MemAlloc2D(int nHeight, int nWidth, unsigned char nInitVal);
float** MemAlloc2Df(int nHeight, int nWidth, int nInitVal);
void MemFree2Df(double ** Mem, int nHeight);
void MemFree2D(unsigned char** Mem, int nHeight);
void DisplayHistogram(int * Hist);

unsigned char**Padding(unsigned char** In, int nHeight, int nWidth, int nFilterSize);
void AverageFilter(unsigned char **In_Pad, unsigned char**Out, int nHeight, int nWidth, int nFilterSize);
void SmoothFilter(unsigned char **In_Pad, unsigned char**Out, int nHeight, int nWidth);
void SharpenFilter(unsigned char **In_Pad, unsigned char**Out, int nHeight, int nWidth);
void GaussianFilter(unsigned char **In_Pad, unsigned char**Out, int nHeight, int nWidth);
Mat GrayToMat(unsigned char** img, int nHeight, int nWidth);

void InputGaussianNoise(unsigned char** In, unsigned char **Out, int nHeight, int nWidth, float fMean, float fStdev);
void InputSaltPepperNoise(unsigned char**in , unsigned char **Out, int nHeight, int nWidth, float fSProb, float fPProb);

void GetGaussianPDF(float* EmptyPDF, int nLength, float fMean, float fStDev);
float GetNoise(float*PDF,int nLength);

void ArithmeticMeanFilter(unsigned char**img_in, unsigned char** Out, int nHeight, int nWidth, int nFilterSize);
void GeometricMeanFilter(unsigned char**img_in, unsigned char**Out, int nHeight, int nWidth, int nFilterSize);
void HarmonicMeanFilter(unsigned char**img_in, unsigned char** Out, int nHeight, int nWidth, int nFilterSize);
void ContraharmonicMeanFilter(unsigned char** img_in, unsigned char**Out, int nHeight, int nWidth, int nFilterSize, int Q);

void MedianFilter(unsigned char **img_in, unsigned char**Out, int nHeight, int nWidth, int nFilterSize);
void AdaptiveMedianFilter(unsigned char**Img_in, unsigned char** Out, int nHeight, int nWidth, int nFilterSize_Min, int nFilterSize_Max);
