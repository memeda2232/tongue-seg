#include "stdafx.h"
#include <opencv2/core/core.hpp>          
#include <opencv2/highgui/highgui.hpp>          
#include <opencv2/imgproc/imgproc.hpp>         
#include <iostream>        
using namespace std;
using namespace cv;



int OTSU(Mat grayImage)
{
	int nRows = grayImage.rows;//行数
	int nCols = grayImage.cols;//列数	
	int threshold = 0;	//初始化阈值
						//------------【1】初始化统计参数------------
	int nSumPix[256];	//用于灰度级中每个像素在整幅图像中的个数
	float nProDis[256];	//用于记录每个灰度级占图像中的概率分布
	for (int i = 0; i < 256; i++)
	{
		nSumPix[i] = 0;
		nProDis[i] = 0;
	}
	//------------【2】统计灰度级中每个像素在整幅图像中的个数------------
	for (int i = 0; i < nRows; i++)
	{
		for (int j = 0; j < nCols; j++)
		{
			nSumPix[(int)grayImage.at<uchar>(i, j)]++;
		}
	}
	//------------【3】计算每个灰度级占图像中的概率分布------------
	for (int i = 0; i < 256; i++)
	{
		nProDis[i] = (float)nSumPix[i] / (nCols*nRows);
	}
	//------------【4】遍历灰度级[0,255]，计算出最大类间方差的阈值------------
	float wb, wf; //比重. wb-背景部分； wf-前景部分
	float u0_temp, u1_temp, u0, u1;	//平均值
	float delta_temp;	//存放临时方差
	double delta_max = 0.0;	//初始化最大类间方差
	for (int i = 0; i < 256; i++)
	{
		wb = wf = u0_temp = u1_temp = u0 = u1 = delta_temp = 0;//初始化相关参数
		for (int j = 0; j < 256; j++)
		{
			//背景部分
			if (j <= i)
			{
				//当前i为分割阈值，第一类总的概率
				wb += nProDis[j];	//比重
				u0_temp += j * nProDis[j];
			}
			//前景部分
			else
			{
				//当前i为分割阈值，第一类总的概率
				wf += nProDis[j];	//比重
				u1_temp += j * nProDis[j];
			}
		}
		//------------分别计算各类的平均值------------
		u0 = u0_temp / wb;
		u1 = u1_temp / wf;
		//-----------计算最大类间方差------------
		delta_temp = (float)(wb*wf*pow((u0 - u1), 2));//形如pow(x,y);其作用是计算x的y次方。
													  //------------依次找到最大类间方差下的阈值------------
		if (delta_temp > delta_max)
		{
			delta_max = delta_temp;
			threshold = i;
		}
	}//计算结束
	return threshold;	//返回OTUS计算出的阈值
}