// fusejiance.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<vector>
#include <photo\photo.hpp>

using namespace cv;
using namespace std;



Mat input_image;
Mat output_mask;
Mat output_image;
Mat mask;

void main()
{
	Mat input_image = imread("F:\\source\\舌头\\新建文件夹\\102501.bmp");

	/*椭圆皮肤模型*/
	Mat skinCrCbHist = Mat::zeros(Size(256, 256), CV_8UC1);
	ellipse(skinCrCbHist, Point(113, 155.6), Size(23.4, 15.2), 43.0, 0.0, 360.0, Scalar(255, 255, 255), -1);

	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));

		Mat ycrcb_image;
		output_mask = Mat::zeros(input_image.size(), CV_8UC1);
		cvtColor(input_image, ycrcb_image, CV_BGR2YCrCb); //首先转换成到YCrCb空间

		for (int i = 0; i < input_image.rows; i++) //利用椭圆皮肤模型进行皮肤检测
		{
			uchar* p = (uchar*)output_mask.ptr<uchar>(i);
			Vec3b* ycrcb = (Vec3b*)ycrcb_image.ptr<Vec3b>(i);
			for (int j = 0; j < input_image.cols; j++)
			{
				if (skinCrCbHist.at<uchar>(ycrcb[j][1], ycrcb[j][2]) > 0)
					p[j] = 255;
			}
		}

		morphologyEx(output_mask, output_mask, MORPH_CLOSE, element);


		vector< vector<Point> > contours;   // 轮廓   
		vector< vector<Point> > filterContours; // 筛选后的轮廓
		vector< Vec4i > hierarchy;    // 轮廓的结构信息 
		contours.clear();
		hierarchy.clear();
		filterContours.clear();

		findContours(output_mask, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
		// 去除伪轮廓 
		for (size_t i = 0; i < contours.size(); i++)
		{
			if (fabs(contourArea(Mat(contours[i]))) > 1000/*&&fabs(arcLength(Mat(contours[i]),true))<2000*/)  //判断手进入区域的阈值
				filterContours.push_back(contours[i]);
		}

		output_mask.setTo(0);
		drawContours(output_mask, filterContours, -1, Scalar(255, 0, 0), CV_FILLED); //8, hierarchy);   

		input_image.copyTo(output_image, output_mask);
		resize(output_image, output_image, Size(), 0.2, 0.2);
		imshow("input image", input_image);
		imshow("output image", output_image);

		output_image.setTo(0);
		resize(output_image, output_image, Size(), 0.2, 0.2);
		waitKey(0);
}

