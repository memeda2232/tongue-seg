// quyuzengzhang.cpp: 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<vector>
#include "quyu.h"
#include"otsu.h"
#include"fillhole.h"
using namespace cv;
using namespace std;


int main()
{

	Mat src, srcHLS, r, dstImage, liantong, liantong1, h, s,srcgray;
	int th = 30;
	Point2i pt = Point(950, 900);
	Point2i pt1 = Point(950, 700);
	Point2i pt2 = Point(650, 800);
	Point2i pt3 = Point(650, 1000);
	src = imread("F:\\source\\舌头\\新建文件夹\\102613.bmp");
	src = src(Rect(500, 150, 1500, 1750));
	cvtColor(src, srcHLS, COLOR_BGR2HLS);
	cvtColor(src, srcgray, COLOR_BGR2GRAY);
	//imshow("gray", srcgray);
	cvtColor(srcgray, srcgray, COLOR_GRAY2BGRA);
	imshow("bgr", srcgray);


	vector<Mat> channels;
	split(srcHLS, channels);
	r = channels.at(0);
	h = channels.at(1);
	s = channels.at(2);
	int yuzhi;

	yuzhi = OTSU(r);
	threshold(r, r, yuzhi, 255, 0);
	



	/*resize(r, r, Size(), 0.2, 0.2);
	imshow("r", r);*/
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
	Mat element1 = getStructuringElement(MORPH_RECT, Size(45, 45));
	Mat element3 = getStructuringElement(MORPH_RECT, Size(40, 40));
	Mat element4 = getStructuringElement(MORPH_RECT, Size(80, 80));
	/*dilate(r, r, element);
	morphologyEx(r, r, MORPH_CLOSE, element);*/
	
	erode(r, r, element);
	morphologyEx(r, r, MORPH_CLOSE, element1);
	dilate(r, r, element1);
	dilate(r, r, element1);
	dilate(r, r, element1);
	morphologyEx(r, r, MORPH_CLOSE, element4);
	morphologyEx(r, r, MORPH_CLOSE, element4);
	/*resize(r, r, Size(), 0.2, 0.2);
	imshow("r", r);*/
	erode(r, r, element3);
	erode(r, r, element3);
	erode(r, r, element3);
	src.copyTo(r, r);
	/*resize(r, r, Size(), 0.2, 0.2);
	imshow("r", r);*/
	Mat zuihou = RegionGrow(r, pt, th);
	Mat zuihou1 = RegionGrow(r, pt1, th);
	Mat zuihou2 = RegionGrow(r, pt2, th);
	Mat zuihou3 = RegionGrow(r, pt3, th);
	addWeighted(zuihou, 0.5, zuihou1, 0.5, 0, zuihou);
	addWeighted(zuihou, 0.5, zuihou2, 0.5, 0, zuihou);
	addWeighted(zuihou, 0.5, zuihou3, 0.5, 0, zuihou);
	morphologyEx(zuihou, zuihou, MORPH_CLOSE, element4);
	/*addWeighted(liantong, 0.5, liantong1, 0.5, 0, zuihou);*/
	my_imfillholes(zuihou);
	src.copyTo(zuihou, zuihou);
	//resize(zuihou, zuihou, Size(), 0.2, 0.2);
	//resize(src, src, Size(), 0.2, 0.2);
	//resize(r, r, Size(), 0.2, 0.2);
	//cvtColor(r, r, COLOR_BGR2GRAY);
	//cvtColor(zuihou, zuihou, COLOR_BGR2GRAY);
	//imshow("r", r);
	//imshow("saf",src);
	imshow("zuihou", zuihou);
	imwrite("F:\\source\\舌头\\新建文件夹\\样本\\102613_quyu.bmp", zuihou);
	waitKey(0);



}
