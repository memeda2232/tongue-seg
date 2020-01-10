
#include "stdafx.h"
#include <opencv2/core/core.hpp>          
#include <opencv2/highgui/highgui.hpp>          
#include <opencv2/imgproc/imgproc.hpp>         
#include <iostream>     
#include <vector>
using namespace std;
using namespace cv;
void my_imfillholes(Mat &src)
{
	// detect external contours
	//
	vector <vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(src, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	//
	// fill external contours
	//
	if (!contours.empty() && !hierarchy.empty())
	{
		for (int idx = 0; idx < contours.size(); idx++)
		{
			drawContours(src, contours, idx, Scalar::all(255), CV_FILLED, 8);
		}
	}
}
