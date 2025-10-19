//利用鼠标函数mousecallback 完成框选并保存 根据参数利用if语句首先了解清楚参数一个个判断==
// 判断鼠标状态显示框线条还不会 用if同时结合bool 鼠标点击导致的bool值转换可以控制开始结束
//setmousecallback在main函数里与mousecallback配套使用 保存框选的图片就用imwrite函数保存到本地文件
#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <string>

using namespace cv;
using namespace std;

// 全局变量
Point startPoint, endPoint;//建立两个point类的坐标 左上角和右下角
bool drawing = false;
Mat image;

// 鼠标回调函数
void mouseCallback(int event, int x, int y, int flags, void* userdata) 
{//参数依次为鼠标类型事件 鼠标x坐标 鼠标y坐标 辅助按键状态 自定义传递数据
    if (event == EVENT_LBUTTONDOWN) {
        // 表示鼠标左键被按下
        drawing = true;
        startPoint = Point(x, y);
    }
    else if (event == EVENT_MOUSEMOVE && drawing)//此时drawing为true 
    {
        // 表示鼠标移动，更新终点并显示矩形
        endPoint = Point(x, y);
        Mat temp = image.clone();//复制原始图像 避免修改原图
        rectangle(temp, startPoint, endPoint, Scalar(0, 255, 0), 2);
        //在复制的图像上创建一个矩形左上角和右下角坐标搞上去 该scalar参数绿色
        imshow("猫猫图片", temp);
    }
    else if (event == EVENT_LBUTTONUP) {
        // 鼠标释放，完成框选
        drawing = false;
        endPoint = Point(x, y);

        // 建立一个rect矩形类 提取框选区域roi感兴趣区域 
        Rect roi(min(startPoint.x, endPoint.x), min(startPoint.y, endPoint.y),
            abs(endPoint.x - startPoint.x), abs(endPoint.y - startPoint.y));
        //min()是取最小值函数 abs（）是取绝对值函数二者相结合防止出现负数坐标的情况 Rect类默认左上角为初始值
        Mat selected = image(roi);//将roi的图像存到mat类型的selected对象

        // 保存图片
        imwrite("selected_cat.jpg", selected);//将selected保存
        cout << "框选的猫猫已保存为 selected_cat.png" << endl;

        // 显示框选的部分
        imshow("框选的猫猫", selected);
    }
}

int main() {
    // 加载图片
    image = imread("Resources/02.png");
    // 创建窗口
    namedWindow("猫猫图片");
    setMouseCallback("猫猫图片", mouseCallback);//调用函数setmousecallback 指定要监听的目标窗口
    //猫猫图片 然后执行mousecallback这个逻辑函数

    // 显示图片
    imshow("猫猫图片", image);

    cout << "按住鼠标左键拖动框选猫猫，松开后自动保存" << endl;

    waitKey(0);
    return 0;
}