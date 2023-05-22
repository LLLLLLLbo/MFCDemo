
// MFCDemoDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCDemo.h"
#include "MFCDemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif




//roi回调函数
void on_mouse(int event, int x, int y, int flags, void* param);
void showimg(Mat img, String str, CRect rect);

//roi自定义变量
bool drawing_box = false;
bool gotBox = false;
Rect box;
Point downPoint;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDeltaposSpinResizewidth(NMHDR* pNMHDR, LRESULT* pResult);
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


// CMFCDemoDlg 对话框








CMFCDemoDlg::CMFCDemoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCDEMO_DIALOG, pParent)

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1_SOBEL, m_Sobelcont);
	DDX_Control(pDX, IDC_SLIDER_LOWSLIDER, m_lowSlider);
	DDX_Slider(pDX, IDC_SLIDER_LOWSLIDER, m_lowSliderthreshold);
	DDX_Control(pDX, IDC_SLIDER_HIGHSLIDER, m_highSlider);
	DDX_Slider(pDX, IDC_SLIDER_HIGHSLIDER, m_highSliderthreshold);
	DDX_Control(pDX, IDC_SLIDER_EMPKERNELX, m_Empkernelx);
	DDX_Control(pDX, IDC_SLIDER_EMPKERNELY, m_Empkernely);

}

BEGIN_MESSAGE_MAP(CMFCDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_STN_CLICKED(IDC_STATIC_1, &CMFCDemoDlg::OnStnClickedStatic1)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON1_READIMG, &CMFCDemoDlg::OnBnClickedButton1Readimg)
	ON_BN_CLICKED(IDC_BUTTON1_CLOSEIMG, &CMFCDemoDlg::OnBnClickedButton1Closeimg)
	ON_BN_CLICKED(IDC_BUTTON2_GRAY, &CMFCDemoDlg::OnBnClickedButton2Gray)
	ON_BN_CLICKED(IDC_BUTTON2_GRAYHIST, &CMFCDemoDlg::OnBnClickedButton2Grayhist)
	ON_BN_CLICKED(IDC_BUTTON8_IMGHIST, &CMFCDemoDlg::OnBnClickedButton8Imghist)
	ON_BN_CLICKED(IDC_BUTTON2_IMGEQUA, &CMFCDemoDlg::OnBnClickedButton2Imgequa)
	ON_BN_CLICKED(IDC_BUTTON2_GRAYEQUA, &CMFCDemoDlg::OnBnClickedButton2Grayequa)
	ON_STN_CLICKED(IDC_STATIC_YUANTU, &CMFCDemoDlg::OnStnClickedStaticYuantu)
	ON_STN_CLICKED(IDC_STATIC_ENHANCEIMG, &CMFCDemoDlg::OnStnClickedStaticEnhanceimg)
	ON_BN_CLICKED(IDC_BUTTON3_BINARYIMG, &CMFCDemoDlg::OnBnClickedButton3Binaryimg)
	ON_BN_CLICKED(IDC_BUTTON3_BINARYGRAY, &CMFCDemoDlg::OnBnClickedButton3Binarygray)
	ON_BN_CLICKED(IDC_BUTTON3_OSTU, &CMFCDemoDlg::OnBnClickedButton3Ostu)
	ON_BN_CLICKED(IDC_BUTTON4_Blur, &CMFCDemoDlg::OnBnClickedButton4Blur)
	ON_BN_CLICKED(IDC_BUTTON_GAUSSIAN, &CMFCDemoDlg::OnBnClickedButtonGaussian)
	ON_BN_CLICKED(IDC_BUTTON2_MEDIAN, &CMFCDemoDlg::OnBnClickedButton2Median)
	ON_BN_CLICKED(IDC_BUTTON_SOBEL, &CMFCDemoDlg::OnBnClickedButtonSobel)
	ON_BN_CLICKED(IDC_BUTTON_LAPLACIAN, &CMFCDemoDlg::OnBnClickedButtonLaplacian)

	ON_BN_CLICKED(IDC_BUTTON11_FILTER, &CMFCDemoDlg::OnBnClickedButton11Filter)
	ON_BN_CLICKED(IDC_BUTTON_CANNY, &CMFCDemoDlg::OnBnClickedButtonCanny)
	ON_BN_CLICKED(IDC_BUTTON_ROI, &CMFCDemoDlg::OnBnClickedButtonRoi)
	ON_BN_CLICKED(IDC_BUTTON3_IMGEQUAHIST, &CMFCDemoDlg::OnBnClickedButton3Imgequahist)
	ON_BN_CLICKED(IDC_BUTTON2_GRAYEQUAHIST, &CMFCDemoDlg::OnBnClickedButton2Grayequahist)


	ON_WM_HSCROLL()

	ON_BN_CLICKED(IDC_BUTTON_HORIZONTALFLIP, &CMFCDemoDlg::OnBnClickedButtonHorizontalflip)
	ON_BN_CLICKED(IDC_BUTTON_VERTICALFLIP, &CMFCDemoDlg::OnBnClickedButtonVerticalflip)
	ON_BN_CLICKED(IDC_BUTTON_HORIZONTALVERTICALFLIP, &CMFCDemoDlg::OnBnClickedButtonHorizontalverticalflip)

	ON_BN_CLICKED(IDC_BUTTON_ROTATE90, &CMFCDemoDlg::OnBnClickedButtonRotate90)
	ON_BN_CLICKED(IDC_BUTTON_ROTATE180, &CMFCDemoDlg::OnBnClickedButtonRotate180)
	ON_BN_CLICKED(IDC_BUTTON_ROTATE270, &CMFCDemoDlg::OnBnClickedButtonRotate270)

	ON_BN_CLICKED(IDC_BUTTON_RESIZEOK, &CMFCDemoDlg::OnBnClickedButtonResizeok)
	ON_BN_CLICKED(IDC_BUTTON_BIANRYINV, &CMFCDemoDlg::OnBnClickedButtonBianryinv)

	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_RESIZEWIDTH, &CMFCDemoDlg::OnDeltaposSpinResizewidth)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_RESIZEHEIGHT, &CMFCDemoDlg::OnDeltaposSpinResizeheight)
	ON_BN_CLICKED(IDC_BUTTON_FXFYOK, &CMFCDemoDlg::OnBnClickedButtonFxfyok)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN3, &CMFCDemoDlg::OnDeltaposSpin3)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN4, &CMFCDemoDlg::OnDeltaposSpin4)
	ON_BN_CLICKED(IDC_BUTTON_EROSION, &CMFCDemoDlg::OnBnClickedButtonErosion)
	ON_BN_CLICKED(IDC_BUTTON_DILATION, &CMFCDemoDlg::OnBnClickedButtonDilation)
	ON_BN_CLICKED(IDC_BUTTON_MOPOPEN, &CMFCDemoDlg::OnBnClickedButtonMopopen)
	ON_BN_CLICKED(IDC_BUTTON_MOPCLOSE, &CMFCDemoDlg::OnBnClickedButtonMopclose)
	ON_BN_CLICKED(IDC_BUTTON_REVERSECOLOR, &CMFCDemoDlg::OnBnClickedButtonReversecolor)

	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CMFCDemoDlg::OnDeltaposSpin1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, &CMFCDemoDlg::OnDeltaposSpin2)
	ON_BN_CLICKED(IDC_BUTTON_DYNBINARY, &CMFCDemoDlg::OnBnClickedButtonDynbinary)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN5, &CMFCDemoDlg::OnDeltaposSpin5)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN6, &CMFCDemoDlg::OnDeltaposSpin6)
	ON_BN_CLICKED(IDC_BUTTON_CHANGELIGHT, &CMFCDemoDlg::OnBnClickedButtonChangelight)
