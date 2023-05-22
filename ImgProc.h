#pragma once
using namespace cv;
class ImgProc 
{

public:
	//绘制直方图
	cv::Mat HistDraw(cv::Mat src_img);
	//bgr图像直方图
	cv::Mat HistBgrImg(cv::Mat src_img);
	//图像灰度化
	cv::Mat Bgr2Gray(cv::Mat src_img);
	//灰度直方图
	cv::Mat HistGrayImg(cv::Mat src_img);
	//bgr图像均衡化
	cv::Mat EquaBgrImg(cv::Mat src_img);
	//灰度图均衡化
	cv::Mat EquaGrayImg(cv::Mat src_img);
	//bgr均衡化直方图
	cv::Mat EquaImgHist(cv::Mat src_img);
	//灰度图均衡化直方图
	cv::Mat EquaGrayImgHist(cv::Mat src_img);
	//bgr图像二值化
	cv::Mat BinaryBgrImg(cv::Mat src_img);
	//灰度图二值化
	cv::Mat BinaryGrayImg(cv::Mat src_img, int lowthreshold, int highthreshold);
	//二值化翻转
	cv::Mat BinaryInv(cv::Mat src_img, int lowthreshold, int highthreshold);
	//OSTU
	cv::Mat Ostu(cv::Mat src_img);
	//均值滤波
	cv::Mat Blur(cv::Mat src_img, int ksize);
	//中值滤波
	cv::Mat MedianBlur(cv::Mat src_img, int ksize);
	//高斯滤波
	cv::Mat GaussianBlur(cv::Mat src_img, int ksize);
	//Sobel
	cv::Mat Sobel(cv::Mat src_img, int ksize);
	//Canny
	cv::Mat Canny(cv::Mat src_img, int ksize);
	//Laplacian
	cv::Mat Laplacian(cv::Mat src_img, int ksize);
	//水平翻转
	cv::Mat HorizontalFlip(cv::Mat src_img);
	//垂直翻转
	cv::Mat VerticalFlip(cv::Mat src_img);
	//水平垂直翻转
	cv::Mat HorizontalVerticalFlip(Mat src_img);
	//图像旋转90度
	cv::Mat Rotate90(Mat src_img);
	//图像旋转180度
	cv::Mat Rotate180(Mat src_img);
	//图像旋转270度
	cv::Mat Rotate270(Mat src_img);
	//修改图像尺寸
	cv::Mat ResizeImg(Mat src_img, int width, int height);
	//按比例缩放图像
	cv::Mat ScaleImg(Mat src_img, float fx, float fy);
	//图像腐蚀
	cv::Mat ErosionImg(Mat src_img, int x, int y);
	//图像膨胀
	cv::Mat DilationImg(Mat src_img, int x, int y);
	//图像开运算
	cv::Mat MopOpenImg(Mat src_img, int x, int y);
	//图像闭运算
	cv::Mat MopCloseImg(Mat src_img, int x, int y);
	//图像反色
	cv::Mat Reversecolor(Mat src_img);
	//图像锐化
	cv::Mat Emphasize(Mat src_img, int kernel_x, int kernel_y, float Factor);
	//均值二值化
	cv::Mat DynBinary(Mat src_img, int kernel_x, int kernel_y, int offset, int mode);
	//亮度调节
	cv::Mat ChangeImgLight(Mat src_img, float alpha, float beta);
};

