//想把坐标也放在Rect里发现不好放 就单独定义一个点结构体
//首先设计一下Armor centralpoint diagonal point函数封装
//在main函数里初始化基本的参数如colorID啥的 函数写好了直接调用在main函数里
//对角线就用勾股定理sqrt开根函数 中心点也是两点除以二 读取输入用cin比scanf方便
//两种颜色正好用一次if语句即可 
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
// 定义一个点结构体，用来存储坐标
struct Point {
    double x, y;

    // 构造函数，初始化坐标
    Point(double x_val = 0, double y_val = 0) 
    {
        x = x_val;
        y = y_val;
    }//不用使用this指针
};


struct Rect {
    int id;         // 数字ID
    int color;      // 颜色（0蓝色，1红色）
    Point topLeft;  // 左上角坐标
    double width;   // 宽度
    double height;  // 高度

    
    Rect(int id_val = 0, int color_val = 0, double x = 0, double y = 0, double w = 0, double h = 0) {
        id = id_val;
        color = color_val;
        topLeft = Point(x, y);
        width = w;
        height = h;//初始化函数
    }
};

// 
class Armor {
private:
    Rect armorRect;  // 包含一个Rect对象作为成员放在private安全一些

public:
    // 有参构造函数，用Rect对象初始化
    Armor(Rect rect) {
        armorRect = rect;
    }

    // 计算装甲板中心坐标
    Point Central_Point() {
        // 中心点x坐标 = 左上角x + 宽度的一半
        // 中心点y坐标 = 左上角y + 高度的一半
        double centerX = armorRect.topLeft.x + armorRect.width / 2;//个人理解为结构的嵌套
        double centerY = armorRect.topLeft.y + armorRect.height / 2;//用点不断向下访问
        return Point(centerX, centerY);//返回坐标
    }

    // 计算装甲板对角线长度
    double Diagonal() {
       
        double diagonal = sqrt(armorRect.width * armorRect.width +
            armorRect.height * armorRect.height);//sqrt 开根函数
        return diagonal;
    }

    // 输出装甲板4个顶点坐标（从左上角开始顺时针）
    void Armor_Point() {
        // 四个点的坐标计算：
        // 左上角：就是原来的topLeft
        // 右上角：x坐标右移宽度，y坐标不变
        // 右下角：x坐标右移宽度，y坐标下移高度
        // 左下角：x坐标不变，y坐标下移高度

        Point topLeft = armorRect.topLeft;
        Point topRight(topLeft.x + armorRect.width, topLeft.y);
        Point bottomRight(topLeft.x + armorRect.width, topLeft.y + armorRect.height);
        Point bottomLeft(topLeft.x, topLeft.y + armorRect.height);
        //建立四个point对象点 根据点坐标加上边长可得个点坐标
        // 按顺序输出四个点
        cout << "(" << topLeft.x << "," << topLeft.y << ") ";
        cout << "(" << topRight.x << "," << topRight.y << ") ";
        cout << "(" << bottomRight.x << "," << bottomRight.y << ") ";
        cout << "(" << bottomLeft.x << "," << bottomLeft.y << ")";
    }

    // 输出装甲板颜色
    void Armor_Color() {
        if (armorRect.color == 0) {
            cout << "蓝";
        }
        else {
            cout << "红";
        }
    }

    // 输出完整的装甲板信息
    void Print_Armor_Info() {
        // 第一行：输出ID和颜色
        cout << "ID：" << armorRect.id << "  颜色：";
        Armor_Color();
       cout << endl;

        // 第二行：输出中心坐标和对角线长度
        Point center = Central_Point();
        cout << "(" << center.x << "," << center.y << ") ";
        cout << "长度：" << fixed << setprecision(2) << Diagonal() << endl;//表示保留两位小数

        // 第三行：输出四个顶点坐标
        Armor_Point();
        cout << endl;
    }
};

int main() {
    int id, color;
    double x, y, width, height;

    // 读取输入
    // 第一行：数字ID和颜色
    cin >> id >> color;

    // 第二行：左上角坐标和宽高
    cin >> x >> y >> width >> height;

    // 创建Rect结构体对象
    Rect armorRect(id, color, x, y, width, height);

    // 创建Armor类对象
    Armor armor(armorRect);

    // 输出装甲板信息
    armor.Print_Armor_Info();

    return 0;
}