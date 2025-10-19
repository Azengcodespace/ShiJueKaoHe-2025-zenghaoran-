全部OpenCV题目考虑时间成本就把照片放到b站视频课用来学习的项目的文件夹resources里了
思路二值化红色 先找出红色的hsv范围 用scalar lower upper提取出来 黑白图像的话参考b站视频中的
Scalar lower(hmin, smin, vmin);
Scalar upper(hmax, smax, vmax);
inRange(imgHSV, lower, upper, mask);
边缘提取用canny算法 窗口大小就用resize  颜色RGB和hsv什么的通过AI查找即可
后面要用全黑背景用Mat::zeros()创建全黑的矩阵




#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <string>
using namespace cv;
using namespace std;
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // 读取图片
    Mat img = imread("Resources/01.png"); //mat 就是一个矩阵类
    if (img.empty()) {
        cout << "无法读取图片，请检查路径是否正确" << endl;
        return -1;
    }

    // 调整图像大小为1280*720
    resize(img, img, Size(1280, 720));

    // 转换为HSV颜色空间
    Mat imgHSV;
    cvtColor(img, imgHSV, COLOR_BGR2HSV);

    // 定义红色的HSV范围（需要根据实际图片调整）
    // 红色在HSV中有两个范围（因为红色在色环的两端）
    Scalar lower_red1(0, 120, 70);
    Scalar upper_red1(10, 255, 255);
    Scalar lower_red2(170, 120, 70);
    Scalar upper_red2(180, 255, 255);

    // 创建掩膜
    Mat mask1, mask2, mask;
    inRange(imgHSV, lower_red1, upper_red1, mask1);
    inRange(imgHSV, lower_red2, upper_red2, mask2);

    // 合并两个红色范围的掩膜
    mask = mask1 | mask2;
    Mat zeros;
    // 创建黑白图像（目标颜色为白色，背景为黑色）
    Mat binaryImg = Mat::zeros(img.size(), CV_8UC1);//img.size()为了获取图片的宽和高
    binaryImg = mask;

    // 边缘提取 - Canny算法
    Mat edges;
    Canny(binaryImg, edges, 50, 150); //原来的后来的 后面的数字是提取程度

    // 创建浅蓝色边缘图像（背景为黑色）
    Mat edgeImg = Mat::zeros(img.size(), CV_8UC3);

    // 将边缘绘制为浅蓝色 (BGR格式：浅蓝色为255,255,0)
    for (int i = 0; i < edges.rows; i++) {
        for (int j = 0; j < edges.cols; j++) {
            if (edges.at<uchar>(i, j) > 0) {
                edgeImg.at<Vec3b>(i, j) = Vec3b(255, 255, 0); // 浅蓝色
            }
        }
    }

    // 显示图像
    namedWindow("原图", WINDOW_NORMAL);
    namedWindow("黑白图像", WINDOW_NORMAL);
    namedWindow("边缘提取", WINDOW_NORMAL);

    resizeWindow("原图", 1280, 720);
    resizeWindow("黑白图像", 1280, 720);
    resizeWindow("边缘提取", 1280, 720);

    imshow("原图", img);
    imshow("黑白图像", binaryImg);
    imshow("边缘提取", edgeImg);

    // 保存边缘图像
    imwrite("edge_image.jpg", edgeImg);//新名字
    cout << "边缘图像已保存为 edge_image.jpg" << endl;

    // 等待按键
    waitKey(0);

    return 0;
}

