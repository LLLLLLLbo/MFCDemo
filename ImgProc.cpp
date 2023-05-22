#pragma once
#include "pch.h"
#include "ImgProc.h"

cv::Mat ImgProc::HistDraw(cv::Mat src_img)
{
	if (src_img.channels() != 1) 
	{
		std::vector<Mat> bgr_plane;
		split(src_img, bgr_plane);

		//��������
		const int channel[1] = { 0 };
		const int bins[1] = { 256 };
		float hranges[2] = { 0,255 };
		const float* ranges[1] = { hranges };
		Mat b_hist, g_hist, r_hist;

		//����B��G��Rͨ����ֱ��ͼ
		cv::calcHist(&bgr_plane[0], 1, 0, Mat(), b_hist, 1, bins, ranges);
		cv::calcHist(&bgr_plane[1], 1, 0, Mat(), g_hist, 1, bins, ranges);
		cv::calcHist(&bgr_plane[2], 1, 0, Mat(), r_hist, 1, bins, ranges);

		//��ʾֱ��ͼ
		int hist_w = 512, hist_h = 400;
		int bin_w = cvRound((double)hist_w / bins[0]);
		Mat hist_img = Mat::zeros(hist_h, hist_w, CV_8UC3);

		//��һ��ֱ��ͼ����
		cv::normalize(b_hist, b_hist, 0, hist_img.rows, NORM_MINMAX, -1, Mat());
		cv::normalize(g_hist, g_hist, 0, hist_img.rows, NORM_MINMAX, -1, Mat());
		cv::normalize(r_hist, r_hist, 0, hist_img.rows, NORM_MINMAX, -1, Mat());

		//����ֱ��ͼ����
		for (int i = 1; i < bins[0]; i++)
		{
			line(hist_img, Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
				Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);
			line(hist_img, Point(bin_w * (i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
				Point(bin_w * (i), hist_h - cvRound(g_hist.at<float>(i))), Scalar(0, 255, 0), 2, 8, 0);
			line(hist_img, Point(bin_w * (i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
				Point(bin_w * (i), hist_h - cvRound(r_hist.at<float>(i))), Scalar(0, 0, 255), 2, 8, 0);

		}

		return hist_img;
	}
	else if (src_img.channels() == 1) 
	{
		//����Ҷ�ֱ��ͼ
		const int channels[] = { 0 }; //ͨ���� �Ҷ�ͼΪ0
		Mat hist; //����Ҷ�ͼ
		int dims = 1; //ֱ��ͼά��
		const int histSize[] = { 256 }; //ÿ��ά�Ȼ��ֵ�������Ŀ
		float pranges[] = { 0 ,255 };
		const float* ranges[] = { pranges }; //ÿ��ά��ȡֵ����
		calcHist(&src_img, 1, channels, Mat(), hist, dims, histSize, ranges, true, false);

		//���ƻҶ�ֱ��ͼ
		int scale = 2;
		int hist_height = 256;
		Mat hist_img = Mat::zeros(hist_height, 256 * scale, CV_8UC3); //�ڵ�8λ3ͨ�� ��256 ��256 * 2
		double max_val;
		minMaxLoc(hist, 0, &max_val, 0, 0); //����ֱ��ͼ������Լ���С���ص�
		for (int i = 0; i < 256; i++)
		{
			float bin_val = hist.at<float>(i); //����histԪ�أ��������ͣ�
			int intensity = cvRound(bin_val * hist_height / max_val); //���Ƹ߶�
			rectangle(hist_img, Point(i * scale, hist_height - 1),
				Point((i + 1) * scale - 1, hist_height - intensity),
				Scalar(255, 255, 255));
		}

		return hist_img;
	}
}

cv::Mat ImgProc::HistBgrImg(cv::Mat src_img)
{
	return HistDraw(src_img);
}

cv::Mat ImgProc::Bgr2Gray(cv::Mat src_img)
{
	Mat gray_img;
	cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);
	return gray_img;
}

cv::Mat ImgProc::HistGrayImg(cv::Mat src_img)
{	
	return HistDraw(src_img);
}

cv::Mat ImgProc::EquaBgrImg(cv::Mat src_img)
{
	Mat img_bgr[3];
	Mat equa_img;
	split(src_img, img_bgr);
	for (int i = 0; i < 3; i++)
	{
		equalizeHist(img_bgr[i], img_bgr[i]);
	}
	merge(img_bgr, 3, equa_img);
	return equa_img;
}

cv::Mat ImgProc::EquaGrayImg(cv::Mat src_img)
{
	Mat equa_grayimg;
	equalizeHist(src_img, equa_grayimg);
	return equa_grayimg;
}

cv::Mat ImgProc::EquaImgHist(cv::Mat src_img)
{
	return HistDraw(EquaBgrImg(src_img));
}

cv::Mat ImgProc::EquaGrayImgHist(cv::Mat src_img)
{
	return HistDraw(EquaGrayImg(src_img));
}

cv::Mat ImgProc::BinaryBgrImg(cv::Mat src_img)
{
	Mat binary_img;
	cv::threshold(src_img, binary_img, 127, 255, cv::THRESH_BINARY);
	return binary_img;
}

cv::Mat ImgProc::BinaryGrayImg(cv::Mat src_img, int lowthreshold, int highthreshold)
{
	Mat binary_grayimg = cv::Mat::zeros(src_img.size(), src_img.type());
	for (int i = 0; i < src_img.rows; i++)
	{
		uchar* srcPt = (uchar*)src_img.data + i * src_img.step;
		uchar* dstPt = (uchar*)binary_grayimg.data + i * binary_grayimg.step;

		for (int j = 0; j < src_img.cols; j++)
		{
			uchar pixel = *srcPt++;
			if (pixel > lowthreshold && pixel < highthreshold)
				* dstPt = 255;
			dstPt++;
		}
	}
	return binary_grayimg;
}

cv::Mat ImgProc::BinaryInv(cv::Mat src_img, int lowthreshold, int highthreshold)
{
	Mat binaryinv_grayimg = cv::Mat::zeros(src_img.size(), src_img.type());
	for (int i = 0; i < src_img.rows; i++)
	{
		uchar* srcPt = (uchar*)src_img.data + i * src_img.step;
		uchar* dstPt = (uchar*)binaryinv_grayimg.data + i * binaryinv_grayimg.step;

		for (int j = 0; j < src_img.cols; j++)
		{
			uchar pixel = *srcPt++;
			if (pixel <= lowthreshold || pixel >= highthreshold)
				* dstPt = 255;
			dstPt++;
		}
	}
	return binaryinv_grayimg;
}

cv::Mat ImgProc::Ostu(cv::Mat src_img)
{
	Mat ostu_grayimg;
	cv::threshold(src_img, ostu_grayimg, 127, 255, cv::THRESH_OTSU);
	return ostu_grayimg;
}

cv::Mat ImgProc::Blur(cv::Mat src_img, int ksize)
{
	Mat blur_img;
	cv::blur(src_img, blur_img, Size(ksize, ksize));
	return blur_img;
}

cv::Mat ImgProc::MedianBlur(cv::Mat src_img, int ksize)
{
	Mat median_img;
	cv::medianBlur(src_img, median_img, ksize);
	return median_img;
}

cv::Mat ImgProc::GaussianBlur(cv::Mat src_img, int ksize)
{
	Mat gaussian_img;
	cv::GaussianBlur(src_img, gaussian_img, Size(ksize, ksize), 0.5, 0.5);
	return gaussian_img;
}

cv::Mat ImgProc::Sobel(cv::Mat src_img, int ksize)
{
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;
	Mat sobel_img;


	// x����
	cv::Sobel(src_img, grad_x, CV_16S, 1, 0, ksize);
	convertScaleAbs(grad_x, abs_grad_x);

	// y����
	cv::Sobel(src_img, grad_y, CV_16S, 0, 1, ksize);
	convertScaleAbs(grad_y, abs_grad_y);

	//�ϲ��ݶ�
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, sobel_img);

	return sobel_img;
}

cv::Mat ImgProc::Canny(cv::Mat src_img, int ksize)
{
	Mat dst_img;
	cv::Canny(src_img, dst_img, 80, 200, ksize);
	return dst_img;
}

cv::Mat ImgProc::Laplacian(cv::Mat src_img, int ksize)
{
	Mat gaussian_img, laplacian_img;
	//��˹�˲�
	gaussian_img = GaussianBlur(src_img, ksize);

	//Laplacian
	cv::Laplacian(gaussian_img, laplacian_img, CV_16S, 3);

	//�������ֵ��תΪ8λ
	cv::convertScaleAbs(laplacian_img, laplacian_img);

	return laplacian_img;
}

cv::Mat ImgProc::HorizontalFlip(cv::Mat src_img)
{
	Mat horizontal_img;
	cv::flip(src_img, horizontal_img, 1);
	return horizontal_img;
}

cv::Mat ImgProc::VerticalFlip(cv::Mat src_img)
{
	Mat vertical_img;
	cv::flip(src_img, vertical_img, 0);
	return vertical_img;
}

cv::Mat ImgProc::HorizontalVerticalFlip(Mat src_img)
{
	Mat vertical_img;
	cv::flip(src_img, vertical_img, -1);
	return vertical_img;
}

cv::Mat ImgProc::Rotate90(Mat src_img)
{
	Mat rotate90_img;
	cv::rotate(src_img, rotate90_img, ROTATE_90_CLOCKWISE);
	return rotate90_img;
}

cv::Mat ImgProc::Rotate180(Mat src_img)
{
	Mat rotate180_img;
	cv::rotate(src_img, rotate180_img, ROTATE_180);
	return rotate180_img;
}

cv::Mat ImgProc::Rotate270(Mat src_img)
{
	Mat rotate270_img;
	cv::rotate(src_img, rotate270_img, ROTATE_90_COUNTERCLOCKWISE);
	return rotate270_img;
}

cv::Mat ImgProc::ResizeImg(Mat src_img, int width, int height)
{
	Mat resize_img;
	int src_width = src_img.cols;
	int src_height = src_img.rows;
	if (width * height < src_width * src_height) 
	{
		cv::resize(src_img, resize_img, Size(width, height), 0, 0, cv::INTER_AREA);
	}
	else 
	{
		cv::resize(src_img, resize_img, Size(width, height), 0, 0, cv::INTER_CUBIC);
	}

	return resize_img;
}

cv::Mat ImgProc::ScaleImg(Mat src_img, float fx, float fy)
{
	Mat scale_img;
	cv::resize(src_img, scale_img, Size(0,0), fx, fy);
	return scale_img;
}

cv::Mat ImgProc::ErosionImg(Mat src_img, int x, int y)
{
	Mat erosion_img;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(x, y));
	erode(src_img, erosion_img, kernel);
	return erosion_img;
}

cv::Mat ImgProc::DilationImg(Mat src_img, int x, int y)
{
	Mat dilation_img;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(x, y));
	dilate(src_img, dilation_img, kernel);
	return dilation_img;
}