END_MESSAGE_MAP()


// CMFCDemoDlg 消息处理程序

BOOL CMFCDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//TODO: 在此添加额外的初始化代码
	//图像显示框1初始化
	CWnd* pwnd1 = GetDlgItem(IDC_STATIC_1);
	pwnd1->GetClientRect(&rect1);
	namedWindow("img");
	HWND hwnd1 = (HWND)cvGetWindowHandle("img");
	HWND parent1 = ::GetParent(hwnd1);
	::SetParent(hwnd1, GetDlgItem(IDC_STATIC_1)->m_hWnd);
	::ShowWindow(parent1, SW_HIDE);
	
	


	//图像显示框2初始化
	CWnd* pwnd2 = GetDlgItem(IDC_STATIC_2);
	pwnd2->GetClientRect(&rect2);
	namedWindow("processimg");
	HWND hwnd2 = (HWND)cvGetWindowHandle("processimg");
	HWND parent2 = ::GetParent(hwnd2);
	::SetParent(hwnd2, GetDlgItem(IDC_STATIC_2)->m_hWnd);
	::ShowWindow(parent2, SW_HIDE);


	//图像显示框3初始化
	CWnd* pwnd3 = GetDlgItem(IDC_STATIC_3);
	pwnd3->GetClientRect(&rect3);
	namedWindow("enhance_img");
	HWND hwnd3 = (HWND)cvGetWindowHandle("enhance_img");
	HWND parent3 = ::GetParent(hwnd3);
	::SetParent(hwnd3, GetDlgItem(IDC_STATIC_3)->m_hWnd);
	::ShowWindow(parent3, SW_HIDE);



	//图像显示框上方字体初始化
	m_font.CreatePointFont(170, _T("楷体"));
	CWnd* twnd1 = GetDlgItem(IDC_STATIC_YUANTU);
	CWnd* twnd2 = GetDlgItem(IDC_STATIC_AFTERIMG);
	CWnd* twnd3 = GetDlgItem(IDC_STATIC_ENHANCEIMG);
	twnd1->SetFont(&m_font);
	twnd2->SetFont(&m_font);
	twnd3->SetFont(&m_font);

	//滤波器大小下拉框初始化
	m_Sobelcont.AddString(_T("1"));
	m_Sobelcont.AddString(_T("3"));
	m_Sobelcont.AddString(_T("5"));
	m_Sobelcont.AddString(_T("7"));
	m_Sobelcont.AddString(_T("9"));

	///1123

	//阈值编辑框只读
	((CEdit*)GetDlgItem(IDC_EDIT_LOWTHRESHOLD))->SetReadOnly(TRUE);
	((CEdit*)GetDlgItem(IDC_EDIT_HIGHTHRESHOLD))->SetReadOnly(TRUE);
	
	//低阈值编辑框初始化
	m_lowSlider.SetRange(0, 255);
	m_lowSlider.SetTicFreq(1);
	int low_Start = 127;
	m_lowSlider.SetPos(low_Start);
	SetDlgItemInt(IDC_EDIT_LOWTHRESHOLD, low_Start);

	//高阈值编辑框初始化
	m_highSlider.SetRange(0, 255);
	m_highSlider.SetTicFreq(1);
	int high_Start = 255;
	m_highSlider.SetPos(high_Start);
	SetDlgItemInt(IDC_EDIT_HIGHTHRESHOLD, high_Start);

	//比例缩放编辑框只读
	((CEdit*)GetDlgItem(IDC_EDIT_RESIZEFX))->SetReadOnly(TRUE);
	((CEdit*)GetDlgItem(IDC_EDIT_RESIZEFY))->SetReadOnly(TRUE);

	//比例缩放编辑框初始化
	CString fx, fy;
	fx = fy = _T("1.0");
	GetDlgItem(IDC_EDIT_RESIZEFX)->SetWindowText(fx);
	GetDlgItem(IDC_EDIT_RESIZEFY)->SetWindowText(fy);

	//形态学内核大小编辑框只读
	((CEdit*)GetDlgItem(IDC_EDIT_MORPKERNELWIDTH))->SetReadOnly(TRUE);
	((CEdit*)GetDlgItem(IDC_EDIT_MORPKERNELHEIGHT))->SetReadOnly(TRUE);

	//形态学核大小初始化
	SetDlgItemInt(IDC_EDIT_MORPKERNELWIDTH, m_Morpkernelwidth);
	SetDlgItemInt(IDC_EDIT_MORPKERNELHEIGHT, m_Morpkernelheight);


	//图像锐化编辑框只读
	((CEdit*)GetDlgItem(IDC_EDIT_EMPKERNELX))->SetReadOnly(TRUE);
	((CEdit*)GetDlgItem(IDC_EDIT_EMPKERNELY))->SetReadOnly(TRUE);
	((CEdit*)GetDlgItem(IDC_EDIT_EMPFACTOR))->SetReadOnly(TRUE);

	//图像锐化核大小及Factor初始化
	m_Empkernelx.SetRange(3, 201);
	m_Empkernelx.SetTicFreq(1);
	int kernel_x = 3;
	m_Empkernelx.SetPos(kernel_x);
	SetDlgItemInt(IDC_EDIT_EMPKERNELX, kernel_x);

	m_Empkernely.SetRange(3, 201);
	m_Empkernely.SetTicFreq(1);
	int kernel_y = 3;
	m_Empkernely.SetPos(kernel_y);
	SetDlgItemInt(IDC_EDIT_EMPKERNELY, kernel_y);

	CString emp_factor = _T("0.3");
	SetDlgItemText(IDC_EDIT_EMPFACTOR, emp_factor);

	//二值化阈值编辑框初始化
	SetDlgItemInt(IDC_EDIT_DYNBINARYOFFSET, m_binaryoffset);

	//亮度系数跟偏移量的初始化
	SetDlgItemInt(IDC_EDIT_LIGHTALPHA, m_imgalpha);
	SetDlgItemInt(IDC_EDIT_LIGHTBETA, m_imgbeta);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


void CMFCDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

}




//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCDemoDlg::OnStnClickedStatic1()
{
	// TODO: 在此添加控件通知处理程序代码
}

//图像显示
void showimg(Mat img, String str, CRect rect)
{
	cv::resize(img, img, Size(rect.Width(), rect.Height()));
	cv::imshow(str, img);
}



//<----------------------------读取图像按钮---------------------------------->
void CMFCDemoDlg::OnBnClickedButton1Readimg()
{
	// TODO: 在此添加控件通知处理程序代码
	//CString FilePathName;

	//CFileDialog dlg(TRUE, //TRUE为OPEN对话框，FALSE为SAVE AS对话框
	//	NULL,
	//	NULL,
	//	OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
	//	(LPCTSTR)_TEXT("Describe Files JPEG (*.jpg)|*.jpg|PNG(*.png) | *.png|GIF (*.gif)|*.gif|BMP (*.bmp)|*.bmp|All Files (*.*)|*.*||"),
	//	NULL);

	//if (dlg.DoModal() == IDOK)
	//{
	//	FilePathName = dlg.GetPathName(); //路径名+文件名
	//}
	//else
	//{
	//	return;
	//}

	//// 读取图像
	//src_img = cv::imread((LPCSTR)CStringA(FilePathName), 1);
	//
	////显示图像
	//showimg(src_img, pre_img, rect1);

	////使读取按钮失效
	//GetDlgItem(IDC_BUTTON1_READIMG)->EnableWindow(FALSE);
	src_img = imread("E://test.jpg");
	
	
	showimg(src_img, "img", rect1);
	GetDlgItem(IDC_BUTTON1_READIMG)->EnableWindow(FALSE);
}


//文本框
void CMFCDemoDlg::OnStnClickedStaticYuantu()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMFCDemoDlg::OnStnClickedStaticEnhanceimg()
{
	// TODO: 在此添加控件通知处理程序代码
}


//<----------------------------关闭图像按钮---------------------------------->
void CMFCDemoDlg::OnBnClickedButton1Closeimg()
{
	// TODO: 在此添加控件通知处理程序代码
	if (src_img.empty()) 
	{
		CString str;
		str = _T("未打开图片");
		MessageBox(str);
		return;
	}
	CRect crect;
	CWnd* pwnd1 = GetDlgItem(IDC_STATIC_1);
	pwnd1->GetClientRect(&crect);
	pwnd1->GetDC()->FillSolidRect(crect.left, crect.top, crect.Width(), crect.Height(), RGB(0, 0, 0));
	GetDlgItem(IDC_BUTTON1_READIMG)->EnableWindow(TRUE);
	src_img.release();
	gray_img.release();
}


//<----------------------------原图直方图---------------------------------->
void CMFCDemoDlg::OnBnClickedButton8Imghist()
{
	// TODO: 在此添加控件通知处理程序代码
	if (src_img.empty())
	{
		CString str;
		str = _T("未读取图片");
		MessageBox(str);
		return;
	}
	
	//直方图
	Mat img_hist = m_ImgProc.HistBgrImg(src_img);

	//显示图像
	CString str;
	str = _T("原图直方图");
	SetDlgItemTextW(IDC_STATIC_AFTERIMG, str);
	showimg(img_hist, after_img, rect2);

	//释放内存
	img_hist.release();
}



//<----------------------------灰度化图像---------------------------------->
void CMFCDemoDlg::OnBnClickedButton2Gray()
{
	// TODO: 在此添加控件通知处理程序代码
	if (src_img.empty()) 
	{
		CString str;
		str = _T("未读取图片");
		MessageBox(str);
		return;
	}

	//图像灰度化
	gray_img = m_ImgProc.Bgr2Gray(src_img);

	//显示图像
	CString str;
	str = _T("图像灰度化");
	SetDlgItemTextW(IDC_STATIC_AFTERIMG, str);
	showimg(gray_img, after_img, rect2);
}




//<----------------------------灰度直方图---------------------------------->
void CMFCDemoDlg::OnBnClickedButton2Grayhist()
{
	// TODO: 在此添加控件通知处理程序代码
	if (src_img.empty()) 
	{
		CString str;
		str = _T("未读取图片");
		MessageBox(str);
		return;
	}

	// 判断灰度图是否存在
	if (gray_img.empty()) 
	{
		cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);
	}

	//灰度图直方图
	Mat grayimg_hist = m_ImgProc.HistGrayImg(gray_img);

	//显示图像
	CString str;
	str = _T("灰度直方图");
	SetDlgItemTextW(IDC_STATIC_AFTERIMG, str);
	showimg(grayimg_hist, after_img, rect2);

	//释放内存
	grayimg_hist.release();
}



//<----------------------------原图均衡化--------------------------------->
void CMFCDemoDlg::OnBnClickedButton2Imgequa()
{
	// TODO: 在此添加控件通知处理程序代码
	if (src_img.empty()) 
	{
		CString str;
		str = _T("未读取图片");
		MessageBox(str);
		return;
	}

	//图像均衡化
	Mat equa_img = m_ImgProc.EquaBgrImg(src_img);

	//显示图像
	CString str;
	str = _T("原图均衡化");
	SetDlgItemTextW(IDC_STATIC_AFTERIMG, str);
	showimg(equa_img, after_img, rect2);

	//释放内存
	equa_img.release();
}

