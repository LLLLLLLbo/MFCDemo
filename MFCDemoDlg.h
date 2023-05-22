
// MFCDemoDlg.h: 头文件
//

#pragma once
#include "ImgProc.h"


// CMFCDemoDlg 对话框
class CMFCDemoDlg : public CDialogEx
{
// 构造
public:


	//亮度调节
	float m_imgalpha = 1;
	int m_imgbeta = 30;

	//均值二值化阈值偏移量
	int m_binaryoffset = 5;

	//图像锐化核大小及Factor
	CSliderCtrl m_Empkernelx;
	CSliderCtrl m_Empkernely;

	int m_empkernelx = 3;
	int m_empkernely = 3;
	float m_empfactor = 0.3f;


	//图像形态学内核大小
	int m_Morpkernelwidth = 3;
	int m_Morpkernelheight = 3;

	//按比例缩放
	float m_ResizeFxwidth = 1.0;
	float m_ResizeFyheight = 1.0;

	//改变图像尺寸大小
	int m_Resizewidth = 0;
	int m_Resizeheight = 0;

	//阈值滑动条
	CSliderCtrl m_lowSlider;
	int m_lowSliderthreshold = 127;
	CSliderCtrl m_highSlider;
	int m_highSliderthreshold = 255;
	
	//卷积核大小下拉框
	CComboBox m_Sobelcont;
	int m_filter = -1;

	//图片控件大小
	CRect rect1;
	CRect rect2;
	CRect rect3;

	//字体及画刷
	CBrush m_brush;
	CFont m_font;

	//图像处理
	ImgProc m_ImgProc;

	//数据定义
	string pre_img = "img";
	string after_img = "processimg";
	string enhance_img = "enhance_img";
	Mat src_img, gray_img;

//自定义函数方法




public:
	CMFCDemoDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCDEMO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStnClickedStatic1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton1Readimg();
	afx_msg void OnBnClickedButton1Readimg2();
	afx_msg void OnBnClickedButton1Closeimg();
	afx_msg void OnBnClickedButton2Gray();
	afx_msg void OnBnClickedButton2Grayhist();
	afx_msg void OnBnClickedButton8Imghist();
	afx_msg void OnBnClickedButton2Equa();
	afx_msg void OnBnClickedButton2Equahist();
	afx_msg void OnBnClickedButton2Imgequa();
	afx_msg void OnBnClickedButton2Grayequa();
	afx_msg void OnStnClickedStaticYuantu();
	afx_msg void OnStnClickedStaticEnhanceimg();
	afx_msg void OnBnClickedButton3Binaryimg();
	afx_msg void OnBnClickedButton3Binarygray();
	afx_msg void OnBnClickedButton3Ostu();
	afx_msg void OnBnClickedButton4Blur();
	afx_msg void OnBnClickedButtonMedian();
	afx_msg void OnBnClickedButtonGaussian();
	afx_msg void OnBnClickedButton2Median();
	afx_msg void OnBnClickedButtonSobel();
	afx_msg void OnBnClickedButtonLaplacian();
	afx_msg void OnCbnSelchangeCombo1Sobel();

	afx_msg void OnBnClickedButton11Filter();
	afx_msg void OnBnClickedButtonCanny();
	afx_msg void OnBnClickedButtonRoi();
	afx_msg void OnBnClickedButton3Imgequahist();
	afx_msg void OnBnClickedButton2Grayequahist();
	afx_msg void OnNMCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult);

//	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	afx_msg void OnNMCustomdrawSliderLowslider(NMHDR* pNMHDR, LRESULT* pResult);

	afx_msg void OnBnClickedButtonHorizontalflip();
	afx_msg void OnBnClickedButtonVerticalflip();
	afx_msg void OnBnClickedButtonHorizontalverticalflip();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButtonRotate90();
	afx_msg void OnBnClickedButtonRotate180();
	afx_msg void OnBnClickedButtonRotate270();
	afx_msg void OnEnChangeEditResizewidth();
	afx_msg void OnBnClickedButtonResizeok();
	afx_msg void OnBnClickedButtonBianryinv();
	afx_msg void OnEnChangeEditLowthreshold();
	afx_msg void OnDeltaposSpinResizewidth(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinResizeheight(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonFxfyok();
	afx_msg void OnDeltaposSpin3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpin4(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonErosion();
	afx_msg void OnBnClickedButtonDiation();
	afx_msg void OnBnClickedButtonDilation();
	afx_msg void OnBnClickedButtonMopopen();
	afx_msg void OnBnClickedButtonMopclose();
	afx_msg void OnBnClickedButtonReversecolor();
	afx_msg void OnNMCustomdrawSliderHighslider(NMHDR* pNMHDR, LRESULT* pResult);

	afx_msg void OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpin2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonDynbinary();
	afx_msg void OnDeltaposSpin5(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpin6(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonChangelight();


	
};

