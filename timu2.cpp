//������ͷ��videocapture cap()�������Ƶ�е���δ����½���һ������namedwindow
//Ȼ����createTrackbar����������¼�ƵĻ��������Ƶ����
//VideoCapture cap(1);
//Mat img;
//while (true)
//{
//    cap.read(img);
//
//    imshow("Image", img);
//    waitKey(1);
//}����ѭ����ÿһ֡��ͼƬ�����������Ƶ
//��ʼ¼�ƽ���¼�ƵĻ�������bool�����ٽ��if��� 
// �ڻ�������ʾ�����Ļ���putText����
// Ҫ֪��֡�ʼ���fps=frameCount /currentTime��һ���ڵ�֡������ʱ���õ�ʵ��֡��
//���ҿ�֪ʱ����getTickCount gettickfrequncy��������


#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <string>

using namespace cv;
using namespace std;

// ȫ�ֱ���
int exposureVal = 0;    // �ع�ֵ
int brightnessVal = 50; // ����ֵ
bool isRecording = false; // �Ƿ�����¼��
VideoWriter writer;     // ��Ƶ¼����

int main() {
    // ������ͷ
    VideoCapture cap(0);//0��Ĭ������ͷ ������cap����
   
    // ������ʾ����
    namedWindow("����ͷ");

    // ����������
    createTrackbar("�ع�", "����ͷ", &exposureVal, 20);//ǰ���ǻ����������� �����Ǵ������� 
    createTrackbar("����", "����ͷ", &brightnessVal, 100);//

    // ���ڼ���FPS�ı���
    int frameCount = 0;//��ʼ��һ���ڵ���֡��
    double startTime = (double)getTickCount();//gettickcount��OpenCV���ú�������ʱ��������
    double fps = 0;//��ʼ��

    while (true) {
        Mat frame;//����frame�ľ���
        cap >> frame; // ��ȡһ֡����

       

        // ��������ͷ��������
        cap.set(CAP_PROP_EXPOSURE, exposureVal - 10); // �عⷶΧ-10��10
        cap.set(CAP_PROP_BRIGHTNESS, brightnessVal);  // ���ȷ�Χ0-100

        // ����FPS
        frameCount++;//֡����һ
        double currentTime = ((double)getTickCount() - startTime) / getTickFrequency();//����ÿ���ʱ��������
        if (currentTime >= 1.0) {
            fps = frameCount / currentTime;
            frameCount = 0;
            startTime = (double)getTickCount();
        }

        // �ڻ�������ʾ��Ϣ to_string()
        string info = "�ֱ���: " + to_string(frame.cols) + "x" + to_string(frame.rows);
        putText(frame, info, Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 255, 0), 2);
        //scalar ������ɫ����   �����Ϊ��ƴ�Ӷ��ٳ˶��ٵķֱ���
        string fpsText = "FPS: " + to_string((int)fps);
        putText(frame, fpsText, Point(10, 60), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 255, 0), 2);

        // ��R����ʼ/ֹͣ¼��
        char key = waitKey(1);//waitkey�������ؼ����ַ���ASCIIֵ
        if (key == 'r' || key == 'R') {
            if (!isRecording) {
                // ��ʼ¼��
                writer.open("recorded_video.avi",
                    VideoWriter::fourcc('M', 'J', 'P', 'G'),//�������ֱ����
                    20,//ÿ��д��20֡
                    Size(frame.cols, frame.rows));
                if (writer.isOpened()) {
                    isRecording = true;
                    cout << "��ʼ¼����Ƶ" << endl;
                }
            }
            else {
                // ֹͣ¼��
                isRecording = false;
                writer.release();
                cout << "ֹͣ¼�ƣ���Ƶ�ѱ���" << endl;
            }
        }

        // �������¼�ƣ����浱ǰ֡
        if (isRecording) {
            writer.write(frame);//����ǰ֡frameд����Ƶ�ļ�
            // �ڻ�������ʾ¼��״̬
            putText(frame, "¼����...", Point(10, 90), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 0, 255), 2);
        }

        // ��ʾ����
        imshow("����ͷ", frame);

        // ��ESC�˳� esc��ASCIIֵ
        if (key == 27) {
            break;
        }
    }

    // �ͷ���Դ
    if (isRecording) {
        writer.release();
    }
    cap.release();//�ر�����ͷ
    destroyAllWindows();//�ر����д����Է�����

    return 0;

}