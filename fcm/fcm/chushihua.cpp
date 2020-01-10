#include "stdafx.h"
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<vector>
#include <photo\photo.hpp>

using namespace cv;
using namespace std;
void chushihua(int cluster_n, int data_n, cv::OutputArray U)
{
	Mat u(cluster_n, data_n, CV_64FC1);
	randu(u, Scalar::all(0), Scalar::all(1));

	for (int i = 0; i < cluster_n;i++)
	{   
		double *data = u.ptr<double>(i);
		double  sum = 0;
		for (int j = 0; j < data_n; j++)
		{
			sum = data[j] + sum;
			
		}
		for (int j = 0; j < data_n; j++)
		{
			data[j] = data[j] / sum;
			
		}
	}
	u.copyTo(U);
}