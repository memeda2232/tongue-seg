// fcm.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<vector>
#include <photo\photo.hpp>
#include"chushihua.h"
#include"julei.h"
#include"quyuzengzhang.h"
#include"fillhole.h"
using namespace cv;
using namespace std;
int main()
{
	Mat src,src0, srcHLS;
	src0 = imread("F:\\source\\舌头\\新建文件夹\\102603.bmp");
	src0 = src0(Rect(500, 150, 1500, 1750));
	cvtColor(src0, src, COLOR_BGR2GRAY);
	src.convertTo(src,CV_64FC1);
	/*imshow("src",src);
	cout << "src" << src << endl;*/
	/*waitKey(0);*/
	Mat ceshi = (Mat_<double>(1, 3) << 1, 10, 100);
	int m = src.rows;
	int n = src.cols;
	int data = m * n;
    int  leishu = 2;
	int cifang =10;
	int cishu = 0;
	int zuidacishu = 100;
    double zuixiaozhi = 0.01;
	double J0 = 0;

	Mat u, mf, dst;
	chushihua(data, leishu, u);
	int k = 0;

	
	dst.create(1, data, src.type());//记录数据矩阵
	double *q = dst.ptr<double>(0);
	for (int i = 0; i < src.rows; i++)
	{
		double *p = src.ptr<double>(i);
		;
		for (int j = 0; j < src.cols; j++)
		{
			q[k] = p[j];
			k++;
		}
	}
	//将数据矩阵提取
	
	double chazhi;
	while (cishu < zuidacishu)
	{
		double J = julei(leishu, cifang, data, u,dst);
	    chazhi =fabs( J - J0);
		if (chazhi < zuixiaozhi)
		{
			break;
		}
		else
		{
			J0 = J;
		}
		
		
		cishu++;
	}
	Mat lei;
	lei.create(data, 1, CV_8UC1);
	for (int i = 0; i < data; i++)
	{
		uchar *a = lei.ptr<uchar>(i);
		double *b = u.ptr<double>(i);
		double max = 0;
		uchar fenlei = 0;
		for(int j=0;j<leishu;j++)
		{
			if (b[j] > max)
			{
				fenlei = j;
				max = b[j];
			}
			else
			{
			}
		}
		a[0] = fenlei;
	}
	
	Mat zuihou;
	zuihou.create(src.rows, src.cols, CV_8UC1);
	int p = 0;
	
	
	for (int i = 0; i < src.rows; i++)
	{
		uchar *c = zuihou.ptr<uchar>(i);
		for (int j = 0; j < src.cols; j++)
		{
			uchar *a = lei.ptr<uchar>(p);
			if (a[0] == 0)
			{
				c[j] = 255;
			}
			else if (a[0] == 1)
			{
				c[j] = 0;
			}
			else if (a[0]==2)
			{
				c[j] = 150;
			}
			else if (a[0] == 3)
			{
				c[j] = 100;
			}
			else if (a[0] == 4)
			{
				c[j] = 50;
			}
			else if (a[0] == 5)
			{
				c[j] = 0;
			}
			p++;
		}
	}
	
	
	/*cout << lei << endl;
	cout << "cishu" << cishu;
	cout << "chazhi" <<chazhi;*/
	/*cout << zuihou << endl;*/
	/*zuihou.convertTo(zuihou,CV_8UC1);*/
	Point2i pt = Point(780, 550);
	Point2i pt1 = Point(500, 730);
	Point2i pt2 = Point(780, 950);
	Point2i pt3 = Point(1000, 730);
	Mat element = getStructuringElement(MORPH_RECT, Size(60, 60));
	int th = 50;
 zuihou = RegionGrow(zuihou, pt, th);
 my_imfillholes(zuihou);
 dilate(zuihou, zuihou, element);
 imshow("1", zuihou);

	src0.copyTo(zuihou, zuihou);
	imshow("src0", zuihou);
	vector<Mat> channels;
	cvtColor(zuihou, srcHLS, COLOR_BGR2HLS);
	split(srcHLS, channels);
	Mat r = channels.at(0);
	 zuihou = RegionGrow(r, pt, th);
	Mat zuihou1 = RegionGrow(r, pt1, th);
	Mat zuihou2 = RegionGrow(r, pt2, th);
	Mat zuihou3 = RegionGrow(r, pt3, th);
	
	addWeighted(zuihou, 0.5, zuihou1, 0.5, 0, zuihou);
	addWeighted(zuihou, 0.5, zuihou2, 0.5, 0, zuihou);
	addWeighted(zuihou, 0.5, zuihou3, 0.5, 0, zuihou);
	imshow("2", zuihou);
	
	
	/*morphologyEx(r, r, MORPH_CLOSE, element);
	morphologyEx(r, r, MORPH_CLOSE, element);
	morphologyEx(r, r, MORPH_CLOSE, element);
	dilate(r, r, element);
	dilate(r, r, element);
	dilate(r, r, element);
	my_imfillholes(r);*/
	my_imfillholes(zuihou);
	Mat element1 = getStructuringElement(MORPH_RECT, Size(10, 10));
	erode(zuihou, zuihou, element1);
	src0.copyTo(zuihou, zuihou);
	resize(zuihou, zuihou, Size(), 0.2, 0.2);
	imshow("zuihou",zuihou);
	waitKey(0);
	
}

