#include "stdafx.h"
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<vector>
#include <photo\photo.hpp>
using namespace cv;
using namespace std;


Mat RegionGrow(Mat src1, Point2i pt, int th)
{
	Mat src;
	src = src1;
	Point2i ptGrowing;						//��������λ��
	int nGrowLable = 0;								//����Ƿ�������
	int nSrcValue = 0;								//�������Ҷ�ֵ
	int nCurValue = 0;	//��ǰ������Ҷ�ֵ
	Mat matDst = Mat::zeros(src.size(), CV_8UC1);	//����һ���հ��������Ϊ��ɫ
													//��������˳������
	int DIR[8][2] = { { -1,-1 },{ 0,-1 },{ 1,-1 },{ 1,0 },{ 1,1 },{ 0,1 },{ -1,1 },{ -1,0 } };
	int sum = 1;
	vector<Point2i> vcGrowPt;						//������ջ
	vcGrowPt.push_back(pt);							//��������ѹ��ջ��
	matDst.at<uchar>(pt.y, pt.x) = 255;				//���������
	nSrcValue = src.at<uchar>(pt.y, pt.x);			//��¼������ĻҶ�ֵ

	int x = pt.x, y = pt.y;//��¼��ʼ������
	while (!vcGrowPt.empty())						//����ջ��Ϊ��������
	{
		pt = vcGrowPt.back();						//ȡ��һ��������
		vcGrowPt.pop_back();
		//�ֱ�԰˸������ϵĵ��������
		for (int i = 0; i < 9; ++i)
		{
			ptGrowing.x = pt.x + DIR[i][0];
			ptGrowing.y = pt.y + DIR[i][1];
			//����Ƿ��Ǳ�Ե��
			if (ptGrowing.x < 0 || ptGrowing.y < 0 || ptGrowing.x >(src.cols - 1) || (ptGrowing.y > src.rows - 1))
				continue;

			nGrowLable = matDst.at<uchar>(ptGrowing.y, ptGrowing.x);		//��ǰ��������ĻҶ�ֵ

			if (nGrowLable == 0)					//�����ǵ㻹û�б�����
			{
				nCurValue = src.at<uchar>(ptGrowing.y, ptGrowing.x);
				float  m = 1 / ((float)((x - ptGrowing.x) ^ 2) / 750 + 1);
				float  n = 1 / ((float)((y - ptGrowing.y) ^ 2) / 700 + 1);
				if ((abs(nSrcValue - nCurValue) < th) && (abs(nSrcValue - nCurValue) < th))					//����ֵ��Χ��������
				{
			
				
					matDst.at<uchar>(ptGrowing.y, ptGrowing.x) = 255;
					//���Ϊ��ɫ

					vcGrowPt.push_back(ptGrowing);					//����һ��������ѹ��ջ��
				}
			}
		}

	}
	return matDst.clone();
}