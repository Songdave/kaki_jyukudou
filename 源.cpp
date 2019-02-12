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


    namedWindow("��1��ԭ��ͼ");
	imshow("��1��ԭ��ͼ", imageROI);

	


	Mat gray;

	cvtColor(imageROI, gray, COLOR_BGR2GRAY);
	namedWindow("��2���Ҷ�ͼ");
	imshow("��2���Ҷ�ͼ", gray);

	Mat threshold;
	cv::threshold(gray, threshold, 132, 255, THRESH_BINARY);
	namedWindow("��3����ֵͼ");
	imshow("��3����ֵͼ", threshold);

	Mat medianfilter;

	medianBlur(threshold, medianfilter, 3);

	namedWindow("��4����ֵ�˲�ͼ");
	imshow("��4����ֵ�˲�ͼ", medianfilter);

	Mat change = medianfilter.clone();

	for (int i = 0; i < change.rows; i++) //��ֵͼ�ڰ׶Ե�
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
	for (int i = 0; i < change.rows; i++)//��������
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
	int x0 = sum_x / area;//��������
	int y0 = sum_y / area;

	cout << "x0 = " << x0 << endl;
	cout << "y0 = " << y0 << endl;

	Point cpoing;
	cpoing.x = x0;
	cpoing.y = y0;

	Mat centerpoint = imageROI.clone();
	circle(centerpoint, cpoing, 6, Scalar(0, 0, 255));

	namedWindow("��4.5����ֵ�˲�ͼ����");
	imshow("��4.5����ֵ�˲�ͼ����", centerpoint);

	





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


	namedWindow("��5��ȥ����");
	imshow("��5��ȥ����", dstImage);


	//��ȡ���ĵ���ΧԲ������
	Mat image = dstImage.clone();
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat mask = Mat::zeros(image.size(), CV_8U);

	Point circleCenter(x0+10, y0+25);
	int radius = 30;
	// ��Բ
	circle(mask, circleCenter, radius, Scalar(255), -1);

	image.copyTo(dst, mask);

	imshow("mask", mask);
	imshow("image", image);
	imshow("dst", dst);

	//������ͼ
	imwrite("bushu19dst.jpg", dst);

		


	waitKey(0);

	return 0;
}