cv::Mat ImgProc::MopOpenImg(Mat src_img, int x, int y)
{
	Mat open_img;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(x, y));
	morphologyEx(src_img, open_img, CV_MOP_OPEN, kernel);
	return open_img;
}

cv::Mat ImgProc::MopCloseImg(Mat src_img, int x, int y)
{
	Mat close_img;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(x, y));
	morphologyEx(src_img, close_img, CV_MOP_CLOSE, kernel);
	return close_img;
}

cv::Mat ImgProc::Reversecolor(Mat src_img)
{
	Mat reverse_img;
	reverse_img.create(src_img.size(), src_img.type());
	int channels = src_img.channels();
	int height = src_img.rows, width = src_img.cols;
	
	if (channels == 3) 
	{
		int b, g, r;
		for (int row = 0; row < height; row++)
		{
			for (int col = 0; col < width; col++)
			{
				b = src_img.at<Vec3b>(row, col)[0];
				g = src_img.at<Vec3b>(row, col)[1];
				r = src_img.at<Vec3b>(row, col)[2];

				reverse_img.at<Vec3b>(row, col)[0] = 255 - b;
				reverse_img.at<Vec3b>(row, col)[1] = 255 - g;
				reverse_img.at<Vec3b>(row, col)[2] = 255 - r;
			}
		}
	}
	else if (channels == 1) 
	{
		for (int row = 0; row < height; row++)
		{
			for (int col = 0; col < width; col++)
			{
				int gray = src_img.at<uchar>(row, col);
				reverse_img.at<uchar>(row, col) = 255 - gray;
			}
		}
	}

	
	return reverse_img;
}