//<----------------------------灰度图均衡化--------------------------------->
void CMFCDemoDlg::OnBnClickedButton2Grayequa()
{
	// TODO: 在此添加控件通知处理程序代码
	if (src_img.empty())
	{
		CString str;
		str = _T("未读取图片");
		MessageBox(str);
		return;
	}

	// 判断灰度图是否存在
	if (gray_img.empty())
	{
		cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);
	}

	//灰度图均衡化
	Mat equa_grayimg = m_ImgProc.EquaGrayImg(gray_img);

	//显示图像
	CString str;
	str = _T("灰度图像均衡化");
	SetDlgItemTextW(IDC_STATIC_ENHANCEIMG, str);
	showimg(equa_grayimg, enhance_img, rect3);


	//释放内存
	equa_grayimg.release();
}
//<----------------------------原图均衡化直方图--------------------------------->
void CMFCDemoDlg::OnBnClickedButton3Imgequahist()
{
	// TODO: 在此添加控件通知处理程序代码
	if (src_img.empty())
	{
		CString str;
		str = _T("未读取图片");
		MessageBox(str);
		return;
	}

	//图像均衡化
	Mat equa_imghist = m_ImgProc.EquaImgHist(src_img);

	//显示图像
	CString str;
	str = _T("原图均衡化直方图");
	SetDlgItemTextW(IDC_STATIC_ENHANCEIMG, str);
	showimg(equa_imghist, enhance_img, rect3);

	//释放内存
	equa_imghist.release();
}

//<----------------------------灰度图均衡化直方图--------------------------------->
void CMFCDemoDlg::OnBnClickedButton2Grayequahist()
{
	// TODO: 在此添加控件通知处理程序代码
		// TODO: 在此添加控件通知处理程序代码
	if (src_img.empty())
	{
		CString str;
		str = _T("未读取图片");
		MessageBox(str);
		return;
	}
	if (gray_img.empty())
	{
		cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);
	}
	//图像均衡化
	Mat equa_grayimghist = m_ImgProc.EquaGrayImgHist(gray_img);

	//显示图像
	CString str;
	str = _T("灰度图均衡化直方图");
	SetDlgItemTextW(IDC_STATIC_ENHANCEIMG, str);
	showimg(equa_grayimghist, enhance_img, rect3);

	//释放内存
	equa_grayimghist.release();
}

//<----------------------------原图二值化--------------------------------->
void CMFCDemoDlg::OnBnClickedButton3Binaryimg()
{
	// TODO: 在此添加控件通知处理程序代码

	if (src_img.empty())
	{
		CString str;
		str = _T("未读取图片");
		MessageBox(str);
		return;
	}

	// 二值化图像
	Mat binary_img = m_ImgProc.BinaryBgrImg(src_img);


	//显示图像
	CString str;
	str = _T("原图二值化");
	SetDlgItemTextW(IDC_STATIC_AFTERIMG, str);
	showimg(binary_img, after_img, rect2);


	//释放内存
	binary_img.release();
}

//<----------------------------灰度图二值化--------------------------------->

void CMFCDemoDlg::OnBnClickedButton3Binarygray()
{
	// TODO: 在此添加控件通知处理程序代码
	if (src_img.empty())
	{
		CString str;
		str = _T("未读取图片");
		MessageBox(str);
		return;
	}

	if (gray_img.empty()) 
	{
		cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);
	}
	// 二值化图像
	Mat binary_grayimg = m_ImgProc.BinaryGrayImg(gray_img, m_lowSliderthreshold, m_highSliderthreshold);

	//显示图像
	CString str;
	str = _T("灰度图二值化");
	SetDlgItemTextW(IDC_STATIC_AFTERIMG, str);
	showimg(binary_grayimg, after_img, rect2);

	//释放内存
	binary_grayimg.release();
}

//<----------------------------OSTU--------------------------------->
void CMFCDemoDlg::OnBnClickedButton3Ostu()
{
	// TODO: 在此添加控件通知处理程序代码
	if (src_img.empty())
	{
		CString str;
		str = _T("未读取图片");
		MessageBox(str);
		return;
	}
	if (gray_img.empty())
	{
		cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);
	}

	// OSTU
	Mat ostu_grayimg = m_ImgProc.Ostu(gray_img);

	//显示图像
	CString str;
	str = _T("OSTU");
	SetDlgItemTextW(IDC_STATIC_ENHANCEIMG, str);
	showimg(ostu_grayimg, enhance_img, rect3);

	//释放内存
	ostu_grayimg.release();
}

//<----------------------------均值滤波--------------------------------->
void CMFCDemoDlg::OnBnClickedButton4Blur()
{
	// TODO: 在此添加控件通知处理程序代码
	if (src_img.empty())
	{
		CString str;
		str = _T("未读取图片");
		MessageBox(str);
		return;
	}
	if (m_filter == -1)
	{
		CString mesg;
		mesg = _T("请选择滤波器大小");
		MessageBox(mesg);
		return;
	}
	//均值滤波
	Mat blur_img = m_ImgProc.Blur(src_img, m_filter);

	//显示图像
	CString str;
	str = _T("均值滤波");
	SetDlgItemTextW(IDC_STATIC_AFTERIMG, str);
	showimg(blur_img, after_img, rect2);

	//释放内存
	blur_img.release();
}

//<----------------------------中值滤波--------------------------------->
void CMFCDemoDlg::OnBnClickedButton2Median()
{
	// TODO: 在此添加控件通知处理程序代码
	if (src_img.empty())
	{
		CString str;
		str = _T("未读取图片");
		MessageBox(str);
		return;
	}
	if (m_filter == -1)
	{
		CString mesg;
		mesg = _T("请选择滤波器大小");
		MessageBox(mesg);
		return;
	}
	//中值滤波
	Mat median_img = m_ImgProc.MedianBlur(src_img, m_filter);

	//显示图像
	CString str;
	str = _T("中值滤波");
	SetDlgItemTextW(IDC_STATIC_ENHANCEIMG, str);
	showimg(median_img, enhance_img, rect3);

	//释放内存
	median_img.release();
}

//<----------------------------高斯滤波--------------------------------->

