ȫ��OpenCV��Ŀ����ʱ��ɱ��Ͱ���Ƭ�ŵ�bվ��Ƶ������ѧϰ����Ŀ���ļ���resources����
˼·��ֵ����ɫ ���ҳ���ɫ��hsv��Χ ��scalar lower upper��ȡ���� �ڰ�ͼ��Ļ��ο�bվ��Ƶ�е�
Scalar lower(hmin, smin, vmin);
Scalar upper(hmax, smax, vmax);
inRange(imgHSV, lower, upper, mask);
��Ե��ȡ��canny�㷨 ���ڴ�С����resize  ��ɫRGB��hsvʲô��ͨ��AI���Ҽ���
����Ҫ��ȫ�ڱ�����Mat::zeros()����ȫ�ڵľ���




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
    // ��ȡͼƬ
    Mat img = imread("Resources/01.png"); //mat ����һ��������
    if (img.empty()) {
        cout << "�޷���ȡͼƬ������·���Ƿ���ȷ" << endl;
        return -1;
    }

    // ����ͼ���СΪ1280*720
    resize(img, img, Size(1280, 720));

    // ת��ΪHSV��ɫ�ռ�
    Mat imgHSV;
    cvtColor(img, imgHSV, COLOR_BGR2HSV);

    // �����ɫ��HSV��Χ����Ҫ����ʵ��ͼƬ������
    // ��ɫ��HSV����������Χ����Ϊ��ɫ��ɫ�������ˣ�
    Scalar lower_red1(0, 120, 70);
    Scalar upper_red1(10, 255, 255);
    Scalar lower_red2(170, 120, 70);
    Scalar upper_red2(180, 255, 255);

    // ������Ĥ
    Mat mask1, mask2, mask;
    inRange(imgHSV, lower_red1, upper_red1, mask1);
    inRange(imgHSV, lower_red2, upper_red2, mask2);

    // �ϲ�������ɫ��Χ����Ĥ
    mask = mask1 | mask2;
    Mat zeros;
    // �����ڰ�ͼ��Ŀ����ɫΪ��ɫ������Ϊ��ɫ��
    Mat binaryImg = Mat::zeros(img.size(), CV_8UC1);//img.size()Ϊ�˻�ȡͼƬ�Ŀ�͸�
    binaryImg = mask;

    // ��Ե��ȡ - Canny�㷨
    Mat edges;
    Canny(binaryImg, edges, 50, 150); //ԭ���ĺ����� �������������ȡ�̶�

    // ����ǳ��ɫ��Եͼ�񣨱���Ϊ��ɫ��
    Mat edgeImg = Mat::zeros(img.size(), CV_8UC3);

    // ����Ե����Ϊǳ��ɫ (BGR��ʽ��ǳ��ɫΪ255,255,0)
    for (int i = 0; i < edges.rows; i++) {
        for (int j = 0; j < edges.cols; j++) {
            if (edges.at<uchar>(i, j) > 0) {
                edgeImg.at<Vec3b>(i, j) = Vec3b(255, 255, 0); // ǳ��ɫ
            }
        }
    }

    // ��ʾͼ��
    namedWindow("ԭͼ", WINDOW_NORMAL);
    namedWindow("�ڰ�ͼ��", WINDOW_NORMAL);
    namedWindow("��Ե��ȡ", WINDOW_NORMAL);

    resizeWindow("ԭͼ", 1280, 720);
    resizeWindow("�ڰ�ͼ��", 1280, 720);
    resizeWindow("��Ե��ȡ", 1280, 720);

    imshow("ԭͼ", img);
    imshow("�ڰ�ͼ��", binaryImg);
    imshow("��Ե��ȡ", edgeImg);

    // �����Եͼ��
    imwrite("edge_image.jpg", edgeImg);//������
    cout << "��Եͼ���ѱ���Ϊ edge_image.jpg" << endl;

    // �ȴ�����
    waitKey(0);

    return 0;
}