cv::Mat ImgProc::Emphasize(Mat src_img, int kernel_x, int kernel_y, float Factor)
{

	//��ʽres := round((orig - mean) * Factor) + orig
	//�ȼ�����MaskHeight��MaskWidth�Ŀռ������Ļ������ӷ���
	Mat mean;
	Mat emphasize_img;
	//�ȼ�����ָ����Χ�����ڵľ�ֵ
	cv::blur(src_img, mean, cv::Size(kernel_x, kernel_y));
	emphasize_img.create(src_img.size(), src_img.type());
	if (src_img.type() == CV_8UC1)
	{
		for (int i = 0; i < src_img.rows; i++)
		{
			const uchar* rptr = src_img.ptr<uchar>(i);
			uchar* mptr = mean.ptr<uchar>(i);
			uchar* optr = emphasize_img.ptr<uchar>(i);
			for (int j = 0; j < src_img.cols; j++)
			{
				optr[j] = cv::saturate_cast<uchar>(round((rptr[j] - mptr[j]) * Factor) + rptr[j] * 1.0f);
			}
		}
	}
	else if (src_img.type() == CV_8UC3)
	{
		for (int i = 0; i < src_img.rows; i++)
		{
			const uchar* rptr = src_img.ptr<uchar>(i);
			uchar* mptr = mean.ptr<uchar>(i);
			uchar* optr = emphasize_img.ptr<uchar>(i);
			for (int j = 0; j < src_img.cols; j++)
			{
				//����ת�� С��0��ֵ�ᱻ��Ϊ0 ����255��ֵ�ᱻ��Ϊ255
				optr[j * 3] = cv::saturate_cast<uchar>(round((rptr[j * 3] - mptr[j * 3]) * Factor) + rptr[j * 3] * 1.0f);
				optr[j * 3 + 1] = cv::saturate_cast<uchar>(round((rptr[j * 3 + 1] - mptr[j * 3 + 1]) * Factor) + rptr[j * 3 + 1] * 1.0f);
				optr[j * 3 + 2] = cv::saturate_cast<uchar>(round((rptr[j * 3 + 2] - mptr[j * 3 + 2]) * Factor) + rptr[j * 3 + 2] * 1.0f);
			}
		}
	}
	return emphasize_img;
}