void CMFCDemoDlg::OnBnClickedButtonGaussian()
{
	// TODO: 在此添加控件通知处理程序代码
	if (src_img.empty())
	{
		CString str;
		str = _T("未读取图片");
		MessageBox(str);
		return;
	}

	if (m_filter == -1)
	{
		CString mesg;
		mesg = _T("请选择滤波器大小");
		MessageBox(mesg);
		return;
	}

	//高斯滤波
	Mat gaussian_img = m_ImgProc.GaussianBlur(src_img, m_filter);

	//显示图像
	CString str;
	str = _T("高斯滤波");
	SetDlgItemTextW(IDC_STATIC_AFTERIMG, str);
	showimg(gaussian_img, after_img, rect2);

	//释放内存
	gaussian_img.release();
}

//<----------------------------Sobel--------------------------------->
void CMFCDemoDlg::OnBnClickedButtonSobel()
{
	// TODO: 在此添加控件通知处理程序代码
	if (src_img.empty())
	{
		CString str;
		str = _T("未读取图片");
		MessageBox(str);
		return;
	}
	if (m_filter == -1) 
	{
		CString mesg;
		mesg = _T("请选择滤波器大小");
		MessageBox(mesg);
		return;
	}
	
	Mat sobel_img = m_ImgProc.Sobel(src_img, m_filter);


	//显示图像
	CString str;
	str = _T("Sobel");
	SetDlgItemTextW(IDC_STATIC_AFTERIMG, str);
	showimg(sobel_img, after_img, rect2);

	//释放内存
	sobel_img.release();
}


//<----------------------------Laplacian--------------------------------->
void CMFCDemoDlg::OnBnClickedButtonLaplacian()
{
	// TODO: 在此添加控件通知处理程序代码
	if (src_img.empty())
	{
		CString str;
		str = _T("未读取图片");
		MessageBox(str);
		return;
	}
	if (m_filter == -1)
	{
		CString mesg;
		mesg = _T("请选择滤波器大小");
		MessageBox(mesg);
		return;
	}

	Mat laplacian_img = m_ImgProc.Laplacian(src_img, m_filter);

	//显示图像
	CString str;
	str = _T("laplacian");
	SetDlgItemTextW(IDC_STATIC_ENHANCEIMG, str);
	showimg(laplacian_img, enhance_img, rect3);

	//释放内存
	laplacian_img.release();

}


//<----------------------------Canny--------------------------------->
void CMFCDemoDlg::OnBnClickedButtonCanny()
{
	// TODO: 在此添加控件通知处理程序代码
	if (src_img.empty())
	{
		CString str;
		str = _T("未读取图片");
		MessageBox(str);
		return;
	}
	if (m_filter == -1)
	{
		CString mesg;
		mesg = _T("请选择滤波器大小");
		MessageBox(mesg);
		return;
	}
	
	Mat canny_img = m_ImgProc.Canny(src_img, m_filter);

	//显示图像
	CString str;
	str = _T("Canny");
	SetDlgItemTextW(IDC_STATIC_ENHANCEIMG, str);
	showimg(canny_img, enhance_img, rect3);

	//释放内存
	canny_img.release();
}


//<----------------------------滤波器大小选择--------------------------------->
void CMFCDemoDlg::OnBnClickedButton11Filter()
{
	// TODO: 在此添加控件通知处理程序代码
	int ind = m_Sobelcont.GetCurSel();
	CString str;
	m_Sobelcont.GetLBText(ind, str);
	m_filter = _ttoi(str);

	MessageBox(_T("滤波器大小为" + str));
}

void CMFCDemoDlg::OnCbnSelchangeCombo1Sobel()
{
	// TODO: 在此添加控件通知处理程序代码

}


//<----------------------------ROI区域--------------------------------->
void CMFCDemoDlg::OnBnClickedButtonRoi()
{
	// TODO: 在此添加控件通知处理程序代码
	if (src_img.empty())
	{
		CString str;
		str = _T("未读取图片");
		MessageBox(str);
		return;
	}

	Mat temp_img, roi_img;
	bool flageROI = true;
	src_img.copyTo(temp_img);
	src_img.copyTo(roi_img);


	namedWindow("ROI");
	setMouseCallback("ROI", on_mouse, NULL);

	while (!gotBox)
	{
		roi_img.copyTo(temp_img);
		rectangle(temp_img, box, Scalar(255, 0, 0), 2);//画出感兴趣区域
		imshow("ROI", temp_img);
		if (waitKey(50) == 'q')
			break;
	}

	setMouseCallback("ROI", NULL, NULL);
	destroyWindow("ROI");
	flageROI = true;
	if (flageROI) 
	{
		showimg(temp_img, enhance_img, rect3);
	}
	gotBox = false;
	temp_img.release();
	roi_img.release();
}

//<----------------------------ROI鼠标回调事件--------------------------------->
void on_mouse(int event, int x, int y, int flags, void* param)
{
	switch (event) 
	{
	case CV_EVENT_MOUSEMOVE:
		if (drawing_box) 
		{
			//鼠标的移动到downPoint的右下角
			if (x >= downPoint.x && y >= downPoint.y)
			{
				box.x = downPoint.x;
				box.y = downPoint.y;
				box.width = x - downPoint.x;
				box.height = y - downPoint.y;
			}
			//鼠标的移动到downPoint的右上角
			if (x >= downPoint.x && y <= downPoint.y)
			{
				box.x = downPoint.x;
				box.y = y;
				box.width = x - downPoint.x;
				box.height = downPoint.y - y;
			}
			//鼠标的移动到downPoint的左上角
			if (x <= downPoint.x && y <= downPoint.y)
			{
				box.x = x;
				box.y = y;
				box.width = downPoint.x - x;
				box.height = downPoint.y - y;
			}
			//鼠标的移动到downPoint的左下角
			if (x <= downPoint.x && y >= downPoint.y)
			{
				box.x = x;
				box.y = downPoint.y;
				box.width = downPoint.x - x;
				box.height = y - downPoint.y;
			}
		}
		break;
	case CV_EVENT_LBUTTONDOWN:
		//按下鼠标，代表可以可以开始画矩形
		drawing_box = true;
		//记录起点
		downPoint = Point(x, y);
		//初始化起始矩形框  
		box = Rect(x, y, 0, 0);
		break;

	case CV_EVENT_LBUTTONUP:

		//松开鼠标，代表结束画矩形
		drawing_box = false;
		gotBox = true;
		break;
	default:
		break;
	}
}

