//������꺯��mousecallback ��ɿ�ѡ������ ���ݲ�������if��������˽��������һ�����ж�==
// �ж����״̬��ʾ������������ ��ifͬʱ���bool ��������µ�boolֵת�����Կ��ƿ�ʼ����
//setmousecallback��main��������mousecallback����ʹ�� �����ѡ��ͼƬ����imwrite�������浽�����ļ�
#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <string>

using namespace cv;
using namespace std;

// ȫ�ֱ���
Point startPoint, endPoint;//��������point������� ���ϽǺ����½�
bool drawing = false;
Mat image;

// ���ص�����
void mouseCallback(int event, int x, int y, int flags, void* userdata) 
{//��������Ϊ��������¼� ���x���� ���y���� ��������״̬ �Զ��崫������
    if (event == EVENT_LBUTTONDOWN) {
        // ��ʾ������������
        drawing = true;
        startPoint = Point(x, y);
    }
    else if (event == EVENT_MOUSEMOVE && drawing)//��ʱdrawingΪtrue 
    {
        // ��ʾ����ƶ��������յ㲢��ʾ����
        endPoint = Point(x, y);
        Mat temp = image.clone();//����ԭʼͼ�� �����޸�ԭͼ
        rectangle(temp, startPoint, endPoint, Scalar(0, 255, 0), 2);
        //�ڸ��Ƶ�ͼ���ϴ���һ���������ϽǺ����½��������ȥ ��scalar������ɫ
        imshow("èèͼƬ", temp);
    }
    else if (event == EVENT_LBUTTONUP) {
        // ����ͷţ���ɿ�ѡ
        drawing = false;
        endPoint = Point(x, y);

        // ����һ��rect������ ��ȡ��ѡ����roi����Ȥ���� 
        Rect roi(min(startPoint.x, endPoint.x), min(startPoint.y, endPoint.y),
            abs(endPoint.x - startPoint.x), abs(endPoint.y - startPoint.y));
        //min()��ȡ��Сֵ���� abs������ȡ����ֵ�����������Ϸ�ֹ���ָ����������� Rect��Ĭ�����Ͻ�Ϊ��ʼֵ
        Mat selected = image(roi);//��roi��ͼ��浽mat���͵�selected����

        // ����ͼƬ
        imwrite("selected_cat.jpg", selected);//��selected����
        cout << "��ѡ��èè�ѱ���Ϊ selected_cat.png" << endl;

        // ��ʾ��ѡ�Ĳ���
        imshow("��ѡ��èè", selected);
    }
}

int main() {
    // ����ͼƬ
    image = imread("Resources/02.png");
    // ��������
    namedWindow("èèͼƬ");
    setMouseCallback("èèͼƬ", mouseCallback);//���ú���setmousecallback ָ��Ҫ������Ŀ�괰��
    //èèͼƬ Ȼ��ִ��mousecallback����߼�����

    // ��ʾͼƬ
    imshow("èèͼƬ", image);

    cout << "��ס�������϶���ѡèè���ɿ����Զ�����" << endl;

    waitKey(0);
    return 0;
}