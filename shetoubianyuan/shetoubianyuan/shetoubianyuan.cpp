// shetoubianyuan.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main()
{
	Mat srcImg, dstImg,cannyImg,gaojiecanny,gray,edge,gaosi,gaosihuidu,lapulasi,hou,lapu,xiufu,fanxiang,zui;
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	srcImg = imread("E:\\舌头\\image\\007a.png");
	imshow("yuanshitu", srcImg); 
	//
	//
	//resize(srcimg, dstimg, size(), 0.2, 0.2);
	//cannyimg = dstimg.clone();
	//vector<mat> channels;
	//split(dstimg, channels);
	//mat r = channels.at(2);
	//
	//for (int y = 0; y <dstimg.rows; y++)
	//{
	//	for (int x = 0; x < dstimg.cols; x++)
	//	{
	//		r.at<uchar>(y, x) = saturate_cast<uchar>(5 * (r.at<uchar>(y, x))-900);
	//	}
	//}
	//imshow("r", r);
	//canny(r, edge, 500, 300, 3);
	//watershed(dstimg, edge);
	//imshow("suolvetu", edge);
	///*imshow("haha", dstimg);
	//cout << x << endl;
	//cout << y << endl;
	//gaojiecanny.create(dstimg.size(), dstimg.type());*/
	///*cvtcolor(dstimg, gray, color_bgr2gray);*/
	///*vector<mat> channels;
	//split(gray, channels);
	//mat gray1 = channels.at(2);*/
 //	/*blur(gray, edge, size(3, 3));*/
	///*canny(edge, edge, 150, 100, 3);
	//imshow("edge1", edge);*/
	//mat element = getstructuringelement(morph_rect, size(10, 10));
	//mat element1 = getstructuringelement(morph_rect, size(60, 60));
	//dilate(edge, edge, element);
	//morphologyex(edge, edge, morph_close, element1);
	//erode(edge, edge, element);//腐蚀、膨胀 形态学运算
	//morphologyex(edge, edge, morph_close, element1);
	//dilate(edge, edge, element);
	//morphologyex(edge, edge, morph_close, element1);
	//dilate(edge, edge, element);
	//morphologyex(edge, edge, morph_close, element1);
	//dstimg.copyto(edge, edge);
	//imshow("edge", edge);
	//waitkey(0);

	
}