//<----------------------------二值化阈值调节--------------------------------->
void CMFCDemoDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值


	if (pScrollBar != NULL)
	{
		CSliderCtrl* pSlider = (CSliderCtrl*)pScrollBar;
		Mat dst_img;
		if (src_img.empty())
		{
			CString str;
			str = _T("未读取图片");
			MessageBox(str);
			return;
		}

		if (gray_img.empty())
		{
			cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);
		}
		if (pSlider->GetDlgCtrlID() == IDC_SLIDER_LOWSLIDER)
		{
			m_lowSliderthreshold = m_lowSlider.GetPos();
			SetDlgItemInt(IDC_EDIT_LOWTHRESHOLD, m_lowSliderthreshold);
			dst_img = m_ImgProc.BinaryGrayImg(gray_img, m_lowSliderthreshold, m_highSliderthreshold);
			CString str;
			str = _T("灰度图二值化");
			SetDlgItemTextW(IDC_STATIC_AFTERIMG, str);
			showimg(dst_img, after_img, rect2);

		}

		if (pSlider->GetDlgCtrlID() == IDC_SLIDER_HIGHSLIDER)
		{
			m_highSliderthreshold = m_highSlider.GetPos();
			SetDlgItemInt(IDC_EDIT_HIGHTHRESHOLD, m_highSliderthreshold);
			dst_img = m_ImgProc.BinaryGrayImg(gray_img, m_lowSliderthreshold, m_highSliderthreshold);
			CString str;
			str = _T("灰度图二值化");
			SetDlgItemTextW(IDC_STATIC_AFTERIMG, str);
			showimg(dst_img, after_img, rect2);

		}

		if (pSlider->GetDlgCtrlID() == IDC_SLIDER_EMPKERNELX)
		{
			m_empkernelx = m_Empkernelx.GetPos();
			SetDlgItemInt(IDC_EDIT_EMPKERNELX, m_empkernelx);
			dst_img = m_ImgProc.Emphasize(src_img, m_empkernelx, m_empkernely, m_empfactor);
			CString str;
			str = _T("图像锐化");
			SetDlgItemTextW(IDC_STATIC_AFTERIMG, str);
			showimg(dst_img, after_img, rect2);

		}

		if (pSlider->GetDlgCtrlID() == IDC_SLIDER_EMPKERNELY)
		{
			m_empkernely = m_Empkernely.GetPos();
			SetDlgItemInt(IDC_EDIT_EMPKERNELY, m_empkernely);
			dst_img = m_ImgProc.Emphasize(src_img, m_empkernelx, m_empkernely, m_empfactor);
			CString str;
			str = _T("图像锐化");
			SetDlgItemTextW(IDC_STATIC_AFTERIMG, str);
			showimg(dst_img, after_img, rect2);
		}
	}
}


//<----------------------------水平反转图像--------------------------------->
void CMFCDemoDlg::OnBnClickedButtonHorizontalflip()
{
	// TODO: 在此添加控件通知处理程序代码
	if (src_img.empty())
	{
		CString str;
		str = _T("未读取图片");
		MessageBox(str);
		return;
	}

	// 水平翻转图像
	Mat horizontalflip_img = m_ImgProc.HorizontalFlip(src_img);

	//显示图像
	CString str;
	str = _T("水平翻转");
	SetDlgItemTextW(IDC_STATIC_AFTERIMG, str);
	showimg(horizontalflip_img, after_img, rect2);

	//释放内存
	horizontalflip_img.release();	
}

//<----------------------------垂直翻转图像--------------------------------->
void CMFCDemoDlg::OnBnClickedButtonVerticalflip()
{
	// TODO: 在此添加控件通知处理程序代码
	if (src_img.empty())
	{
		CString str;
		str = _T("未读取图片");
		MessageBox(str);
		return;
	}

	// 垂直翻转图像
	Mat verticalflip_img = m_ImgProc.VerticalFlip(src_img);

	//显示图像
	CString str;
	str = _T("垂直翻转");
	SetDlgItemTextW(IDC_STATIC_ENHANCEIMG, str);
	showimg(verticalflip_img, enhance_img, rect3);

	//释放内存
	verticalflip_img.release();
}

//<----------------------------水平垂直翻转图像--------------------------------->
void CMFCDemoDlg::OnBnClickedButtonHorizontalverticalflip()
{
	// TODO: 在此添加控件通知处理程序代码
	if (src_img.empty())
	{
		CString str;
		str = _T("未读取图片");
		MessageBox(str);
		return;
	}

	//水平垂直翻转图像
	Mat horizontalverticalflip_img = m_ImgProc.HorizontalVerticalFlip(src_img);

	//显示图像
	CString str;
	str = _T("水平垂直翻转");
	SetDlgItemTextW(IDC_STATIC_ENHANCEIMG, str);
	showimg(horizontalverticalflip_img, enhance_img, rect3);


	//释放内存
	horizontalverticalflip_img.release();
}




//<----------------------------图像旋转90度--------------------------------->
void CMFCDemoDlg::OnBnClickedButtonRotate90()
{
	// TODO: 在此添加控件通知处理程序代码
	if (src_img.empty())
	{
		CString str;
		str = _T("未读取图片");
		MessageBox(str);
		return;
	}

	//图像旋转90度
	Mat rotate90_img = m_ImgProc.Rotate90(src_img);

	//显示图像
	CString str;
	str = _T("图像旋转90度");
	SetDlgItemTextW(IDC_STATIC_AFTERIMG, str);
	showimg(rotate90_img, after_img, rect2);


	//释放内存
	rotate90_img.release();
}

//<----------------------------图像旋转180度--------------------------------->
void CMFCDemoDlg::OnBnClickedButtonRotate180()
{
	// TODO: 在此添加控件通知处理程序代码
	if (src_img.empty())
	{
		CString str;
		str = _T("未读取图片");
		MessageBox(str);
		return;
	}

	//图像旋转180度
	Mat rotate180_img = m_ImgProc.Rotate180(src_img);

	//显示图像
	CString str;
	str = _T("图像旋转180度");
	SetDlgItemTextW(IDC_STATIC_ENHANCEIMG, str);
	showimg(rotate180_img, enhance_img, rect3);


	//释放内存
	rotate180_img.release();
}

