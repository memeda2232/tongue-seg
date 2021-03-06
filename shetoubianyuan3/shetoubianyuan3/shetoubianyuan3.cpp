// shetoubianyuan3.cpp: 定义控制台应用程序的入口点。
//
#include"stdafx.h"
#include<opencv2\opencv.hpp>
#include<opencv2\dnn.hpp>
#include <iostream>
#include<map>
#include<string>
#include<time.h>

using namespace std;
using namespace cv;

//这里的宽度和高度不能太小了，否则识别率会降低，但是大的尺寸会消耗比较多的时间。
const size_t inWidth = 600;
const size_t inHeight = 600;
//const float WHRatio = inWidth / (float)inHeight;
const char* classNames[] = { "1","2","3" };//只有一类的话，写一类就好

										 //这是coco数据集的类别
										 //const char* classNames[] = { "person", "bicycle", "car", "motorcycle", "airplane", "bus", "train", "truck", "boat", "traffic light",
										 //"fire hydrant", "background", "stop sign", "parking meter", "bench", "bird", "cat", "dog", "horse", "sheep", "cow", "elephant", "bear", "zebra", "giraffe", "background", "backpack",
										 //"umbrella", "background", "background", "handbag", "tie", "suitcase", "frisbee", "skis", "snowboard", "sports ball", "kite", "baseball bat", "baseball glove", "skateboard", "surfboard", "tennis racket",
										 //"bottle", "background", "wine glass", "cup", "fork", "knife", "spoon", "bowl", "banana", "apple", "sandwich", "orange", "broccoli", "carrot", "hot dog", "pizza", "donut",
										 //"cake", "chair", "couch", "potted plant", "bed", "background", "dining table", "background", "background", "toilet", "background", "tv", "laptop", "mouse", "remote", "keyboard",
										 //"cell phone", "microwave", "oven", "toaster", "sink", "refrigerator", "background", "book", "clock", "vase", "scissors", "teddy bear", "hair drier", "toothbrush", "background" };



const float WHRatio = inWidth / (float)inHeight;


int main()
{

	String weights = "G:/tffasterrcnntrain/pbgraph/frozen_model.pb";
	String prototxt = "G:/tffasterrcnntrain/pbgraph/lenet2.pbtxt";
	dnn::Net net = cv::dnn::readNetFromTensorflow(weights,prototxt);
	cout << "ok" << endl;
	Mat frame = cv::imread("G:/tffasterrcnntrain/data/demo/1106023.png_pred");
	Size frame_size = frame.size();

	
	//cv::Mat blob = cv::dnn::blobFromImage(frame, 1, Size(inWidth, inHeight), false, true);//这里的格式是个坑，参考其它博客真的是不行，最后在google上找了好久才发现这个问题,这是个坑！
	//imshow("a", blob);
	//waitKey(0);
	//net.setInput(blob);
	//Mat output = net.forward();
	//cout << "ok" << endl;
	//Mat detectionMat(output.size[2], output.size[3], CV_32F, output.ptr<float>());

	//float confidenceThreshold = 0.5;
	//for (int i = 0; i < detectionMat.rows; i++)
	//{
	//	float confidence = detectionMat.at<float>(i, 2);

	//	if (confidence > confidenceThreshold)
	//	{
	//		size_t objectClass = (size_t)(detectionMat.at<float>(i, 1));
	//		int xLeftBottom = static_cast<int>(detectionMat.at<float>(i, 3) * frame.cols);
	//		int yLeftBottom = static_cast<int>(detectionMat.at<float>(i, 4) * frame.rows);
	//		int xRightTop = static_cast<int>(detectionMat.at<float>(i, 5) * frame.cols);
	//		int yRightTop = static_cast<int>(detectionMat.at<float>(i, 6) * frame.rows);

	//		ostringstream ss;
	//		ss << confidence;
	//		String conf(ss.str());

	//		Rect object((int)xLeftBottom, (int)yLeftBottom,
	//			(int)(xRightTop - xLeftBottom),
	//			(int)(yRightTop - yLeftBottom));

	//		rectangle(frame, object, Scalar(0, 255, 0), 2);
	//		String label = String(classNames[objectClass]) + ": " + conf;
	//		int baseLine = 0;
	//		Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
	//		rectangle(frame, Rect(Point(xLeftBottom, yLeftBottom - labelSize.height),
	//			Size(labelSize.width, labelSize.height + baseLine)),
	//			Scalar(0, 255, 0), CV_FILLED);
	//		putText(frame, label, Point(xLeftBottom, yLeftBottom),
	//			FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0));
	//	}
	//}
	//namedWindow("image", CV_WINDOW_NORMAL);
	//imshow("image", frame);
	//waitKey(0);
	//return 0;
}