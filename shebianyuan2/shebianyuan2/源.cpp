#include "stdafx.h"
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>

using namespace cv;
using namespace std;
//宏定义
#define WINDOW_NAME "image[procedure window]"

//全局变量声明
Mat g_srcImage, g_maskImage;
Point prevPt(-1, -1);

//全局函数声明
static void on_Mouse(int event, int x, int y, int flags, void*);

//主函数
int main()
{
	//载入源图像
	g_srcImage = imread("F:\\source\\102611.bmp");
	if (!g_srcImage.data) { printf("读取源图像srcImage错误～！\n"); return false; }

	//显示源图像
	imshow(WINDOW_NAME, g_srcImage);
	Mat srcImage, grayImage;
	g_srcImage.copyTo(srcImage);
	//灰度化
	cvtColor(srcImage, g_maskImage, COLOR_BGR2GRAY);
	//imshow("image[mask]",g_maskImage);
	cvtColor(g_maskImage, grayImage, COLOR_GRAY2BGR);
	//imshow("image[gray]",grayImage);
	//掩膜图像初始化为0
	g_maskImage = Scalar::all(0);

	//设置鼠标回调函数
	setMouseCallback(WINDOW_NAME, on_Mouse, 0);

	//轮询按键处理
	while (1)
	{
		//获取键值
		int c = waitKey(0);
		//若按键为ESC时，退出
		if ((char)c == 27)
			break;
		//若按键为2时，恢复原图
		if ((char)c == '2')
		{
			g_maskImage = Scalar::all(0);
			srcImage.copyTo(g_srcImage);
			imshow("image", g_srcImage);
		}
		//若按键为1,则进行处理
		if ((char)c == '1')
		{
			//定义一些参数
			int i, j, compCount = 0;
			vector<vector<Point>>contours;
			vector<Vec4i> hierarchy;
			//寻找轮廓
			findContours(g_maskImage, contours, hierarchy, CV_RETR_CCOMP, CHAIN_APPROX_SIMPLE);
			//轮廓为空时的处理
			if (contours.empty())
				continue;
			//复制掩膜
			Mat maskImage(g_maskImage.size(), CV_32S);
			maskImage = Scalar::all(0);

			//循环绘制轮廓
			for (int index = 0; index >= 0; index = hierarchy[index][0], ++compCount)
				drawContours(maskImage, contours, index, Scalar::all(compCount + 1), -1, 8, hierarchy, INT_MAX);
			//compCount为零时的处理
			if (compCount == 0)
				continue;

			//生成随机颜色
			vector<Vec3b>colorTab;
			for (int i = 0; i<compCount; ++i)
			{
				int b = theRNG().uniform(0, 255);
				int g = theRNG().uniform(0, 255);
				int r = theRNG().uniform(0, 255);

				colorTab.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
			}
			//计算处理时间并输出到窗口中
			double dTime = (double)getTickCount();
			//进行分水岭算法
			watershed(srcImage, maskImage);
			dTime = (double)getTickCount() - dTime;
			printf("\t 处理时间=%gms\n", dTime*1000. / getTickFrequency());
			//双层循环，将分水岭图像遍历存入watershedImage中
			Mat watershedImage(maskImage.size(), CV_8UC3);
			for (i = 0; i<maskImage.rows; ++i)
				for (j = 0; j<maskImage.cols; ++j)
				{
					int index = maskImage.at<int>(i, j);
					if (index == -1)
						watershedImage.at<Vec3b>(i, j) = Vec3b(255, 255, 255);//图像变白色
					else if (index <= 0 || index>compCount)
						watershedImage.at<Vec3b>(i, j) = Vec3b(0, 0, 0);//图像变黑色
					else
						watershedImage.at<Vec3b>(i, j) = colorTab[index - 1];
				}
			//混合灰度图和分水岭效果图并显示最终的窗口
			watershedImage = watershedImage * 0.5 + grayImage * 0.5;
			imshow("image[watershed]", watershedImage);
		}
	}
	return 0;
}

//回调函数定义
void on_Mouse(int event, int x, int y, int flags, void*)
{
	//处理鼠标不在窗口中的情况
	if (x<0 || x >= g_srcImage.cols || y<0 || y >= g_srcImage.rows)
		return;

	//处理鼠标左键相关消息
	if (event == EVENT_LBUTTONUP || !(flags & EVENT_FLAG_LBUTTON))//按下左键
		prevPt = Point(-1, -1);
	else if (event == EVENT_LBUTTONDOWN)//松开左键
		prevPt = Point(x, y);//鼠标所指的位置

							 //鼠标左键按下并移动，绘制出白色线条
	else if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON))
	{
		Point pt(x, y);
		if (prevPt.x<0)//如果指出去了，返回
			prevPt = pt;
		line(g_maskImage, prevPt, pt, Scalar::all(255), 2, 8, 0);//画白线
		line(g_srcImage, prevPt, pt, Scalar::all(255), 2, 8, 0);//画白线
		prevPt = pt;
		imshow(WINDOW_NAME, g_srcImage);

	}
}