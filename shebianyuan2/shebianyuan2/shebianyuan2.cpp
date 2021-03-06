// shebianyuan2.cpp: 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <photo\photo.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat srcImg, dstImg, cannyImg,gaosi,gaosihuidu,lapulasi,hou;
	vector<vector<Point>> outputcon;

	vector<Vec4i> hiera;
	RNG g_rng(12345);
	srcImg = imread("F:\\source\\102619.bmp");
	resize(srcImg, dstImg, Size(), 0.2, 0.2);
	imshow("yuanshitu", dstImg);
	GaussianBlur(dstImg, gaosi, Size(3, 3), 0, 0, BORDER_DEFAULT);
	cvtColor(gaosi, gaosihuidu, COLOR_RGB2GRAY);
	//Laplacian(gaosihuidu, lapulasi, CV_16S, 3, 1, 0, BORDER_DEFAULT);
	Canny(dstImg, cannyImg, 150, 200, 3);
	imshow("cannyImg", cannyImg);
	/*convertScaleAbs(lapulasi, hou);
	threshold(hou, hou, 20, 255, 0);
	imshow("lapulasi", hou);*/

	findContours(cannyImg, outputcon, hiera, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
	Mat drawing = Mat::zeros(cannyImg.size(), CV_8UC3);
	for (int i = 0; i < outputcon.size(); i++)
	{
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255) );
		drawContours(drawing, outputcon, i, color, 2, 8, hiera, 0, Point());
		
	}
	imshow("lunkuo", drawing);
	waitKey(0);
}

