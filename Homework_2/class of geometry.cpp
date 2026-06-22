// 类与对象的真理，我已解明！！！哈哈哈哈哈！！！
// 最大的遗憾是Rectangle类中Length1和Length2没有实现初始化（需要对基本上所有成员函数大修）

#include <iostream>
#include <cmath>
using namespace std;

class Point
{
    double x, y;

public:
    Point();
    Point(int m, int n);
    Point(const Point &other);
    ~Point();
    double getX() const;
    double getY() const;
    void setX();
    void setY();
    void PrintPoint();
};

Point::Point()
{
    x = 0;
    y = 0;
}

Point::Point(int m, int n)
{
    x = m;
    y = n;
}

Point::Point(const Point &other)
{
    x = other.x;
    y = other.y;
    cout << "拷贝构造函数调用" << endl;
}

Point::~Point()
{
    cout << "析构函数调用" << endl;
}

double Point::getX() const
{
    return x;
}

double Point::getY() const
{
    return y;
}

void Point::setX()
{
    cin >> x;
}

void Point::setY()
{
    cin >> y;
}

void Point::PrintPoint()
{
    cout << "(" << x << "," << y << ")" << endl;
}

class Line
{
    Point p1, p2;

public:
    Line();
    Line(Point p, Point q);
    Line(const Line &l);
    ~Line();
    Point getP1() const;
    Point getP2() const;
    double getLength();
    void PrintLine();
};

Line::Line()
{
    p1 = Point(0, 0);
    p2 = Point(0, 0);
}

Line::Line(Point p, Point q)
{
    p1 = p;
    p2 = q;
}

Line::Line(const Line &l)
{
    p1 = l.p1;
    p2 = l.p2;
}

Line::~Line()
{
    cout << "析构函数调用" << endl;
}

Point Line::getP1() const
{
    return p1;
}

Point Line::getP2() const
{
    return p2;
}

double Line::getLength()
{
    double DeltaX = p1.getX() - p2.getX();
    double DeltaY = p1.getY() - p2.getY();
    return sqrt(DeltaX * DeltaX + DeltaY * DeltaY);
}

void Line::PrintLine()
{
    cout << "线段的端点分别为：";
    p1.PrintPoint();
    cout << '\t' << "与" << '\t';
    p1.PrintPoint();
    cout << endl
         << "线段的长度为：";
    getLength();
    cout << endl;
}

class Rectangle
{
    Point topLeft, bottomRight;
    double Length1, Length2;

public:
    Rectangle();
    Rectangle(Point p1, Point p2);
    Rectangle(const Rectangle &R);
    ~Rectangle();
    void setTopLeft(const Point &p);
    void setBottomRight(const Point &p);
    double getArea();
    double getPerimeter();
    bool IsInRect(const Point &p);
    void ShowRectangle();
};

Rectangle::Rectangle()
{
    topLeft = Point(0, 1);
    bottomRight = Point(1, 0);
}

Rectangle::Rectangle(Point p1, Point p2)
{
    topLeft = p1;
    bottomRight = p2;
}

Rectangle::Rectangle(const Rectangle &R)
{
    topLeft = R.topLeft;
    bottomRight = R.bottomRight;
}

Rectangle::~Rectangle()
{
    cout << "析构函数调用" << endl;
}

void Rectangle::setTopLeft(const Point &p)
{
    topLeft = p;
}

void Rectangle::setBottomRight(const Point &p)
{
    bottomRight = p;
}

double Rectangle::getArea()
{
    return Length1 * Length2;
}

double Rectangle::getPerimeter()
{
    return 2 * (Length1 + Length2);
}

bool Rectangle::IsInRect(const Point &p)
{
    double p_x = p.getX();
    double p_y = p.getY();
    double tl_x = topLeft.getX();
    double tl_y = topLeft.getY();
    double br_x = bottomRight.getX();
    double br_y = bottomRight.getY();
    return p_x > tl_x && p_x < br_x && p_y > br_y && p_y < tl_y;
}

void Rectangle::ShowRectangle()
{
    cout << "矩形的左上角点：";
    topLeft.PrintPoint();
    cout << '\t' << "矩形的右下角点：";
    bottomRight.PrintPoint();
    cout << endl
         << "矩形的边长一：" << Length1 << '\t' << "矩形的边长二：" << Length2 << endl
         << "矩形的面积：" << getArea() << endl
         << "矩形的周长：" << getPerimeter() << endl;
}