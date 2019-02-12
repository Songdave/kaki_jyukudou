#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<imgproc/imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;
int main()
{
    Mat srcImage = imread("bushu19.jpg");
	
    Mat imageROI = srcImage(Rect(434, 99, 320, 150));


    namedWindow("【1】原画图");
	imshow("【1】原画图", imageROI);

	


	Mat gray;

	cvtColor(imageROI, gray, COLOR_BGR2GRAY);
	namedWindow("【2】灰度图");
	imshow("【2】灰度图", gray);

	Mat threshold;
	cv::threshold(gray, threshold, 132, 255, THRESH_BINARY);
	namedWindow("【3】二值图");
	imshow("【3】二值图", threshold);

	Mat medianfilter;

	medianBlur(threshold, medianfilter, 3);

	namedWindow("【4】中值滤波图");
	imshow("【4】中值滤波图", medianfilter);

	Mat change = medianfilter.clone();

	for (int i = 0; i < change.rows; i++) //二值图黑白对调
	{
		for (int j = 0; j < change.cols; j++)
		{
			if (change.at<uchar>(i, j) == 0)
				change.at<uchar>(i, j) = 1;
			else
				change.at<uchar>(i, j) = 0;
			
		}
	}

	int sum_x = 0, sum_y = 0, area = 0;
	for (int i = 0; i < change.rows; i++)//计算形心
	{
		for (int j = 0; j < change.cols; j++)
		{
			if (change.at<uchar>(i, j) == 0)
			{
				sum_x = sum_x + j;
				sum_y = sum_y + i;
				area = area + 1;
			}
		}
	}
	int x0 = sum_x / area;//形心坐标
	int y0 = sum_y / area;

	cout << "x0 = " << x0 << endl;
	cout << "y0 = " << y0 << endl;

	Point cpoing;
	cpoing.x = x0;
	cpoing.y = y0;

	Mat centerpoint = imageROI.clone();
	circle(centerpoint, cpoing, 6, Scalar(0, 0, 255));

	namedWindow("【4.5】中值滤波图形心");
	imshow("【4.5】中值滤波图形心", centerpoint);

	





	Mat dstImage = imageROI.clone();

	for (int y = 0; y < dstImage.rows; y++)
	{
		for (int x = 0; x < dstImage.cols; x++)
		{
			if (medianfilter.at<uchar>(y, x) == 0 )
			{

				for (int c = 0; c < 3; c++)
				{
					dstImage.at<Vec3b>(y, x)[c] = 0;
				}
				
			}
		}
	}


	namedWindow("【5】去背景");
	imshow("【5】去背景", dstImage);


	//截取形心点周围圆形区域
	Mat image = dstImage.clone();
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat mask = Mat::zeros(image.size(), CV_8U);

	Point circleCenter(x0+10, y0+25);
	int radius = 30;
	// 画圆
	circle(mask, circleCenter, radius, Scalar(255), -1);

	image.copyTo(dst, mask);

	imshow("mask", mask);
	imshow("image", image);
	imshow("dst", dst);

	//输出结果图
	imwrite("bushu19dst.jpg", dst);

		


	waitKey(0);

	return 0;
}