cv::Mat ImgProc::DynBinary(Mat src_img, int kernel_x, int kernel_y, int offset, int mode)
{
	Mat mean_img;
	Mat dynbinary_img = Mat::zeros(src_img.size(), CV_8UC1);
	cv::blur(src_img, mean_img, Size(kernel_x, kernel_y));
	int value = 0;
	int r = src_img.rows, c = src_img.cols;
	for (int i = 0; i < r; i++) 
	{
		uchar* srcdata = src_img.ptr<uchar>(i);
		uchar* meandata = mean_img.ptr<uchar>(i);
		uchar* dyndata = dynbinary_img.ptr<uchar>(i);
		for (int j = 0; j < c; j++) 
		{
			switch (mode) 
			{
			case 0:
				value = srcdata[j] - meandata[j];
				if (value >= offset) 
				{
					dyndata[j] = 255;
				}
				break;
			case 1:
				value = meandata[j] - srcdata[j];
				if (value >= offset) 
				{
					dyndata[j] = 255;
				}
				break;
			case 2:
				value = srcdata[j] - meandata[j];
				if (value >= -offset && value <= offset) 
				{
					dyndata[j] = 255;
				}
				break;

			case 3:
				value = srcdata[j] - meandata[j];
				if (value < -offset || value > offset)
				{
					dyndata[j] = 255;
				}
				break;
			default:
				break;

			}
		}
	}
	return dynbinary_img;
}

cv::Mat ImgProc::ChangeImgLight(Mat src_img, float alpha, float beta)
{
	Mat dst_img;
	src_img.convertTo(dst_img, src_img.type(), alpha, beta);
	return dst_img;
}
