#include "stdafx.h"
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>

using namespace cv;
using namespace std;
//�궨��
#define WINDOW_NAME "image[procedure window]"

//ȫ�ֱ�������
Mat g_srcImage, g_maskImage;
Point prevPt(-1, -1);

//ȫ�ֺ�������
static void on_Mouse(int event, int x, int y, int flags, void*);

//������
int main()
{
	//����Դͼ��
	g_srcImage = imread("F:\\source\\102611.bmp");
	if (!g_srcImage.data) { printf("��ȡԴͼ��srcImage���󡫣�\n"); return false; }

	//��ʾԴͼ��
	imshow(WINDOW_NAME, g_srcImage);
	Mat srcImage, grayImage;
	g_srcImage.copyTo(srcImage);
	//�ҶȻ�
	cvtColor(srcImage, g_maskImage, COLOR_BGR2GRAY);
	//imshow("image[mask]",g_maskImage);
	cvtColor(g_maskImage, grayImage, COLOR_GRAY2BGR);
	//imshow("image[gray]",grayImage);
	//��Ĥͼ���ʼ��Ϊ0
	g_maskImage = Scalar::all(0);

	//�������ص�����
	setMouseCallback(WINDOW_NAME, on_Mouse, 0);

	//��ѯ��������
	while (1)
	{
		//��ȡ��ֵ
		int c = waitKey(0);
		//������ΪESCʱ���˳�
		if ((char)c == 27)
			break;
		//������Ϊ2ʱ���ָ�ԭͼ
		if ((char)c == '2')
		{
			g_maskImage = Scalar::all(0);
			srcImage.copyTo(g_srcImage);
			imshow("image", g_srcImage);
		}
		//������Ϊ1,����д���
		if ((char)c == '1')
		{
			//����һЩ����
			int i, j, compCount = 0;
			vector<vector<Point>>contours;
			vector<Vec4i> hierarchy;
			//Ѱ������
			findContours(g_maskImage, contours, hierarchy, CV_RETR_CCOMP, CHAIN_APPROX_SIMPLE);
			//����Ϊ��ʱ�Ĵ���
			if (contours.empty())
				continue;
			//������Ĥ
			Mat maskImage(g_maskImage.size(), CV_32S);
			maskImage = Scalar::all(0);

			//ѭ����������
			for (int index = 0; index >= 0; index = hierarchy[index][0], ++compCount)
				drawContours(maskImage, contours, index, Scalar::all(compCount + 1), -1, 8, hierarchy, INT_MAX);
			//compCountΪ��ʱ�Ĵ���
			if (compCount == 0)
				continue;

			//���������ɫ
			vector<Vec3b>colorTab;
			for (int i = 0; i<compCount; ++i)
			{
				int b = theRNG().uniform(0, 255);
				int g = theRNG().uniform(0, 255);
				int r = theRNG().uniform(0, 255);

				colorTab.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
			}
			//���㴦��ʱ�䲢�����������
			double dTime = (double)getTickCount();
			//���з�ˮ���㷨
			watershed(srcImage, maskImage);
			dTime = (double)getTickCount() - dTime;
			printf("\t ����ʱ��=%gms\n", dTime*1000. / getTickFrequency());
			//˫��ѭ��������ˮ��ͼ���������watershedImage��
			Mat watershedImage(maskImage.size(), CV_8UC3);
			for (i = 0; i<maskImage.rows; ++i)
				for (j = 0; j<maskImage.cols; ++j)
				{
					int index = maskImage.at<int>(i, j);
					if (index == -1)
						watershedImage.at<Vec3b>(i, j) = Vec3b(255, 255, 255);//ͼ����ɫ
					else if (index <= 0 || index>compCount)
						watershedImage.at<Vec3b>(i, j) = Vec3b(0, 0, 0);//ͼ����ɫ
					else
						watershedImage.at<Vec3b>(i, j) = colorTab[index - 1];
				}
			//��ϻҶ�ͼ�ͷ�ˮ��Ч��ͼ����ʾ���յĴ���
			watershedImage = watershedImage * 0.5 + grayImage * 0.5;
			imshow("image[watershed]", watershedImage);
		}
	}
	return 0;
}

//�ص���������
void on_Mouse(int event, int x, int y, int flags, void*)
{
	//������겻�ڴ����е����
	if (x<0 || x >= g_srcImage.cols || y<0 || y >= g_srcImage.rows)
		return;

	//���������������Ϣ
	if (event == EVENT_LBUTTONUP || !(flags & EVENT_FLAG_LBUTTON))//�������
		prevPt = Point(-1, -1);
	else if (event == EVENT_LBUTTONDOWN)//�ɿ����
		prevPt = Point(x, y);//�����ָ��λ��

							 //���������²��ƶ������Ƴ���ɫ����
	else if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON))
	{
		Point pt(x, y);
		if (prevPt.x<0)//���ָ��ȥ�ˣ�����
			prevPt = pt;
		line(g_maskImage, prevPt, pt, Scalar::all(255), 2, 8, 0);//������
		line(g_srcImage, prevPt, pt, Scalar::all(255), 2, 8, 0);//������
		prevPt = pt;
		imshow(WINDOW_NAME, g_srcImage);

	}
}