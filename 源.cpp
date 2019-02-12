#include <opencv2/opencv.hpp>
#include<vector>
#include <fstream>

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{


	//从文件中读入图像
	Mat img = imread("bushu19dst.jpg");
	ofstream outfileg("g.txt");

	//如果读入图像失败


	
	int  cPointG;//currentPoint;
	for (int i = 1; i < img.rows; i++)
	{
		for (int j = 1; j < img.cols; j++)
		{
			
			cPointG = img.at<Vec3b>(i, j)[1];
			

			if (cPointG != 0)
			{
				
				outfileg << cPointG << endl;
				
			}
		}
		outfileg << endl;
	}

	ofstream outfileb("b.txt");

	
	int cPointB;//currentPoint;
	for (int i = 1; i < img.rows; i++)
	{
		for (int j = 1; j < img.cols; j++)
		{
			cPointB = img.at<Vec3b>(i, j)[0];
			

			if (cPointB != 0)
			{

				outfileb << cPointB << endl;

			}
		}
		outfileb << endl;
	}

	ofstream outfiler("r.txt");

	
	int cPointR;//currentPoint;
	for (int i = 1; i < img.rows; i++)
	{
		for (int j = 1; j < img.cols; j++)
		{
			
			cPointR = img.at<Vec3b>(i, j)[2];

			if (cPointR != 0)
			{

				outfiler << cPointR << endl;

			}
		}
		outfiler << endl;
	}


	//显示图像
	imshow("image", img);

	//此函数等待按键，按键盘任意键就返回
	waitKey();

	return 0;
}