#include "stdafx.h"
#include <opencv2/core/core.hpp>          
#include <opencv2/highgui/highgui.hpp>          
#include <opencv2/imgproc/imgproc.hpp>         
#include <iostream>        
using namespace std;
using namespace cv;



int OTSU(Mat grayImage)
{
	int nRows = grayImage.rows;//����
	int nCols = grayImage.cols;//����	
	int threshold = 0;	//��ʼ����ֵ
						//------------��1����ʼ��ͳ�Ʋ���------------
	int nSumPix[256];	//���ڻҶȼ���ÿ������������ͼ���еĸ���
	float nProDis[256];	//���ڼ�¼ÿ���Ҷȼ�ռͼ���еĸ��ʷֲ�
	for (int i = 0; i < 256; i++)
	{
		nSumPix[i] = 0;
		nProDis[i] = 0;
	}
	//------------��2��ͳ�ƻҶȼ���ÿ������������ͼ���еĸ���------------
	for (int i = 0; i < nRows; i++)
	{
		for (int j = 0; j < nCols; j++)
		{
			nSumPix[(int)grayImage.at<uchar>(i, j)]++;
		}
	}
	//------------��3������ÿ���Ҷȼ�ռͼ���еĸ��ʷֲ�------------
	for (int i = 0; i < 256; i++)
	{
		nProDis[i] = (float)nSumPix[i] / (nCols*nRows);
	}
	//------------��4�������Ҷȼ�[0,255]������������䷽�����ֵ------------
	float wb, wf; //����. wb-�������֣� wf-ǰ������
	float u0_temp, u1_temp, u0, u1;	//ƽ��ֵ
	float delta_temp;	//�����ʱ����
	double delta_max = 0.0;	//��ʼ�������䷽��
	for (int i = 0; i < 256; i++)
	{
		wb = wf = u0_temp = u1_temp = u0 = u1 = delta_temp = 0;//��ʼ����ز���
		for (int j = 0; j < 256; j++)
		{
			//��������
			if (j <= i)
			{
				//��ǰiΪ�ָ���ֵ����һ���ܵĸ���
				wb += nProDis[j];	//����
				u0_temp += j * nProDis[j];
			}
			//ǰ������
			else
			{
				//��ǰiΪ�ָ���ֵ����һ���ܵĸ���
				wf += nProDis[j];	//����
				u1_temp += j * nProDis[j];
			}
		}
		//------------�ֱ��������ƽ��ֵ------------
		u0 = u0_temp / wb;
		u1 = u1_temp / wf;
		//-----------���������䷽��------------
		delta_temp = (float)(wb*wf*pow((u0 - u1), 2));//����pow(x,y);�������Ǽ���x��y�η���
													  //------------�����ҵ������䷽���µ���ֵ------------
		if (delta_temp > delta_max)
		{
			delta_max = delta_temp;
			threshold = i;
		}
	}//�������
	return threshold;	//����OTUS���������ֵ
}