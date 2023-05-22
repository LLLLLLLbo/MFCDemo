#pragma once
using namespace cv;
class ImgProc 
{

public:
	//����ֱ��ͼ
	cv::Mat HistDraw(cv::Mat src_img);
	//bgrͼ��ֱ��ͼ
	cv::Mat HistBgrImg(cv::Mat src_img);
	//ͼ��ҶȻ�
	cv::Mat Bgr2Gray(cv::Mat src_img);
	//�Ҷ�ֱ��ͼ
	cv::Mat HistGrayImg(cv::Mat src_img);
	//bgrͼ����⻯
	cv::Mat EquaBgrImg(cv::Mat src_img);
	//�Ҷ�ͼ���⻯
	cv::Mat EquaGrayImg(cv::Mat src_img);
	//bgr���⻯ֱ��ͼ
	cv::Mat EquaImgHist(cv::Mat src_img);
	//�Ҷ�ͼ���⻯ֱ��ͼ
	cv::Mat EquaGrayImgHist(cv::Mat src_img);
	//bgrͼ���ֵ��
	cv::Mat BinaryBgrImg(cv::Mat src_img);
	//�Ҷ�ͼ��ֵ��
	cv::Mat BinaryGrayImg(cv::Mat src_img, int lowthreshold, int highthreshold);
	//��ֵ����ת
	cv::Mat BinaryInv(cv::Mat src_img, int lowthreshold, int highthreshold);
	//OSTU
	cv::Mat Ostu(cv::Mat src_img);
	//��ֵ�˲�
	cv::Mat Blur(cv::Mat src_img, int ksize);
	//��ֵ�˲�
	cv::Mat MedianBlur(cv::Mat src_img, int ksize);
	//��˹�˲�
	cv::Mat GaussianBlur(cv::Mat src_img, int ksize);
	//Sobel
	cv::Mat Sobel(cv::Mat src_img, int ksize);
	//Canny
	cv::Mat Canny(cv::Mat src_img, int ksize);
	//Laplacian
	cv::Mat Laplacian(cv::Mat src_img, int ksize);
	//ˮƽ��ת
	cv::Mat HorizontalFlip(cv::Mat src_img);
	//��ֱ��ת
	cv::Mat VerticalFlip(cv::Mat src_img);
	//ˮƽ��ֱ��ת
	cv::Mat HorizontalVerticalFlip(Mat src_img);
	//ͼ����ת90��
	cv::Mat Rotate90(Mat src_img);
	//ͼ����ת180��
	cv::Mat Rotate180(Mat src_img);
	//ͼ����ת270��
	cv::Mat Rotate270(Mat src_img);
	//�޸�ͼ��ߴ�
	cv::Mat ResizeImg(Mat src_img, int width, int height);
	//����������ͼ��
	cv::Mat ScaleImg(Mat src_img, float fx, float fy);
	//ͼ��ʴ
	cv::Mat ErosionImg(Mat src_img, int x, int y);
	//ͼ������
	cv::Mat DilationImg(Mat src_img, int x, int y);
	//ͼ������
	cv::Mat MopOpenImg(Mat src_img, int x, int y);
	//ͼ�������
	cv::Mat MopCloseImg(Mat src_img, int x, int y);
	//ͼ��ɫ
	cv::Mat Reversecolor(Mat src_img);
	//ͼ����
	cv::Mat Emphasize(Mat src_img, int kernel_x, int kernel_y, float Factor);
	//��ֵ��ֵ��
	cv::Mat DynBinary(Mat src_img, int kernel_x, int kernel_y, int offset, int mode);
	//���ȵ���
	cv::Mat ChangeImgLight(Mat src_img, float alpha, float beta);
};

