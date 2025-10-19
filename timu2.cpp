//打开摄像头用videocapture cap()借鉴了视频中的这段代码新建了一个窗口namedwindow
//然后用createTrackbar创建滑动条录制的话借鉴了视频代码
//VideoCapture cap(1);
//Mat img;
//while (true)
//{
//    cap.read(img);
//
//    imshow("Image", img);
//    waitKey(1);
//}无限循环把每一帧的图片存起来组成视频
//开始录制结束录制的话可以用bool函数再结合if语句 
// 在画面上显示参数的话用putText函数
// 要知道帧率计算fps=frameCount /currentTime用一秒内的帧数除以时间差得到实际帧率
//查找可知时间有getTickCount gettickfrequncy两个函数


#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <string>

using namespace cv;
using namespace std;

// 全局变量
int exposureVal = 0;    // 曝光值
int brightnessVal = 50; // 亮度值
bool isRecording = false; // 是否正在录制
VideoWriter writer;     // 视频录制器

int main() {
    // 打开摄像头
    VideoCapture cap(0);//0是默认摄像头 创建了cap对象
   
    // 创建显示窗口
    namedWindow("摄像头");

    // 创建滑动条
    createTrackbar("曝光", "摄像头", &exposureVal, 20);//前面是滑动条的名称 后面是窗口名称 
    createTrackbar("亮度", "摄像头", &brightnessVal, 100);//

    // 用于计算FPS的变量
    int frameCount = 0;//初始化一秒内的总帧数
    double startTime = (double)getTickCount();//gettickcount是OpenCV内置函数返回时钟周期数
    double fps = 0;//初始化

    while (true) {
        Mat frame;//叫做frame的矩阵
        cap >> frame; // 读取一帧画面

       

        // 设置摄像头参数属性
        cap.set(CAP_PROP_EXPOSURE, exposureVal - 10); // 曝光范围-10到10
        cap.set(CAP_PROP_BRIGHTNESS, brightnessVal);  // 亮度范围0-100

        // 计算FPS
        frameCount++;//帧数加一
        double currentTime = ((double)getTickCount() - startTime) / getTickFrequency();//返回每秒的时钟周期数
        if (currentTime >= 1.0) {
            fps = frameCount / currentTime;
            frameCount = 0;
            startTime = (double)getTickCount();
        }

        // 在画面上显示信息 to_string()
        string info = "分辨率: " + to_string(frame.cols) + "x" + to_string(frame.rows);
        putText(frame, info, Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 255, 0), 2);
        //scalar 就是颜色设置   这个是为了拼接多少乘多少的分辨率
        string fpsText = "FPS: " + to_string((int)fps);
        putText(frame, fpsText, Point(10, 60), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 255, 0), 2);

        // 按R键开始/停止录制
        char key = waitKey(1);//waitkey函数返回键盘字符的ASCII值
        if (key == 'r' || key == 'R') {
            if (!isRecording) {
                // 开始录制
                writer.open("recorded_video.avi",
                    VideoWriter::fourcc('M', 'J', 'P', 'G'),//不清楚但直接用
                    20,//每秒写入20帧
                    Size(frame.cols, frame.rows));
                if (writer.isOpened()) {
                    isRecording = true;
                    cout << "开始录制视频" << endl;
                }
            }
            else {
                // 停止录制
                isRecording = false;
                writer.release();
                cout << "停止录制，视频已保存" << endl;
            }
        }

        // 如果正在录制，保存当前帧
        if (isRecording) {
            writer.write(frame);//将当前帧frame写入视频文件
            // 在画面上显示录制状态
            putText(frame, "录制中...", Point(10, 90), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 0, 255), 2);
        }

        // 显示画面
        imshow("摄像头", frame);

        // 按ESC退出 esc的ASCII值
        if (key == 27) {
            break;
        }
    }

    // 释放资源
    if (isRecording) {
        writer.release();
    }
    cap.release();//关闭摄像头
    destroyAllWindows();//关闭所有窗口以防残留

    return 0;

}