//<----------------------------图像旋转270度--------------------------------->
void CMFCDemoDlg::OnBnClickedButtonRotate270()
{
	// TODO: 在此添加控件通知处理程序代码
	if (src_img.empty())
	{
		CString str;
		str = _T("未读取图片");
		MessageBox(str);
		return;
	}

	//图像旋转270度
	Mat rotate270_img = m_ImgProc.Rotate270(src_img);

	//显示图像
	CString str;
	str = _T("图像旋转270度");
	SetDlgItemTextW(IDC_STATIC_AFTERIMG, str);
	showimg(rotate270_img, after_img, rect2);


	//释放内存
	rotate270_img.release();
}




//<----------------------------修改图像大小--------------------------------->
void CMFCDemoDlg::OnBnClickedButtonResizeok()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Resizeheight = GetDlgItemInt(IDC_EDIT_RESIZEHEIGHT);
	m_Resizewidth = GetDlgItemInt(IDC_EDIT_RESIZEWIDTH);


	if (m_Resizeheight == 0 || m_Resizewidth == 0)
	{
		CString str;
		str = _T("请输入正确的宽高（整数）");
		MessageBox(str);
		return;
	}

	if (src_img.empty())
	{
		CString str;
		str = _T("未读取图片");
		MessageBox(str);
		return;
	}
	

	//图像改变尺寸
	Mat resize_img = m_ImgProc.ResizeImg(src_img, m_Resizewidth, m_Resizeheight);

	//显示图像
	CString str;
	str = _T("图像改变尺寸");
	SetDlgItemTextW(IDC_STATIC_AFTERIMG, str);
	showimg(resize_img, after_img, rect2);


	//释放内存
	resize_img.release();
}


//<----------------------------二值化图像反转--------------------------------->
void CMFCDemoDlg::OnBnClickedButtonBianryinv()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	if (src_img.empty())
	{
		CString str;
		str = _T("未读取图片");
		MessageBox(str);
		return;
	}

	if (gray_img.empty())
	{
		cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);
	}
	// 二值化图像反转
	Mat binaryinv_grayimg = m_ImgProc.BinaryInv(gray_img, m_lowSliderthreshold, m_highSliderthreshold);

	//显示图像
	CString str;
	str = _T("二值化反转");
	SetDlgItemTextW(IDC_STATIC_ENHANCEIMG, str);
	showimg(binaryinv_grayimg, enhance_img, rect3);

	//释放内存
	binaryinv_grayimg.release();
}







//<----------------------------比例缩放图像FX--------------------------------->
void CMFCDemoDlg::OnDeltaposSpinResizewidth(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (pNMUpDown->iDelta < 0)
	{
		m_ResizeFxwidth += 0.1f;
	}
	else if (pNMUpDown->iDelta > 0 && m_ResizeFxwidth > 0.1)
	{
		m_ResizeFxwidth -= 0.1f;
	}

	CString fx;
	fx.Format(_T("%.1f"), m_ResizeFxwidth);
	GetDlgItem(IDC_EDIT_RESIZEFX)->SetWindowText(fx);
	*pResult = 0;
}

//<----------------------------比例缩放图像FY--------------------------------->
void CMFCDemoDlg::OnDeltaposSpinResizeheight(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (pNMUpDown->iDelta < 0)
	{
		m_ResizeFyheight += 0.1f;
	}
	else if (pNMUpDown->iDelta > 0 && m_ResizeFyheight > 0.1)
	{
		m_ResizeFyheight -= 0.1f;
	}

	CString fy;
	fy.Format(_T("%.1f"), m_ResizeFyheight);
	GetDlgItem(IDC_EDIT_RESIZEFY)->SetWindowText(fy);
	*pResult = 0;
}

//<----------------------------图像缩放--------------------------------->
void CMFCDemoDlg::OnBnClickedButtonFxfyok()
{
	// TODO: 在此添加控件通知处理程序代码

	if (src_img.empty())
	{
		CString str;
		str = _T("未读取图片");
		MessageBox(str);
		return;
	}


	//图像缩放
	Mat scale_img = m_ImgProc.ScaleImg(src_img, m_ResizeFxwidth, m_ResizeFyheight);

	
	//显示图像
	CString str;
	str = _T("图像缩放");
	SetDlgItemTextW(IDC_STATIC_AFTERIMG, str);
	showimg(scale_img, after_img, rect2);


	//释放内存
	scale_img.release();
}

//<----------------------------形态学X内核大小--------------------------------->
void CMFCDemoDlg::OnDeltaposSpin3(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (pNMUpDown->iDelta < 0 &&  m_Morpkernelwidth < 200)
	{
		m_Morpkernelwidth += 1;
	}
	else if (pNMUpDown->iDelta > 0 && m_Morpkernelwidth >= 2)
	{
		m_Morpkernelwidth -= 1;
	}

	CString kernel;
	kernel.Format(_T("%d"), m_Morpkernelwidth);
	GetDlgItem(IDC_EDIT_MORPKERNELWIDTH)->SetWindowText(kernel);
	*pResult = 0;
}

//<----------------------------形态学Y内核大小--------------------------------->
void CMFCDemoDlg::OnDeltaposSpin4(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (pNMUpDown->iDelta < 0 && m_Morpkernelheight < 200)
	{
		m_Morpkernelheight += 1;
	}
	else if (pNMUpDown->iDelta > 0 && m_Morpkernelheight >= 2)
	{
		m_Morpkernelheight -= 1;
	}

	CString kernel;
	kernel.Format(_T("%d"), m_Morpkernelheight);
	GetDlgItem(IDC_EDIT_MORPKERNELHEIGHT)->SetWindowText(kernel);
	*pResult = 0;
}

//<----------------------------图像腐蚀--------------------------------->
void CMFCDemoDlg::OnBnClickedButtonErosion()
{
	// TODO: 在此添加控件通知处理程序代码
	if (src_img.empty())
	{
		CString str;
		str = _T("未读取图片");
		MessageBox(str);
		return;
	}

	//图像腐蚀
	Mat erosion_img = m_ImgProc.ErosionImg(src_img, m_Morpkernelwidth, m_Morpkernelheight);

	//显示图像
	CString str;
	str = _T("图像腐蚀");
	SetDlgItemTextW(IDC_STATIC_AFTERIMG, str);
	showimg(erosion_img, after_img, rect2);


	//释放内存
	erosion_img.release();
}

