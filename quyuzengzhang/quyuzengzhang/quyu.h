#pragma once
#include "stdafx.h"
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<vector>

using namespace cv;
using namespace std;
Mat RegionGrow(Mat src, Point2i pt, int th);