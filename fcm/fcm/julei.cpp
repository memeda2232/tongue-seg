#include "stdafx.h"
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<vector>
#include <photo\photo.hpp>

using namespace cv;
using namespace std;




double julei(int leishu, int cifang, int data, Mat &u,Mat& dst)
{
	Mat fenzi,mf;
	fenzi.create(1, leishu, u.type());
	pow(u, cifang, mf);
	double *q = dst.ptr<double>(0);
	double *z = fenzi.ptr<double>(0);
	double zi;
	double* w;
	double mu;
	/*ut << "u1=" << u << endl;*/
	for (int j = 0; j < leishu; j++)
	{
		 zi = 0;
		for (int i = 0; i < data; i++)
		{
			 w = mf.ptr<double>(i);
			zi = zi + w[j] *(double) q[i];
		}
		z[j] = zi;
	}

	
	Mat fenmu;
	fenmu.create(1, leishu, u.type());
	double*y = fenmu.ptr<double>(0);
	
	for (int j = 0; j < leishu; j++)
	{
		 mu = 0;
		for (int i = 0; i < data; i++)
		{
			 w = mf.ptr<double>(i);
			mu = mu + w[j];
		}
		y[j] = mu;
	}
	/*cout << "fenmu"<<fenmu << endl;*/
	Mat ci = fenzi / fenmu;
	//cout << "ci=" << ci << endl;
	Mat juli;
	juli.create(data, leishu, u.type());
	double *qq = dst.ptr<double>(0);
	double *r = ci.ptr<double>(0);
	double *m;
	for (int i = 0; i < data; i++)
	{

	      m = juli.ptr<double>(i);

		for (int j = 0; j < leishu; j++)
		{
			m[j] = pow((r[j] - (double)qq[i]), 2 );
			
		}
	}//Éú³ÉÁË¾àÀë¾ØÕó

	/*cout << "juli" << juli << endl;*/
	for (int i = 0; i < data; i++)
	{
		z = u.ptr<double>(i);
		m = juli.ptr<double>(i);
		for (int j = 0; j < leishu; j++)
		{
			double shang = 0;
			for (int k = 0; k < leishu; k++)
			{
				double zz =pow((m[j] / m[k]), (1 / (double)(cifang - 1)));
				
				shang = shang +zz;
				
			}
			z[j] = pow(shang,-1);
		}
	}/*
	cout << "u=" << u << endl;*/
	double J = 0;
	double *s;
	for (int i = 0; i < data; i++)
	{
		s = u.ptr<double>(i);
		m = juli.ptr<double>(i);
		for (int j = 0; j < leishu; j++)
		{
			J = J + pow(s[j], cifang)*pow(m[j], (cifang - 1));
		}
	}
	//cout << "J="<<J << endl;
	
	return J;
}