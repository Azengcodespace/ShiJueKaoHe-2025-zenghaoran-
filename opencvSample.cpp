// opencvSample.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "opencv2/opencv.hpp"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>
using namespace cv;
using namespace std;

/*void main()
{
	string path = "Resources/test.png";
	Mat img = imread(path);
	imshow("Image", img);
}*/
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

/*void main()
{   
	string path = "Resources/test_video.mp4";
	VideoCapture cap(path); 
	Mat img;
	while (true)
	{
		cap.read(img);
	
		imshow("Image", img);
		waitKey(20);
	}
}*/
/*Mat img = imread("Resources/test.png"); //提前放置测试图片D://a.png
		imshow("test", img);
	waitKey(0);
	return 0;*/
void main()
{
	
	VideoCapture cap(0);
	Mat img;
	while (true)
	{
		cap.read(img);

		imshow("Image", img);
		waitKey(20);
	}
}