//<----------------------------图像膨胀--------------------------------->
void CMFCDemoDlg::OnBnClickedButtonDilation()
{
	// TODO: 在此添加控件通知处理程序代码
	if (src_img.empty())
	{
		CString str;
		str = _T("未读取图片");
		MessageBox(str);
		return;
	}

	//图像膨胀
	Mat dilation_img = m_ImgProc.DilationImg(src_img, m_Morpkernelwidth, m_Morpkernelheight);

	//显示图像
	CString str;
	str = _T("图像膨胀");
	SetDlgItemTextW(IDC_STATIC_ENHANCEIMG, str);
	showimg(dilation_img, enhance_img, rect3);

	//释放内存
	dilation_img.release();
}

//<----------------------------图像开运算--------------------------------->
void CMFCDemoDlg::OnBnClickedButtonMopopen()
{
	// TODO: 在此添加控件通知处理程序代码
	if (src_img.empty())
	{
		CString str;
		str = _T("未读取图片");
		MessageBox(str);
		return;
	}


	//图像开运算
	Mat open_img = m_ImgProc.MopOpenImg(src_img, m_Morpkernelwidth, m_Morpkernelheight);

	//显示图像
	CString str;
	str = _T("图像开运算");
	SetDlgItemTextW(IDC_STATIC_AFTERIMG, str);
	showimg(open_img, after_img, rect2);

	//释放内存
	open_img.release();
}

//<----------------------------图像闭运算--------------------------------->
void CMFCDemoDlg::OnBnClickedButtonMopclose()
{
	// TODO: 在此添加控件通知处理程序代码
	if (src_img.empty())
	{
		CString str;
		str = _T("未读取图片");
		MessageBox(str);
		return;
	}

	//图像闭运算
	Mat close_img = m_ImgProc.MopCloseImg(src_img, m_Morpkernelwidth, m_Morpkernelheight);

	//显示图像
	CString str;
	str = _T("图像闭运算");
	SetDlgItemTextW(IDC_STATIC_ENHANCEIMG, str);
	showimg(close_img, enhance_img, rect3);

	//释放内存
	close_img.release();
}

//<----------------------------图像反色--------------------------------->
void CMFCDemoDlg::OnBnClickedButtonReversecolor()
{
	// TODO: 在此添加控件通知处理程序代码
	if (src_img.empty())
	{
		CString str;
		str = _T("未读取图片");
		MessageBox(str);
		return;
	}

	//图像反色
	Mat reverse_img = m_ImgProc.Reversecolor(src_img);

	//显示图像
	CString str;
	str = _T("图像反色");
	SetDlgItemTextW(IDC_STATIC_ENHANCEIMG, str);
	showimg(reverse_img, enhance_img, rect3);

	//释放内存
	reverse_img.release();
}




// 图像锐化Factor调节按钮
void CMFCDemoDlg::OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (pNMUpDown->iDelta < 0 && m_empfactor < 20)
	{
		m_empfactor += 0.1f;
	}
	else if (pNMUpDown->iDelta > 0 && m_empfactor > 0.4)
	{
		m_empfactor -= 0.1f;
	}

	CString fy;
	fy.Format(_T("%.1f"), m_empfactor);
	GetDlgItem(IDC_EDIT_EMPFACTOR)->SetWindowText(fy);
	
	Mat emp_img = m_ImgProc.Emphasize(src_img, m_empkernelx, m_empkernely, m_empfactor);
	CString str;
	str = _T("图像锐化");
	SetDlgItemTextW(IDC_STATIC_AFTERIMG, str);
	showimg(emp_img, after_img, rect2);
	*pResult = 0;
}


void CMFCDemoDlg::OnDeltaposSpin2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (pNMUpDown->iDelta < 0 && m_binaryoffset < 50)
	{
		m_binaryoffset += 1;
	}
	else if (pNMUpDown->iDelta > 0 && m_binaryoffset >= 6)
	{
		m_binaryoffset -= 1;
	}

	CString offset;
	offset.Format(_T("%d"), m_binaryoffset);
	GetDlgItem(IDC_EDIT_DYNBINARYOFFSET)->SetWindowText(offset);
	*pResult = 0;
}

//<----------------------------均值二值化--------------------------------->
void CMFCDemoDlg::OnBnClickedButtonDynbinary()
{
	// TODO: 在此添加控件通知处理程序代码
	if (src_img.empty())
	{
		CString str;
		str = _T("未读取图片");
		MessageBox(str);
		return;
	}
	if (gray_img.empty())
	{
		cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);
	}
	//均值二值化
	Mat dynbinary_img = m_ImgProc.DynBinary(gray_img, m_Morpkernelwidth, m_Morpkernelheight, m_binaryoffset, 0);

	//显示图像
	CString str;
	str = _T("均值二值化");
	SetDlgItemTextW(IDC_STATIC_ENHANCEIMG, str);
	showimg(dynbinary_img, enhance_img, rect3);

	//释放内存
	dynbinary_img.release();
}


void CMFCDemoDlg::OnDeltaposSpin5(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (pNMUpDown->iDelta < 0 && m_imgalpha < 10)
	{
		m_imgalpha += 0.1;
	}
	else if (pNMUpDown->iDelta > 0 && m_imgalpha >= 0.1 )
	{
		m_imgalpha -= 0.1;
	}

	CString imgalpha;
	imgalpha.Format(_T("%.1f"), m_imgalpha);
	GetDlgItem(IDC_EDIT_LIGHTALPHA)->SetWindowText(imgalpha);
	*pResult = 0;

}


void CMFCDemoDlg::OnDeltaposSpin6(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (pNMUpDown->iDelta < 0 && m_imgbeta < 300)
	{
		m_imgbeta += 1;
	}
	else if (pNMUpDown->iDelta > 0 && m_imgbeta >= 1)
	{
		m_imgbeta -= 1;
	}

	SetDlgItemInt(IDC_EDIT_LIGHTBETA, m_imgbeta);
	*pResult = 0;
}


void CMFCDemoDlg::OnBnClickedButtonChangelight()
{
	// TODO: 在此添加控件通知处理程序代码
	if (src_img.empty())
	{
		CString str;
		str = _T("未读取图片");
		MessageBox(str);
		return;
	}

	//亮度改变
	Mat light_img = m_ImgProc.ChangeImgLight(src_img, m_imgalpha, m_imgbeta);

	//显示图像
	CString str;
	str = _T("亮度改变");
	SetDlgItemTextW(IDC_STATIC_ENHANCEIMG, str);
	showimg(light_img, enhance_img, rect3);

	//释放内存
	light_img.release();
}



